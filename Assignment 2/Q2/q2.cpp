#include <iostream>
#include <vector>
#include <sstream>
#include <iostream>
#include <fstream>
#include <vector>
#include <queue>


string ans = "";
using namespace std;

struct SingleRack{
	int i;
	double l;
	double p;
	double x;

	bool operator<(const SingleRack& right) const{
		return x < right.x;
	}
};

priority_queue<SingleRack> parse(char* filename){
		
	string line;
	ifstream data;
	data.open(filename);
	string tempString;
	data >> tempString;
	data >> tempString;

	stringstream geek(tempString);
	int N;
	geek >> N;

	double L[N];
	double P[N];

	int j = 0;
	while(!data.eof())
	{
		string temp1;
		data >> temp1;

		string str;
		getline(data, str);

		stringstream ss;     
	    ss << str; 
	    double number;

	    for (int i = 0; i < N; i++)
	    {
	    	ss >> number;
	    	if (j == 0)
	    	{
	    		L[i] = number;
	    	}
	    	else 
	    	{
	    		P[i] = number;
	    	}
	    }
	    j++;
	}
	data.close();


	priority_queue<SingleRack> AllRacks;

	for (int i = 0; i < N; i++)
	{
		SingleRack temp;
		temp.i = i+1;
		temp.l = L[i];
		temp.p = P[i];
		temp.x = P[i]/L[i];
		AllRacks.push(temp);
	}

	return AllRacks;	
}

void TimeTaken(priority_queue<SingleRack> AllRacks){
	
	double WholeLength, AlltheTime = 0;

	int counter = 0;

	while(!AllRacks.empty())
	{
		SingleRack temp = AllRacks.top();
		stringstream sss;
		sss<<temp.i;
		string s1;
		sss>>s1;
		if (counter != 0)
		{
			ans+= " ";
		}
		ans+=s1;
		WholeLength += temp.l;
		double time = temp.p * WholeLength;
		AlltheTime += time;
		AllRacks.pop();
		counter++;
	}

	std::ostringstream ss;
	ss << AlltheTime;
	std::string s(ss.str());

	ans+= "\nExpected time: " + s + '\n';
}

int main(int argc, char** argv){

	char* filename;
	if (argc == 2)
	{
		filename = argv[1];
	}
	priority_queue<SingleRack> AllRacks = parse(filename);

	TimeTaken(AllRacks);
	cout<<ans;
	return 0;
}