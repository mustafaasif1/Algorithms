#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <sstream>
#include <queue>

using namespace std;
string ans = "";

string intToString(int a)
{
    ostringstream str1; 
    str1 << a; 
    return str1.str(); 
}

priority_queue < pair<int,int> > column;

struct matrix{
	int* r;
	int* c;
	int N;
};


matrix input(char* filename){
	string line;

	ifstream data;
	data.open(filename);
	string tempString;
	data >> tempString;
	data >> tempString;

	stringstream geek(tempString);
	int N;
	geek >> N;

	int* AllRows = new int[N];
	int* AllColumns = new int[N];

	int j = 0;
	while(!data.eof())
	{
		string temp1;
		data >> temp1;

		string str;
		getline(data, str);

		stringstream ss;     
	    ss << str; 
	    int number;

	    for (int i = 0; i < N; i++)
	    {
	    	ss >> number;
	    	if (j == 0)
	    	{
	    		AllRows[i] = number;
	    	}
	    	else 
	    	{
	    		AllColumns[i] = number;
	    		column.push(make_pair(AllColumns[i],i));
	    	}
	    }
	    j++;
	}
	data.close();

	matrix m;
	m.N = N;
	m.r = AllRows;
	m.c = AllColumns;

	return m;
}

void find(int* AllRows,int* AllColumns,int N){
	
	bool** dummy = new bool*[N];
	for(int i = 0; i < N; i++){
		dummy[i] = new bool[N];
		for(int j = 0; j < N; j++){
			dummy[i][j] = 0;
		}
	}

	for (int i = 0; i < N; ++i)	
	{
		while(AllRows[i] > 0)
		{
			int max_value = column.top().first;
			int max_col = column.top().second;
			column.pop();
			column.push(make_pair(max_value-1,max_col));
			dummy[i][max_col] = 1;
			AllColumns[max_col]--;
			AllRows[i]--;
		}
	}

	int i1 = 0;
	while(i1 < N)
	{
		if(AllColumns[i1] || AllRows[i1] )
		{
			ans+= "Not Possible\n";
			return;
		}
		i1++;
	}

	int x1 = 0;
	for(int i = 0; i < N; i++)
	{
		for(int j = 0; j < N; j++){
			if(dummy[i][j]){
				if (x1 != 0 )
				{
					ans+=" ";
				}
				ans+="(" + intToString(i+1) + "," + intToString(j+1) + ")";
				x1=1;
			}
		}
		ans+="\n";
		x1 = 0;
	}
}

int main(int argc, char** argv){

	char* filename;
	if (argc == 2)
	{
		filename = argv[1];
	}

	matrix mat = input(filename);
	find(mat.r, mat.c, mat.N);
	cout<<ans;

	return 0;
}