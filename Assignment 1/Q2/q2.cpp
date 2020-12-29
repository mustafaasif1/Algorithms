#include <iostream> 
#include <string.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <queue>
#include <list>

/*

    In this question I used a class Roads which contained the number of nodes and the edges that are stored in a list. 
    A function called BrgHelper was used which step by step removed an edge from the graph and connected if the graph 
    was still connected using the BrgHelper function which used vector and traversed all the nodes. If every node was reached
    then the edge was not a vulnerable edge or bridge. The DFS used in the algorithm had a running time complexity of O(V+E).
    d[] stores the discovery time of visited vertices and p1 stores the parent vertices.
    
*/

using namespace std; 

struct allBrgs{
    int src;
    int dest;
};

vector<allBrgs> Brgs;

class Roads
{
        int V; 
        list<int> *edges; 
        
    public:
        Roads(int V); 
        void Brg(); 
        void AddingAnEdge(int v, int w);
        void BrgHelper(int v, bool vst[], int d[], int l[], int p1[]); 
        
      
};
 
Roads::Roads(int V)
{
    edges = new list<int> [V];
    this->V = V;
}
 

 
void Roads::BrgHelper(int u, bool vst[], int d[], int l[], int p1[])
{
   
    vst[u] = true;
    static int time = 0;

    list<int>::iterator i;

    l[u] = d[u] = ++time;
    i = edges[u].begin();

    while (i != edges[u].end())
    {
        int v = *i; 
       
        if (!vst[v])
        {
            p1[v] = u;

            BrgHelper(v, vst, d, l, p1);
            
            l[u] = min(l[u], l[v]);
           
            if (l[v] > d[u])
            {          
                allBrgs a;
                a.src = u;
                a.dest = v;

                Brgs.push_back(a);

            }

        }
       
        else if (v != p1[u])
        {
            l[u] = min(l[u], d[v]);
        }
        ++i;
    }
}

void Roads::AddingAnEdge(int v, int w)
{
    edges[v].push_back(w);
}
 

void Roads::Brg()
{
    int *d = new int[V];
    bool *vst = new bool[V];
    
    int *p1 = new int[V];
    int *l = new int[V];
 
    int x = 0;
    while (x < V)
    {
        vst[x] = false;
        p1[x] = -1;
        x++;
    }
    x = 0;
 
    while (x < V)
    {
        if (vst[x] != true)
        {
            BrgHelper(x, vst, d, l, p1);
        }
        x++;
    }
    
        
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
    int numberOfNodes;
    geek >> numberOfNodes;

    Roads g2(numberOfNodes);

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
            g2.AddingAnEdge(i,number);    
       }
       i++;
    }
    
    data.close();
    

    g2.Brg();

    string final_answer;

    string out_string;
    stringstream ss1;
    
    //out_string = ss1.str();   

    if (Brgs.empty())
    {
        final_answer += "0";
    }
    else
    {
        ss1 << Brgs.size();
        out_string = ss1.str();
        final_answer += out_string += "\n";
        ss1.str("");

        for (int i = 0; i < Brgs.size(); i++)
        {
            ss1 << Brgs[i].src;
            out_string = ss1.str();
            final_answer += "(" + out_string + ",";
            ss1.str("");

            ss1 << Brgs[i].dest;
            out_string = ss1.str();
            final_answer += out_string + ")\n";
            ss1.str("");
        }
    }

    cout<<final_answer<<endl;
    return 0; 
}

