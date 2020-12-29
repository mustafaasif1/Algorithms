#include <iostream>
#include <vector>
#include <cstdlib>
#include <time.h>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>


/*
	Mustafa Asif
	21100042
	
	In this algorithm I created an array of size n. I then broke the array into equal sizes. These equal sizes were then passed recursively
	into the function. The base case of the recursive function "RecursionAlgorithms" returns the value when the size of the array is equal 
	to 1. The recursive function backtracks and compares this value to its sibling function. This comparison takes place in O(n) its the 
	recusive function takes place in O(logn) time. The total complexity is hence O(nlogn) 

	The recurence relation is: 
	T(1) = c
	T(n) = 2T(n/2) + nc
	T(n/2) = 2(2T(n/4) + (n/4)*c) + n*c
	If we solve the further we get T(n) = O(nlogn)

*/

using namespace std;

int Totaleft_count = 0;

string answer1 = "";
string answer2 = "";

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

bool decode(int x, int y);
int Counting(int* array1, int n, int begin, int z);

int Counting(int* array1, int n, int begin, int z)
{
	int x = 0;
	int i = 0;

	while (i < begin + n)
	{
		x += (decode(array1[i],z)) ? 1 : 0;
		++i;
	}
	
	return x;
}

bool decode(int x, int y)
{
	return (x==y) ? true : false;
}


int RecursionAlgorithms(int* array1, int size, int begin){
	
	// Base Case
	if (size == 1)
	{
		return array1[begin];
	}

	int l = RecursionAlgorithms(array1, size/2, begin);
	int r = RecursionAlgorithms(array1, size-size/2, begin+size/2);

	if (r == -1)
	{
		int count = Counting(array1,size,begin,l);
		
		if (count > size/2)
		{
			return l;
		}
		else
		{
			return -1;
		}
	}

	if (1)
	{
		if (l == -1)
		{
			int count = Counting(array1,size,begin,r);
			
			if (count > size/2)
			{
				return r;
			}
			else
			{
				return -1;
			}
		}
	}
	
	if (decode(l,r)) 
	{
		return l;
	} 
	
	int left_count = Counting(array1,size,begin,l);
	int right_count = Counting(array1,size,begin,r);
	
	if (left_count > size/2)
	{
		return l;
	} 

	else if (right_count > size/2)
	{
		return r;
	}

	return -1;
	
}

int Final(int* array1, int n){
	
	int x = RecursionAlgorithms(array1,n,0);

	if (x == -1)
	{
		answer1 += "Failure\n";
	} 
	else 
	{	answer1 += "Success\n";

		answer2 = "Dominant Species Indices";

		int i = 0;
		while (i<n)
		{
			if (decode(array1[i],x))
			{
				answer2 += " " + intToString(i);
				Totaleft_count++;
			}
			++i;
		}
		answer2 += '\n';
	}
}


int main(int argc, char** argv){
	
	char* filename;
	filename = argv[1];

	ifstream file;
	file.open(filename);
	string s;

	file >> s;
	file >> s;
	int n = StringToInt(s);
	file >> s;
	file >> s;
	int m = StringToInt(s);

	int array1[n];

	for (int i = 0; i < n; ++i)
	{
		int a;
		file >> a;
		array1[i] = a;
	}

	Final(array1, n);

	string FinalAnswer = "";
	string answer3 = "Dominant Species Count "+ intToString(Totaleft_count) + '\n';
	FinalAnswer += answer1 + answer3 + answer2;
	cout<<FinalAnswer;

}