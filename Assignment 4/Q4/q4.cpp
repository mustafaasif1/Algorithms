#include <iostream> 
#include <string.h> 
#include <fstream>
#include <vector>
using namespace std; 

vector<char> Ans;
vector<char> A1;
vector<char> B1;

void isInterleaved(string A, string B, string C) 
{ 
    
    int M = A.length();
    int N = B.length(); 


    bool **IL = new bool*[M + 1];

    for (int i = 0; i < M + 1; i++)
    {
    	IL[i] = new bool[N + 1];
    }

    for (int i = 0; i < M + 1; i++)
    {
    	for (int j = 0; j < N + 1; j++)
	    {
	    	IL[i][j] = false;
	    }
    }
  
    if ((M + N) != C.length()) {
        cout <<"INVALID"<< endl;
        return;
    }


    //IL[0][0] = true; 
  
    for (int i = 0; i <= M; ++i) 
    { 
        for (int j = 0; j <= N; ++j) 
        { 
            if (i == 0 && j == 0) 
                IL[i][j] = true; 
  
            
            // else if (i == 0) { 
            //     if (B[j - 1] == C[j - 1]) 
            //         IL[i][j] = IL[i][j - 1]; 
            // } 
  
            
            // else if (j == 0) { 
            //     if (A[i - 1] == C[i - 1]) 
            //         IL[i][j] = IL[i - 1][j]; 
            // } 
  
            else if (A[i - 1] == C[i + j - 1] && B[j - 1] != C[i + j - 1]) {
                IL[i][j] = IL[i - 1][j];
                // if (IL[i][j]== true)
                // {
                // 	cout<<" "<<A[i - 1];
                // }
                //cout<<"1:"<<A[i - 1]<<endl;
                //Ans.push_back('1');
                //A1.push_back(A[i - 1]);

                // if (IL[i][j]== true)
                // {
                //  cout<<" "<<A[i - 1];
                // }
                //cout<<"1:"<<A[i - 1]<<endl;
                //Ans.push_back('1');
                //A1.push_back(A[i - 1]);

            }
  
            // Current character of C matches with current character of B, 
            // but doesn't match with current character of A 
            else if (A[i - 1] != C[i + j - 1] && B[j - 1] == C[i + j - 1]) {
                IL[i][j] = IL[i][j - 1]; 
                //cout<<"2:"<<B[j - 1]<<endl;
                //Ans.push_back('2');
                //B1.push_back(B[j - 1]);
                // if (IL[i][j] == true)
                // {
                // 	cout<<" "<<B[j - 1];

                 //cout<<"2:"<<B[j - 1]<<endl;
                //Ans.push_back('2');
                //B1.push_back(B[j - 1]);
                // if (IL[i][j] == true)
                // {
                //  cout<<" "<<B[j - 1];
            }
  
            // Current character of C matches with that of both A and B 
            else if (A[i - 1] == C[i + j - 1] && B[j - 1] == C[i + j - 1]) {
                IL[i][j] = (IL[i - 1][j] || IL[i][j - 1]);
                // if (IL[i][j])
                // {
                // 	cout<<" "<<A[i - 1];
                // }
                //cout<<"1:"<<A[i - 1]<<endl;
                //Ans.push_back('2');
                //B1.push_back(B[j - 1]);

                 // if (IL[i][j])
                // {
                //  cout<<" "<<A[i - 1];
                // }
                //cout<<"1:"<<A[i - 1]<<endl;
                //Ans.push_back('2');
                //B1.push_back(B[j - 1]);
            }
        } 
    }

    // for (int i = 0; i <= M; ++i) 
    // { 
    //     for (int j = 0; j <= N; ++j) 
    //     { 
    //         cout<<IL[i][j]<<" ";
    //     }
    //     cout<<endl;
    // }

    // for (int i = 0; i <= M; ++i) 
    // { 
    //     for (int j = 0; j <= N; ++j) 
    //     { 
    //         cout<<IL[i][j]<<" ";
    //     }
    //     cout<<endl;
    // }



    if (IL[M][N])
    {
    	cout << "VALID";
    	int row = M;
    	int col = N;
    	while (row != -1 && col != -1)
    	{
    		// if (IL[row][col-1] == 1 && )
    		// {
    		// 	cout<<B[col-1];
    		// 	col--;
    		// }

            // if (IL[row][col-1] == 1 && )
            // {
            //  cout<<B[col-1];
            //  col--;
            // }
    		if (row != 0 || col != 0)
    		{
    			if (IL[row][col-1] == 1)
	    		{
	    			//cout<<B[col-1];
	    			A1.push_back(B[col-1]);
	    			A1.push_back('2');
	    			col--;
	    		}

	    		if (IL[row-1][col] == 1)
	    		{
	    			//cout<<;
	    			A1.push_back(A[row-1]);
	    			A1.push_back('1');
	    			row--;
	    		}
    		}

    		if (row == 0)
    		{
    			//cout<<B[col-1];
    			A1.push_back(B[col-1]);
    			A1.push_back('1');
	    		col--;
    		}

    		else if (col == 0)
    		{
    			//cout<<A[row-1];
    			A1.push_back(A[row-1]);
    			A1.push_back('1');
	    		row--;
    		}
    	}
    }
    else 
    {
        cout <<"INVALID"<< endl; 
    }
} 


int main(int argc, char** argv) 
{ 
   	char* filename = argv[1];
   	string a,b,c;
   	ifstream data;
	data.open(filename);
	data >> a;
	data >> b;
	data >> c;

	data.close();
	isInterleaved(a,b,c);

	int x = 0;
	int y = 0;

	for (int i = A1.size() - 3; i >= 1 ; i--)
	{
		
		if (A1[i] == '1')
		{	
			y = 0;
			if (x == 0)
			{
				cout<<"\n1:";
				x++;
			}
			cout<<A1[i-1];
			i--;
		}
		else
		{
			x = 0;
			if (y == 0)
			{
				cout<<"\n2:";
				y++;
			}
			cout<<A1[i-1];
			i--;
		}
	}
	

    return 0; 
} 