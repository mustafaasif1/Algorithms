#include <bits/stdc++.h> 
#include<stdlib.h> 
#include<stdio.h> 
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

/*
    Mustafa Asif
    21100042

    The time complexity of the algorithm is O(nlogn) 

*/

int **inversions1;

struct store{
    int indexes;
    int values;
};

class data{
    public:
    int size;
    int *array1ay1;
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

int merge(store array1[], store temp[], int l, int mid, int r); 
int _mergeSort(store array1[], store temp[], int l, int r); 

int _mergeSort(store array1[], store temp[], int l, int r) 
{ 
    int mid = 0; 
    int inversions1_count = 0;

    if (r > l) 
    { 
        mid = (r + l) / 2; 
        inversions1_count = _mergeSort(array1, temp, l, mid); 
        inversions1_count += _mergeSort(array1, temp, mid + 1, r); 
        inversions1_count += merge(array1, temp, l, mid + 1, r); 
    } 
    return inversions1_count; 
} 

int mergeSort(store array1[], int array1ay_size) 
{
    store temp[array1ay_size];
    return _mergeSort(array1, temp, 0, array1ay_size - 1); 
}

int merge(store array1[], store temp[], int l, int mid, int r) 
{ 
    int i, j, k; 
    int inversions1_count = 0; 
  
    j = mid; 
    i = l;
    k = l;

    int z = mid - 1;
    while ((j <= r) && (i <= z)) 
    { 
        if (array1[i].values <= array1[j].values) 
        { 
            temp[k].values = array1[i].values;
            temp[k].indexes = array1[i].indexes;
            k++;
            i++;
        } 
        else 
        { 
            temp[k].values = array1[j].values;
            temp[k].indexes = array1[j].indexes;

            for (int x = i; x < mid; x++)
            {
                if (array1[x].values > array1[j].values * 2)
                {
                    inversions1[array1[j].indexes][array1[x].indexes] = 1;
                    inversions1_count++;
                }
            }
            j++;
            k++;  
        } 
    } 

    for (; i <= mid - 1; i++)
    {
        temp[k].values = array1[i].values; 
        temp[k].indexes = array1[i].indexes; 
        k++;
    }

    for (;j <= r; j++)
    {
        temp[k].values = array1[j].values; 
        temp[k].indexes = array1[j].indexes; 
        k++;
    }

    for (i = l; i <= r; i++) 
    {
        array1[i].values = temp[i].values;
        array1[i].indexes = temp[i].indexes; 
    }
  
    return inversions1_count; 
} 
  
int main(int argc, char** argv) 
{   
    char* filename;
    filename = argv[1];
    
    ifstream file;
    file.open(filename);

    string temp;
    file >> temp;
    file >> temp;
    int n = StringToInt(temp);
    
    store array1[n];

    inversions1 = new int*[n];
    for (int i = 0; i < n; i++)
    {
        inversions1[i] = new int[n];
    }


    for (int i = 0; i < n; i++)
    {
        int x;
        file >> x;
        array1[i].values = x;
        array1[i].indexes = i;
    }

    int ans = mergeSort(array1, n); 

    string ans2 = "";
    string finalAns = "";
    bool found = false;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (inversions1[i][j] == 1)
            {
                found = true;
                ans2 += "(" + intToString(i) + "," + intToString(j) + ")";  
            }
        }
        if (found)
        {
            ans2 += '\n';
        }
        found = false;
    }

    finalAns = "Failed Trial " + intToString(ans) + '\n' + ans2;

    cout<<finalAns;
    return 0; 
} 