 #include <bits/stdc++.h> 
#include<stdlib.h> 
#include<stdio.h> 
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <cmath>

using namespace std; 


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


struct Node 
{ 
    int data; 
    Node* left, *right;

    Node(int x)
    {
        data = x;
        left= right = NULL;
    } 
}; 

void printGivenLevel(Node* root, int level);  
int height(Node* node); 
 
Node* insertLevelOrder(int arr[], Node* root,int i, int n) 
{
    if (i < n) 
    { 
        Node* temp = new Node(arr[i]);  
        root = temp;
        root->left = insertLevelOrder(arr, root->left, 2 * i + 1, n); 
        root->right = insertLevelOrder(arr, root->right, 2 * i + 2, n); 
    } 
    return root; 
} 


void printLevelOrder(Node* root)  
{  
    int h = height(root);  
    int i;  
    for (i = 1; i <= h; i++)
    {
        printGivenLevel(root, i);
    }      
}  
  
void printGivenLevel(Node* root, int level)  
{  
    if (root == NULL)  
        return;  
    if (level == 1)  
        cout << root->data << " ";  
    else if (level > 1)  
    {  
        printGivenLevel(root->left, level-1);  
        printGivenLevel(root->right, level-1);  
    }  
}  
  

int height(Node* node)  
{  
    if (node == NULL){
        return 0;  
    }     
    else
    {  
        int left_height = height(node->left);  
        int right_height = height(node->right);  
  
        if (left_height > right_height)
        {
            return(left_height + 1);  
        } 
            
        else 
        {
            return(right_height + 1);
        }  
    }  
} 

void readInput(int* &temp, char* fileName, int &size)
{
	ifstream file;
	file.open(fileName);

	string temp2;
	file >> temp2;
	file >> temp2;
	size = (pow(2,StringToInt(temp2)+1)) - 1;
	temp = new int[size];


	for (int i = 0; i < size; i++)
	{
		int x;
		file >> x;
		temp[i] = x;
	}
}
  
int main(int argc, char** argv) 
{ 
	char* filename;
	filename = argv[1];
	int *temp;
	int n;
	readInput(temp, filename, n);
	int arr[n];
	for (int i = 0; i < n; i++)
    {
    	arr[i] = temp[i];
    }
    Node* root = insertLevelOrder(arr, root, 0, n); 
    printLevelOrder(root);
    cout<<endl;
}

//Binary tree has been made from the inputs