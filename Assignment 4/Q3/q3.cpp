#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

using namespace std;

vector<int> MarkingOnRod;
int size;
int MarkingOnRodSize;
int **SelectThis;
int **memo;

int StringToInt(string a);

void readData(char *filename)
{
	ifstream file;
	file.open(filename);
	string temp;
	int len;
	file >> temp;
	file >> len;
	size = len;
	MarkingOnRod.push_back(0);
	file >> temp;
	while (file >> temp)
	{
		MarkingOnRod.push_back(StringToInt(temp));
	}
	MarkingOnRod.push_back(size);

	MarkingOnRodSize = MarkingOnRod.size();
	SelectThis = new int*[MarkingOnRodSize];
	memo = new int*[MarkingOnRodSize];

	for (int i = 0; i < MarkingOnRodSize; i++)
	{
		SelectThis[i] = new int[MarkingOnRodSize];
		memo[i] = new int[MarkingOnRodSize];

	}

	for (int i = 0; i < MarkingOnRodSize; ++i)
	{
		for (int j = 0; j < MarkingOnRodSize; ++j)
		{
			memo[i][j] = 0;
		}
	}
}

int StringToInt(string a)
{
	int i;
	istringstream(a) >> i;
	return i;
}

string intToString(int a)
{
    ostringstream str1; 
    str1 << a; 
    return str1.str(); 
}

void PrintData()
{
	cout<<"Size: "<<size<<endl;
	cout<<"MarkingOnRod:";
	for (int i = 0; i < MarkingOnRodSize; i++)
	{
		cout<<" "<<MarkingOnRod[i];
	}
	cout<<endl;
	cout<<"Memoization: "<<endl;
	for (int i = 0; i < MarkingOnRodSize; i++)
	{
		for (int j = 0; j < MarkingOnRodSize; j++)
		{
			cout<<" "<<memo[i][j];
		}
		cout<<endl;
	}

	cout<<"\nSelected: "<<endl;
	for (int i = 0; i < MarkingOnRodSize; i++)
	{
		for (int j = 0; j <MarkingOnRodSize; j++)
		{
			cout<<" "<<SelectThis[i][j];
		}
		cout<<endl;
	}
}

int Algorithm(int beg, int end)
{
	if (end == beg + 1)
	{
		return 0;
	}

	if (memo[beg][end])
	{
		return memo[beg][end];
	}
	else
	{
		int Min = 100000;
		int k = beg + 1;

		while (k < end)
		{
			int newMin = min(Min, Algorithm(beg,k) + Algorithm(k,end));

			if (Min != newMin)
			{
				SelectThis[beg][end] = k;
				Min = newMin;
			}
			k++;
		}

		memo[beg][end] = (MarkingOnRod[end] - MarkingOnRod[beg]) + Min;
		return memo[beg][end];
	}
	
	
}

void printOrdering(int start, int end)
{
	if (end <= start+1)
	{
		return;
	}
	int z = SelectThis[start][end];
	cout << MarkingOnRod[z] << " ";
	printOrdering(start,z);
	printOrdering(z,end);
}

int main(int argc, char** argv)
{
	char* filename = argv[1];
	readData(filename);
	int result = Algorithm(0, MarkingOnRodSize-1);
	cout<<"Optimal cut ordering: ";
	printOrdering(0, MarkingOnRodSize-1);
	cout<<"\nLeast cost: "<<result<<endl;
}
