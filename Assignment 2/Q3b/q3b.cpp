#include <iostream>
#include <list>
#include <vector>
#include <queue>
#include <cstdio>
#include <sstream>
#include <fstream>
using namespace std; 

string ans = "";
string intToString(int a)
{
    ostringstream str1; 
    str1 << a; 
    return str1.str(); 
}
  
typedef pair<int, int> EdgeEW; 

struct Node{
    int source;
    int dest;
    int weight;
};

class Graph 
{ 
    int V; 
    list< pair<int, int> > *Edges; 
    vector<Node> MinimumSpanningTree;
  
public: 
    Graph(int V);
    void addEdge(int u, int v, int w); 
    void MinimumSpanning1(int &z);
    void MinimumSpanning2(int &z); 
    void removeEdge(int x, int y);
    int Sum(int x, int y);
}; 
  

Graph::Graph(int V) 
{ 
    this->V = V; 
    Edges = new list<EdgeEW> [V]; 
} 
  
void Graph::addEdge(int u, int v, int w) 
{ 
    Edges[u].push_back(make_pair(v, w)); 
} 
  
void Graph::MinimumSpanning1(int &z) 
{ 
    z = 0;
    priority_queue< EdgeEW, vector <EdgeEW> , greater<EdgeEW> > PriorityQueue; 
    int src = 0; 
    vector<bool> Present(V, false); 
    vector<int> parent(V, -1); 
    vector<int> Weights(V, 10000); 
    PriorityQueue.push(make_pair(0, src)); 
    Weights[src] = 0; 
  
    while (!PriorityQueue.empty()) 
    { 
        int u = PriorityQueue.top().second; 
        PriorityQueue.pop(); 
        Present[u] = true;  
        list< pair<int, int> >::iterator i; 
        for (i = Edges[u].begin(); i != Edges[u].end(); ++i) 
        { 
            int v = (*i).first; 
            int weight = (*i).second; 
            if (Weights[v] > weight && Present[v] == false ) 
            { 
                Weights[v] = weight; 
                PriorityQueue.push(make_pair(Weights[v], v)); 
                parent[v] = u; 
            } 
        } 
    } 
  	     
    int ab = 0;
    for (int i = 1; i < V; ++i)
    {
        Node Temp;
        if (ab != 0)
        {
            ans += " ";
        } 
        ans += "(" + intToString(parent[i]) + "," + intToString(i) + ")";
        int a = Sum(parent[i], i);
        z += a; 
        Temp.source = parent[i];
        Temp.dest = i;
        Temp.weight = a;
        MinimumSpanningTree.push_back(Temp);
        ab = 1;
    }   	
} 

void Graph::MinimumSpanning2(int &z) 
{ 
    z = 0;
    priority_queue< EdgeEW, vector <EdgeEW> , greater<EdgeEW> > PriorityQueue; 
    int src = 0; 
    vector<bool> Present(V, false); 
    vector<int> parent(V, -1); 
    vector<int> Weights(V, 10000); 
    PriorityQueue.push(make_pair(0, src)); 
    Weights[src] = 0; 
  
    while (!PriorityQueue.empty()) 
    { 
        int u = PriorityQueue.top().second; 
        PriorityQueue.pop(); 
        Present[u] = true;  
        list< pair<int, int> >::iterator i; 
        for (i = Edges[u].begin(); i != Edges[u].end(); ++i) 
        { 
            int v = (*i).first; 
            int weight = (*i).second; 
            if (Weights[v] > weight && Present[v] == false ) 
            { 
                Weights[v] = weight; 
                PriorityQueue.push(make_pair(Weights[v], v)); 
                parent[v] = u; 
            } 
        } 
    } 
         
    int ab = 0;
    for (int i = 1; i < V; ++i)
    {
        Node Temp;
        if (ab != 0)
        {
            ans += " ";
        } 
        ans += "(" + intToString(parent[i]) + "," + intToString(i) + ")";
        int a = Sum(parent[i], i);
        z += a; 
        Temp.source = parent[i];
        Temp.dest = i;
        Temp.weight = a;
        MinimumSpanningTree.push_back(Temp);
        ab = 1;
    }       
}


int Graph::Sum(int x, int y)
{
        pair<int, int> p1;
        list< pair<int, int> >::iterator z; 
        for (z = Edges[x].begin(); z != Edges[x].end(); ++z) 
        {    
            int v = (*z).first; 
            if (v == y)
            {
                p1 = *z;
                return p1.second;
            }
        }
}

void Graph::removeEdge(int x, int y)
{
	pair<int, int> p1;
	list< pair<int, int> >::iterator i; 
    for (i = Edges[x].begin(); i != Edges[x].end(); ++i) 
    {    
        int v = (*i).first; 
        if (v == y)
        {
        	p1 = *i;
        }
    } 

    Edges[x].remove(p1); 
} 

  
int main(int argc, char** argv) 
{ 
 
	char* filename;
	if (argc == 2)
	{
		filename = argv[1];
	}

	ifstream data;
	data.open(filename);
	string tempString;
	data >> tempString;
	data >> tempString;

	stringstream geek(tempString);
	int V;
	geek >> V;
    
    Graph g1(V);

    int i = 0;

    for (int i = 0; i < V; i++)
    {
    	string temp1;
        data >> temp1;
        data >> temp1;

        string str;
        getline(data, str);
        if (str.empty())
        {
            i++;
            continue;
        }

        stringstream ss;     
        ss << str; 
        string l;

       while (!ss.eof()) 
       { 
            ss >> l;
            g1.addEdge(i,l[0] - '0', l[2] - '0');    
       }
    }
    
    string str;
    getline(data, str);
    stringstream sss;     
    sss << str; 
    string l;
    sss >> l;
    int a = l[1] - '0';
    int b = l[3] - '0';
    sss >> l;
    int weight = l[0] - '0';


    data.close();
    
    ans+= "MST1: ";
    int z = 0;
    g1.MinimumSpanning1(z);
    ans+="\n";
    ans+= "Sum MST1: " + intToString(z) + "\n";
    g1.addEdge(a, b, weight);
    g1.addEdge(b, a, weight);
    ans+= "Edge Added: (" + intToString(a) + "," + intToString(b) + ")\nMST2: ";
    g1.MinimumSpanning2(z);
    ans+= "\nSum MST2: " + intToString(z) + "";
    cout<<ans;
    return 0; 
}

