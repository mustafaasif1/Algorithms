#include <iostream> 
#include <string.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <queue>
#include <stack>
#include <list>

using namespace std; 

/*
    The code first checks if there is a cycle. If a cycle is present then if prints out the cycle in O(V + E) where V is the number
    of vertices and E is the number of Edges. If there isn't a cycle then it sorts topologically. 

*/

class AngryPeople 
{ 
    int V;   
    list<int> *edges; 
    
public: 
    AngryPeople(int V); 
    void TopSort(string &ans); 
    bool IsThisACycle(); 
    bool BreadthFirstSearch(int s, string &ans);
    bool HelpingInDFS(int v, int visit[]); 
    void AddingAnEdge(int v, int w); 
    void HelpingTopSort(int v, bool vst[], stack<int> &stacker); 
    
}; 
  
AngryPeople::AngryPeople(int V) 
{ 
    edges = new list<int>[V]; 
    this->V = V; 
   
} 
  
void AngryPeople::HelpingTopSort(int v, bool vst[], stack<int> &stacker) 
{ 
    
    vst[v] = true; 
  
    list<int>::iterator i;

    i = edges[v].begin();

    while (i != edges[v].end())
    {
        if (!vst[*i]) 
        {
            HelpingTopSort(*i, vst, stacker); 
        }
        ++i;
    }
   
    stacker.push(v); 
} 

void AngryPeople::AddingAnEdge(int v, int w) 
{ 
    edges[v].push_back(w); 
}

bool AngryPeople::HelpingInDFS(int u, int visit[]) 
{ 
   
    visit[u] = 1; 
  
 
    list<int>::iterator i;
    i = edges[u].begin();

    while (i != edges[u].end())
    { 
        int v = *i;  
  
        
        if (visit[v] == 1) 
        {
          return true; 
        }
  
       
        if (visit[v] == 0 && HelpingInDFS(v, visit)) 
        {
          return true; 
        }

        ++i;
    } 
  
    visit[u] = 2; 
    return false; 
}
  

void AngryPeople::TopSort(string &ans) 
{ 
    stack<int> Stack; 
    
    int i = 0;

    bool *vst = new bool[V];

    while (i < V)
    {
        vst[i] = false; 
        i++;
    }  
    
    i = 0;

    while (i < V)
    {
        if (vst[i] != true) 
        {
            HelpingTopSort(i, vst, Stack);
        }
        i++;
    }
       
    string out_string;
    stringstream ss1;

    while (Stack.empty() == false) 
    { 
        ss1 << Stack.top();
        out_string = ss1.str();
        ans += out_string + " ";
        ss1.str("");  
        Stack.pop(); 
    } 
} 
  

bool AngryPeople::IsThisACycle() 
{ 
    
    int *visit = new int[V]; 
    for (int i = 0; i < V; i++) 
    {
        visit[i] = 0; 
    }
  
    for (int i = 0; i < V; i++) 
    {
        if (visit[i] == 0) 
        {
           if (HelpingInDFS(i, visit) == !false)
           {
                return true; 
           } 
              
        }
    }
  
    return false; 
}

bool AngryPeople::BreadthFirstSearch(int s, string &ans) 
{ 
    int parentArray[V];
    int ss = s;

    for (int i = 0; i < V; i++)
    {
        parentArray[i] = -99;
    }

   
    bool *vst = new bool[V]; 
    
    for(int i = 0; i < V; i++) 
        vst[i] = false; 
  
   
    list<int> queue; 
  
    
    vst[s] = true; 
    queue.push_back(s);
    parentArray[s] = -1; 
  
    list<int>::iterator i; 
    int last = -99;
    
    int ab = 0;
    while(!queue.empty()) 
    { 
       
        s = queue.front(); 
        
        queue.pop_front(); 
       
        for (i = edges[s].begin(); i != edges[s].end(); ++i) 
        { 
           
            if (!vst[*i]) 
            { 
                vst[*i] = !false; 
                queue.push_back(*i); 
                parentArray[*i] = s;
            } 

            if (vst[*i] && *i == ss) 
            { 
                last = s;
                break;
            } 

        } 
        
    } 

    stack<int> stack1;
    string out_string;
    stringstream ss1;
    
    if (last == -99)
    {
        return 0;
    }
    else
    {
   
        stack1.push(ss);
        while (last != -1)
        {  
            stack1.push(last);
            last = parentArray[last]; 
        }

        int z = 0; 
        int size1 = stack1.size();
        for (int i = 0; i < size1; i++)
        {
            ss1 << stack1.top();
            out_string = ss1.str();
            ans += out_string;
            if (z < size1 - 1)
            {
                    ans += "->";
            }
            ss1.str("");
            stack1.pop();
            z++;
        }
        return 1;
        
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

    AngryPeople g2(numberOfNodes);
   
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

    string ans = "";
    
    if (g2.IsThisACycle()) 
    {
        ans += "No\n";
        int i2 = 0;
        while(1)
        {
            if (g2.BreadthFirstSearch(i2, ans) == true)
            {
                break;
            }
            i2++;
        }    
    }

    else
    {
        ans += "Yes\n";
        g2.TopSort(ans);
    }
    
    cout<<ans<<endl;
    return 0; 
} 
