#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

int StoI(string a);
string ItoS(int a);

vector<string> FinalAnswer;
string Ans;

class Data{
public:
	int NumberOfWeeks;
	int *HighRevenue;
	int *LowRevenue;
	int *memoization;

	Data(int x)
	{
		NumberOfWeeks = x;
		HighRevenue = new int[x+1];
		LowRevenue = new int[x+1];
		memoization = new int[x+1];

		for (int i = 0; i <= NumberOfWeeks; i++)
		{
			memoization[i] = -1;
		}
		memoization[0] = 0;	
	}

	int FindMaxRevenue(int n)
	{
		if (memoization[n] < 0)
		{
			int isLow  = FindMaxRevenue(n-1) + LowRevenue[n];
			int isHigh = HighRevenue[n] + FindMaxRevenue(n-2);
			memoization[n] = max(isHigh, isLow);
		}
		return memoization[n];
	}
	
};

int StoI(string a)
{
	int i;
	istringstream(a) >> i;
	return i;
}

string ItoS(int a)
{
    ostringstream str1; 
    str1 << a; 
    return str1.str(); 
}


void readInput(Data* input, char *filename)
{
	ifstream file1;
	file1.open(filename);
	string temp;
	file1 >> temp >> temp;
	input = new Data(StoI(temp));
	file1 >> temp;

	//cout<<input->NumberOfWeeks<<endl;
	for (int i = 1; i <= input->NumberOfWeeks; i++)
	{
		file1 >> input->HighRevenue[i];
		//cout<<input->HighRevenue[i]<<endl;
	}
	file1 >> temp;

	for (int i = 1; i <= input->NumberOfWeeks; i++)
	{
		file1 >> input->LowRevenue[i];
		//cout<<input->LowRevenue[i]<<endl;
	}

	input->memoization[1] = max(input->LowRevenue[1], input->HighRevenue[1]);
	
	input->FindMaxRevenue(input->NumberOfWeeks);


	int n = input->NumberOfWeeks;
	while(n > 0)
	{
		if (input->memoization[n] - input->memoization[n-2] == input->HighRevenue[n])
		{
			//Ans += "Week " + ItoS(n) + ": High " + ItoS(input->HighRevenue[n]) + "\n";
			FinalAnswer.push_back("Week " + ItoS(n) + ": High " + ItoS(input->HighRevenue[n]));
			//Ans += "Week " + ItoS(n-1) + ": Priming \n";
			FinalAnswer.push_back("Week " + ItoS(n-1) + ": Priming ");
			n--;
		} 
		else 
		{
			FinalAnswer.push_back("Week " + ItoS(n) + ": Low " + ItoS(input->LowRevenue[n]));
			//Ans += "Week " + ItoS(n) + ": Low " + ItoS(input->LowRevenue[n]) + "\n";

		}
		n--;
		
	}


	for (int i = input->NumberOfWeeks-1 ; i >=0 ; i--)
	{
		cout << FinalAnswer[i] << endl;
	}
	//cout<<Ans<<endl;
	
	cout << "Total Revenue: " << input->memoization[input->NumberOfWeeks] << endl;
}


int main(int argc, char** argv)
{
	char* filename = argv[1];
	Data* input;
	readInput(input, filename);
	return 0;
}
