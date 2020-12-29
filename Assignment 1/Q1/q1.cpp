#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <queue>
#include <stack>

using namespace std;

/*
	Question 1, part 3: THe data structure that I used to implement the bipartite graph was adjancency list which I 
	implemented with the help of vectors of structure chemical. The running time complexity is O(V + E) where V is 
	the number of nodes and E is the number of edges of each node traversed. I implemented Breadth First Serch in 
	which I enqueued all the "chemicals" nodes into a queue and marked the nodes before removing them and adding its
	edges. If the node had the same color as its neighbouring node it was obvious that it was not a bipartite graph.

	If it was not a bipartite graph it would have an odd cycle. The method I used to print the odd cycle was by 
	storing all of the parents of the nodes "chemicals". In the isBipartite function I used had stored the nodes which 
	clashed with each other. Then using the parent array I backtracked until the clashing nodes had the same parent.
	The time complexity of printing the Cycle was O(N) where N was the number of nodes.

*/

struct edges {
	int src;
	int dest;
};

class chemicals
{
public:
	int nodename;
	vector<int> array1;  //storing edges
	string color;
	bool visited;

	chemicals(int x)
	{
		nodename = x;
		color = "";
		visited = false;
	};
};


bool isBipartite(vector<chemicals> &allChemicals, int &m, int &);
void TraverseUsingBFS(vector<chemicals> allChemicals,int m, int n, string &ans);


int main(int argc, char** argv)
{
	char* filename;
	if (argc == 2)
	{
		filename = argv[1];
		//cout<<filename;
	}
	
	vector<chemicals> allChemicals;
	vector<edges> AllEdges;

	ifstream data;
	data.open(filename);
	string tempString;
	data >> tempString;
	data >> tempString;

	stringstream geek(tempString);
	int numberOfNodes;
	geek >> numberOfNodes;
	UO

	int i = 0;

	while(!data.eof())
	{
		
		string temp1;
		data >> temp1;
		data >> temp1;

		string str;
		getline(data, str);

		stringstream ss;     
	    ss << str; 
	    int number;

	    chemicals chemical(i);
	    edges e;
	  
	   while (!ss.eof()) 
	   { 
	  
	        ss >> number;
	        chemical.array1.push_back(number);
	        e.src = i;
	        e.dest = number;
	        AllEdges.push_back(e);
	    }

	    allChemicals.push_back(chemical);
	    i++;
	}
	data.close();
	/////
	int m = -1;
	int n = -1;
	/////

	string ans = "";

	string out_string;
    stringstream ss1;



	if (isBipartite(allChemicals, m, n))
	{
		
		ans = ans + "Yes\n";
		for (int i = 0; i < allChemicals.size(); i++)
		{
			if (allChemicals[i].color == "red")
			{
				ss1 << allChemicals[i].nodename;
        		out_string = ss1.str();
				ans += out_string + " ";
				ss1.str("");
			}
		}

		ans += "\n";
 
		for (int i = 0; i < allChemicals.size(); i++)
		{
			if (allChemicals[i].color == "blue")
			{
				ss1 << allChemicals[i].nodename;
        		out_string = ss1.str();
				ans += out_string + " ";
				ss1.str("");
			}
		}
		ans += "\n";
	}

	else
	{
		ans += "No\n";
		TraverseUsingBFS(allChemicals, m, n, ans);	
	}
	cout<<ans<<endl;
}

bool isBipartite(vector<chemicals> &allChemicals, int &m, int &n)
{
	queue<chemicals> q;
	allChemicals[0].color = "blue";
	q.push(allChemicals[0]);
	
	while (!q.empty())
	{
		chemicals u = q.front();
		q.pop();

		for (int z = 0; z < u.array1.size(); z++)
		{
			int a = u.array1[z];
			if (allChemicals[a].color == "" && u.color == "blue")
			{
				allChemicals[a].color = "red";
				q.push(allChemicals[a]);
			}

			if (allChemicals[a].color == "" && u.color == "red")
			{
				allChemicals[a].color = "blue";
				q.push(allChemicals[a]);
			}

			if (allChemicals[a].color != "" && allChemicals[a].color == u.color)
			{	
				m = allChemicals[a].nodename;
				n = u.nodename;
				return false;
			}
		}
	
	}
	return true;
}

void TraverseUsingBFS(vector<chemicals> allChemicals,int m, int n, string &ans)
{
	queue<int> q1;
	stack<int> s1;
	//queue<int> finalq;

	//////////  Bfs ends here
	int parentArray[allChemicals.size()];

	for (int i = 0; i < allChemicals.size(); i++)
	{
		parentArray[i] = -99;
	}

	queue<chemicals> q;
	allChemicals[0].visited = true;
	q.push(allChemicals[0]);
	parentArray[0] = -1;

	while (!q.empty())
	{
		chemicals u = q.front();
		//cout<<u.nodename<<"->";
		q.pop();

		for (int z = 0; z < u.array1.size(); z++)
		{
			int a = u.array1[z];
			if (allChemicals[a].visited == false)
			{
				allChemicals[a].visited = true;
				q.push(allChemicals[a]);
				parentArray[a] = u.nodename;
			}
		}

		
	}

	/*
	for (int i = 0; i < allChemicals.size(); i++)
	{
		cout<<parentArray[i]<<" ";
	}
	cout<<endl;
	*/

	q1.push(m);
	s1.push(n);
	//cout<<m<<" "<<n<<endl;

	while (1)
	{
		m = parentArray[m];
		n = parentArray[n];
		//cout<<m<<" "<<n<<endl;

		q1.push(m);
		s1.push(n);
		

		if (parentArray[m] == parentArray[n])
		{
			if (parentArray[m] == -1 || m == n)
			{
				break;
			}
			else
			{
				q1.push(parentArray[m]);
				//cout<<parentArray[m]<<" ";
				s1.push(parentArray[n]);
				//cout<<parentArray[n];
				break;
			}
			
		}


	} 
	//cout<<endl;

	string out_string;
    stringstream ss1;

	int b = s1.size();
	for (int i = 0; i < b; i++)
	{
		ss1 << s1.top();
        out_string = ss1.str();
        ss1.str("");
        ans += out_string + "->";
		s1.pop();
	}
	
	int a = q1.size();
	int z = 0;
	ss1.str("");

	for (int i = 0; i < a; i++)
	{
		ss1 << q1.front();
        out_string = ss1.str();
        ss1.str("");
        ans += out_string;
		q1.pop();
		if (z < a - 1)
		{
			//cout<<"->";
			ans += "->";
		}
		z++;
		
	}
	
}



