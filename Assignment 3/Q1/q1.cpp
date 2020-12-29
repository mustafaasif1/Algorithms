#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

/*
	Mustafa Asif
	21100042

	This algorithm has a complexity of O(n^2). No woman proposes to a man more than once. If the all n women propose to all n men,
	there would be n^2 proposals. Since no woman proposes to a man more than once, there can’t be any additional proposals.

	This was the psuedocode that I used to implement stableMatching
	
	function stableMatching {
	    Initialize all m ∈ M and w ∈ W to free
	    while ∃ free man m who still has a woman w to propose to {
	       w = first woman on m’s list to whom m has not yet TimesProposed
	       if w is free
	         (m, w) become engaged
	       else some pair (m', w) already exists
	         if w prefers m to m'
	            m' becomes free
	           (m, w) become engaged 
	         else
	           (m', w) remain engaged
	    }
	}
*/

struct data
{
	int m;
	int n;
	vector< vector<int> > AllLocations;
	vector< vector<int> > AllTeams;
	vector< vector<int> > AllSchedules;
};



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

int getNum(string s){
   for (int i = 0; i < s.length(); ++i)
   {
      if (isdigit(s[i]))
      {
         return StringToInt(s.substr(i));
      }
   }

}

vector<string> SplitingString(string sen)
{
	int begin = 0;
	int n = sen.length();
	vector<string> answer;
	int i = 0;
	
	while (i < n)
	{
		if(sen[i] != '-'  && !isalnum(sen[i]))
		{
			if(i > begin) 
			{
				answer.push_back(sen.substr(begin, i-begin));
			}
			begin = i+1;
		}
		++i;
	}
	
	answer.push_back(sen.substr(begin,n-begin));
	return answer;
}

void readInput(data* Data, char* fileName){
	ifstream file;
	file.open(fileName);
	string s;
	int n;
	int m;
	getline(file,s);
	n = StringToInt(SplitingString(s)[1]);
	Data->n = n;

	for (int i = 0; i < n; ++i)
	{
		getline(file,s);
		vector<string> vec = SplitingString(s);
	
		Data->m = vec.size()-1;
		m = Data->m;
		int m = getNum(vec[0]);
		
		vector<int> xx;
		vector<int> eachTeam;
		
		for (int i = 1; i < vec.size(); ++i)
		{
			if(vec[i] == "-"){
				xx.push_back(0);
			}
			else{
				eachTeam.push_back(getNum(vec[i]) );
				xx.push_back(getNum(vec[i]) );
				
			}
		}
		Data->AllTeams.push_back(eachTeam);
		Data->AllSchedules.push_back(xx);
	}
	
	Data->AllLocations.resize(n);

	int x3 = m-1;
	while (x3 >= 0)
	{
		for (int j =0; j < n; j++)
		{
			if(Data->AllSchedules[j][x3]){
				int n = Data->AllSchedules[j][x3];
				Data->AllLocations[n-1].push_back(j+1);
			}
		}
		--x3;
	}
	return;
}

bool CheckingPreference(data* Data,int prev,int cur,int team)
{
	int x = 0;
	while (x<Data->n)
	{
		if(Data->AllTeams[team][x] == cur)
		{
			return true;
		}
		if (Data->AllTeams[team][x] == prev)
		{
			return false;
		}
		++x;
	}
}

int somePersonLeft(int* M, int* h, int z){
	
	int x = 0;
	while(x < z)
	{
		if (M[x] == 0)
		{
			if (h[x] < z)
			{
				return x;
			}
		}
		++x;
	}
	if (1)
		return -1;
}

void GaleShapleyAlgorithm(data *Data)
{
	int n = Data->n;
	// n is the total number of AllTeams

	int TeamMatched[n];
	// TeamMatched has AllTeams who have matched. The index contain the AllLocationss of the AllTeams
	
	int AX[n];

	int TimesProposed[n];
	// h or TimesProposed are the number of times h[i] has TimesProposed. Has to be less than the total number of AllLocations. 
	
	
	int x1 = 0;
	while (x1 < n)
	{
		TeamMatched[x1] = 0;
		TimesProposed[x1] = 0;
		AX[x1] = 0;
		++x1;
	}
	// Everything has been initialized to 0. TeamMatched, TimesProposed and AX


	while(somePersonLeft(TeamMatched,TimesProposed,n) != -1)
	{
		int PersonNotMatched = somePersonLeft(TeamMatched,TimesProposed,n);
		//This is the person that has not been matched yet

		int s = Data->AllLocations[PersonNotMatched][TimesProposed[PersonNotMatched]];
		// This finds out the next preference of the person taht is not yet matched. The previous preferences that have been rejected are cancelled.

		s = s-1;
		// This is done as we have to access the values at the 0th index.
		
		TimesProposed[PersonNotMatched]++;
		// x has increased its number of proposals.

		if (AX[s] == 0)
		{
			AX[s] = PersonNotMatched+1;
			TeamMatched[PersonNotMatched] = s+1;
			// A match has been made
		}
		else if (CheckingPreference(Data,AX[s],PersonNotMatched+1,s) )
		{
			TeamMatched[PersonNotMatched] = s+1;
			TeamMatched[AX[s]-1] = 0;
			AX[s] = PersonNotMatched+1;
		}
		else 
		{
			TeamMatched[PersonNotMatched] = 0;
		}

	}

	string ans;
	ans += "Final Destinations: ";
	int x2 = 0;

	while (x2 < n-1)
	{
		if (TeamMatched[x2] != 0)
		{
			ans+="L" + intToString(x2+1) + " T" + intToString(TeamMatched[x2]) + ", ";
		}
		x2++;
	}
	ans+="L" + intToString(n) + " T" + intToString(TeamMatched[n-1]) + "\n";
	cout<<ans;
}

int main(int argc, char** argv)
{
	char* filename;
	filename = argv[1];
	data* Data = new data;
	readInput(Data, filename);
	GaleShapleyAlgorithm(Data);
	return 0;
}