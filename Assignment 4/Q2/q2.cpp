#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <list>

using namespace std;

int **memo;

struct node
{
    int nodenumber;
    bool haslight;
    vector<int> children;
};

class Graph
{
    public:
    int V; 
    list<int> *edges;
    Graph(char* filename); 
    void AddingAnEdge(int v, int w);
    void printEdges();
    void printVertexCover();
      
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

Graph::Graph(char* filename)
{

    ifstream data;
    data.open(filename);
    string tempString;
    data >> tempString;
    data >> tempString;

    V = StringToInt(tempString);
    edges = new list<int> [V];

    //The number of nodes have been read and have been printed as an integer
    
    int i = 0;

    while(!data.eof())
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
        int number;

       while (!ss.eof()) 
       { 
            ss >> number;
            AddingAnEdge(i,number);    
       }
       i++;
    }
    
    data.close();
}

void Graph::AddingAnEdge(int v, int w)
{
    edges[v].push_back(w);
}

void Graph::printEdges()
{
    cout<<"n "<<V<<endl;
    list<int>::iterator i;
    for (int j = 0; j < V; j++)
    {
        cout<<j<<" :";
        for (i = edges[j].begin(); i != edges[j].end(); i++)
        {
            int x = *i;
            cout<<" "<<x;
        }
        cout<<endl;
    }
    
}

void Graph::printVertexCover() 
{ 
    bool visited[V]; 
    for (int i=0; i<V; i++) 
        visited[i] = false; 
  
    list<int>::iterator i; 
  
    for (int u=0; u<V; u++) 
    { 
        if (visited[u] == false) 
        { 
            for (i= edges[u].begin(); i != edges[u].end(); ++i) 
            { 
                int v = *i; 
                if (visited[v] == false) 
                { 
                     visited[v] = true; 
                     visited[u]  = true; 
                     break; 
                } 
            } 
        } 
    } 
    for (int i=0; i<V; i++) 
        if (visited[i]) 
          cout << i << " "; 
}

int Q2(node *node1, int n)
{
    if (node1[n].children.size() <= 0)
    {
        //memo[n][n] = 1;
        return 0;
    }
    
    int minLightFromChildren = 0;
    
    for (int i = 0; i < node1[n].children.size(); i++)
    {
        int x = node1[n].children[i];
        minLightFromChildren += Q2(node1, x);
    }
    
    int childrenWithLights = 0;

    for (int j = 0; j < node1[n].children.size(); j++)
    {
        int x = node1[n].children[j];
        if (node1[x].haslight == true)
        {
            childrenWithLights++;
            //memo[j][x] = 0;
        }
    }

    //cout<<"\n "<<childrenWithLights<<"\n";
    if (childrenWithLights < node1[n].children.size())
    {
        minLightFromChildren++;
        node1[n].haslight = true;
    }
    return minLightFromChildren;
}

int main(int argc, char** argv)
{
    char* filename = argv[1];
    Graph* graph = new Graph(filename);
    //graph->printEdges();
    
    node* node1 = new node[graph->V];

    list<int>::iterator j;
    for (int i = 0; i < graph->V; i++)
    {
        node1[i].nodenumber = i;
        node1[i].haslight = false;
        for (j = graph->edges[i].begin(); j != graph->edges[i].end(); j++) 
        { 
            int v = *j;
            if(i<v)
                node1[i].children.push_back(v);        
        } 
    }


    // This uses node1 to print out the nodes
    // for (int i = 0; i < graph->V; i++)
    // {
    //  cout<<node1[i].nodenumber<<":";
    //  //cout<<node1[i].haslight<<endl;
    //  for (int j = 0; j < node1[i].children.size(); j++)
    //  {
    //      cout<<" "<<node1[i].children[j];
    //  }
    //  cout<<endl;
        
    // }

    int **memo = new int*[graph->V + 1];
    for (int i = 0; i < graph->V + 1; i++)
    {
     memo[i] = new int[graph->V + 1];
    }

    int ab = Q2(node1, 0);
    cout<<"Minimum Lights "<<ab<<endl;
    int c = 0;
    cout<<"{";
    for (int i = 0; i < graph->V; i++)
    {
        if (node1[i].haslight == true) {
            cout<<node1[i].nodenumber;
            c++;
            if (ab != c)
            {
                cout<<", ";
            }
        }
        

    }
    cout<<"}"<<endl;
    return 0;
}