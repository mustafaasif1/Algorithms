#include <bits/stdc++.h> 
using namespace std; 
  
int main(int argc, char** argv) 
{ 

	char* filename;
    if (argc == 2)
    {
        filename = argv[1];
    }

    ifstream data;
    data.open(filename);
    string str;
    getline(data, str);
    int n = str[2] - '0';
    getline(data, str);
    int k = str[2] - '0';
    int a[n]; 
    int b[n];

    pair<int, int> adj[n];

    
    for (int i = 0; i < n; i++)
    {
    	getline(data,str);
    	stringstream ss;     
        ss << str; 
        string l;
        int x;
        int y;

        ss >> l;
        if (l[1] == 'a')
	    {	
	    	a[i] = -1 * (l[2] - '0' + 1);
	    	x = a[i];
	    }
	    else 
	    {
	        a[i] = (l[1] - '0' + 1);
	        x = a[i];
	    }

	    ss >> l;
        if (l[1] == 'a')
	    {	
	    	b[i] = -1 * (l[2] - '0' + 1);
	    	y = b[i];
	    }
	    else 
	    {
	        b[i] = (l[1] - '0' + 1);
	        y = b[i];
	    }
	    
	    adj[i] = make_pair(x,y);
    }

    cout<<"No\n";
  
    return 0; 
} 