#include<iostream>
#include<fstream>
#include<vector>
#include<stdlib.h>
#include <utility>
#include <sstream>
#include <iomanip>

/*

    Mustafa Asif
    21100042

    The approach I used for this problem was by first making a n*n matrix, initially filling is with garbage values. Then I
    marked -1 on the location which was given in the input. Ater that I divided the matrix into 4 quadrants each time, until 
    I'm left with the base condition, which is 2*2 matrix. I marked the quadrants which were not previously marked with x.
    Through recusrion I was able to populate the whole matrix with values.

    The recurrence realtion for this agorithm is:
    


*/

using namespace std;

// Global Variables
vector< vector<int> > Output;
int x = 0;

struct TakingInput
{
    int** matrix;
    int n;
    int x;
    int y;
    
};

struct Coordinates {
    int X_coordinate;
    int Y_coordinate;

    Coordinates(){};
    Coordinates(int x, int y)
    {
        X_coordinate = x;
        Y_coordinate = y;
    };

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


void Boomerang(TakingInput* Input, Coordinates begin, Coordinates finish, Coordinates fixed){
    

    // It wil enter this condition when a two by two matrix is left. This is the base condition
    if ((finish.X_coordinate - begin.X_coordinate ) == 1)
    {
        for (int i = begin.X_coordinate; i <= finish.X_coordinate; i++)
        {
            for (int j = begin.Y_coordinate; j <= finish.Y_coordinate; ++j)
            {
                if (i == fixed.X_coordinate && j == fixed.Y_coordinate)
                {
                    continue;
                } 
                else 
                {
                    //This loop will run 4 times and insert x at 3 locations
                    Input->matrix[i][j] = x;
                    Output[x].push_back(i);
                    Output[x].push_back(j);
                }
            }
        }
        x+=1;
        return;

    } 
    else 
    {
        int MidX = (finish.X_coordinate - begin.X_coordinate)/2 + begin.X_coordinate;
        int MidY = (finish.Y_coordinate - begin.Y_coordinate)/2 + begin.Y_coordinate;

        Coordinates Firstbegin(begin.X_coordinate,begin.Y_coordinate);
        Coordinates Firstfinish(MidX,MidY);
        Coordinates Secondbegin(MidX+1,MidY+1);
        Coordinates Secondfinish(finish.X_coordinate,finish.Y_coordinate);
        Coordinates Thirdbegin(begin.X_coordinate,MidY+1);
        Coordinates Thirdfinish(MidX,finish.Y_coordinate);
        Coordinates Fourthbegin(MidX+1,begin.Y_coordinate);
        Coordinates Fourthfinish(finish.X_coordinate,MidY);

        int a;

        // This checks where the fixed number is in the quadrant
        if (fixed.X_coordinate > MidX)
        {
            if (fixed.Y_coordinate > MidY)
            {
                a = 2;
            }
            else  
            {
                a = 4;
            }
        } 

        else
        {
            if (fixed.Y_coordinate > MidY)
            {
                a = 3;
            }
            else  
            {
                a = 1;
            }
        }

        Coordinates FirstFixed(Firstfinish.X_coordinate, Firstfinish.Y_coordinate); 
        Coordinates SecondFixed(Secondbegin.X_coordinate, Secondbegin.Y_coordinate); 
        Coordinates ThirdFixed(MidX,MidY+1);
        Coordinates FourthFixed(MidX+1,MidY);
        

        switch(a)
        {
            case 1:
            {
                FirstFixed = fixed;
                Input->matrix[MidX][MidY+1] = x;
                Input->matrix[MidX+1][MidY+1] = x;
                Input->matrix[MidX+1][MidY] = x;
                
                Output[x].push_back(MidX+1);
                Output[x].push_back(MidY+1);
                Output[x].push_back(MidX);
                Output[x].push_back(MidY+1);
                Output[x].push_back(MidX+1);
                Output[x].push_back(MidY);
                x++;
                break;
            }
            case 2:
            {
                SecondFixed = fixed;
                Input->matrix[MidX][MidY+1] = x;
                Input->matrix[MidX][MidY] = x;
                Input->matrix[MidX+1][MidY] = x;
                
                Output[x].push_back(MidX);
                Output[x].push_back(MidY);
                Output[x].push_back(MidX);
                Output[x].push_back(MidY+1);
                Output[x].push_back(MidX+1);
                Output[x].push_back(MidY);
                x++;
                break;
            }
            case 3:
            {
                ThirdFixed = fixed;
                Input->matrix[MidX+1][MidY+1] = x;
                Input->matrix[MidX][MidY] = x;
                Input->matrix[MidX+1][MidY] = x;

                Output[x].push_back(MidX);
                Output[x].push_back(MidY);
                Output[x].push_back(MidX+1);
                Output[x].push_back(MidY+1);
                Output[x].push_back(MidX+1);
                Output[x].push_back(MidY);
                x++;
                break;
            }
            default:
            {
                FourthFixed = fixed;
                Input->matrix[MidX+1][MidY+1] = x;
                Input->matrix[MidX][MidY] = x;
                Input->matrix[MidX][MidY+1] = x;

                Output[x].push_back(MidX);
                Output[x].push_back(MidY);
                Output[x].push_back(MidX+1);
                Output[x].push_back(MidY+1);
                Output[x].push_back(MidX);
                Output[x].push_back(MidY+1);
                x++;
                break;
            }
        }

        Boomerang(Input,Firstbegin,Firstfinish,FirstFixed);
        Boomerang(Input,Secondbegin,Secondfinish,SecondFixed);
        Boomerang(Input,Thirdbegin,Thirdfinish,ThirdFixed);
        Boomerang(Input,Fourthbegin,Fourthfinish,FourthFixed);
    }
}



void readInput(TakingInput* Input, char* fileName){
    
    ifstream file;
    file.open(fileName);

    string temp;
    file >> temp;
    file >> temp;
    Input->n = StringToInt(temp);
    file >> temp;
    int a = temp[1] - '0';
    int b = temp[3] - '0';
    Input->x = a;
    Input->y = b;

    Input->matrix = new int*[Input->n];
    for (int i = 0; i < Input->n; ++i)
    {
        Input->matrix[i] = new int[Input->n];
    }
    Input->matrix[Input->x][Input->y] = -1;

    int TotalNumbers = (((Input->n)*(Input->n))/3);
    Output.resize(TotalNumbers);

    return;   
}

string PrintOutput()
{
    string ans = "";
    for (int i = 0; i < Output.size();i++)
    {

        ans += intToString(i);
        bool a = true;
        
        for (int j = 0; j < Output[i].size(); j++)
        {
            if (a == true)
            {
                ans += " (" + intToString(Output[i][j]) + ",";
            }
            else
            {

                ans += intToString(Output[i][j]) + ")";
            }
            a = !a;
            
        }
        ans+="\n";
    }
    return ans;
}

int main(int argc, char** argv){
    char* fileName;
    fileName = argv[1];
    TakingInput* Input = new TakingInput;
    readInput(Input, fileName);
    
    Coordinates a(0,0);
    Coordinates b(Input->n-1,Input->n-1);
    Coordinates c(Input->x,Input->y);
    Boomerang(Input, a, b, c);
    string ans = PrintOutput(); 
    cout<<ans;
}