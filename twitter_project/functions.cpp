#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <cstring>
#include "functions.h"
#include "classes.h"
#include "hashT.h"
using namespace std;

int lineCounter(char *path1)
{
	string line;
	int counterOfLines=0;
	ifstream myfile(path1);
	if(myfile.is_open())
	{
		while(getline(myfile,line))
		{
			counterOfLines++;	
		}
		myfile.close();	
	}
	else
	{ 
		cout << "Unable to open!" << endl;
	}
	return counterOfLines;
}

void readConfig(char * path,int &k,int &hf,int &L)
{
	string line;
	ifstream myfile(path);
	string delims = " \n\t";
	vector <string> tokens1;
	if(myfile.is_open())
	{
		getline(myfile,line);
		tokens1=tokenize( line, delims);
		string a = tokens1[tokens1.size()-1];
		k = atoi((a).c_str());
		if(k==0) k=4;
		
		getline(myfile,line);
		tokens1=tokenize( line, delims);
		a = tokens1[tokens1.size()-1];
		hf = atoi((a).c_str());
		if (hf==0) hf = 4;
		
		getline(myfile,line);
		tokens1=tokenize( line, delims);
		a = tokens1[tokens1.size()-1];
		L = atoi((a).c_str());
		if(L==0) L=5;
		myfile.close();
	}
	else
	{
		cout << "Unable to open!" << endl;
	}
}

int lineCounter2(char *path1)
{
	string line;
	int counterOfLines=0;
	ifstream myfile(path1);
	if(myfile.is_open())
	{
		//getline(myfile,line); //h grammh tou radius
		while(getline(myfile,line))
		{
			counterOfLines++;	
		}
		myfile.close();	
	}
	else
	{ 
		cout << "Unable to open!" << endl;
	}
	return counterOfLines;
}
double Rfunction(char* path)
{
	double r=0.0;
	string line;
	ifstream myfile(path);
	string delims = " \n\t";
	vector <string> tokens1;
	if(myfile.is_open())
	{
		while(getline(myfile,line))
		{
			char p1[1000];
			const char * c = line.c_str();
			strcpy(p1,c);
			
			char* p = strstr(p1,"Radius");			
			if(p!=NULL)
			{
				tokens1=tokenize( line, delims);
				string a = tokens1[tokens1.size()-1];
				r = stod(a,NULL);	
			}
		}
		myfile.close();
	}
	else
	{
		cout << "Unable to open!" << endl;
	}
	return r;
}

int metricfunction(char* path)
{
	int metric=0;
	char* p = strstr(path,"cosine");			
	if(p!=NULL)
	{
		metric=2;	
	}
	char* pm = strstr(path,"euclidean");			
	if(pm!=NULL)
	{
		metric=1;	
	}
	return metric;
}
int mod1(long long int f1 , int M , int HTsize)//for lsh
{
	int f2,f;
	if(f1>0)
	{
		f2 = f1 % M;
	}
	else
	{
		f2 = (f1 % M + M) % M;
	}
	f = f2 % (HTsize/2);
	
	return f;
}

int mod2(long long int f1 , int M) //for hypercube
{
	int f2,f;
	if(f1>0)
	{
		f2 = f1 % M;
	}
	else
	{
		f2 = (f1 % M + M) % M;
	}
	f = f2 ;
	
	return f;
}

int convertBinaryToDecimal(long long n)
{
    int decimalNumber = 0, i = 0, remainder;
    while (n!=0)
    {
        remainder = n%10;
        n /= 10;
        decimalNumber += remainder*pow(2,i);
        ++i;
    }
    return decimalNumber;
}


vector<string> tokenize(const string& str, const string& delimiters){
    int prev = 0;
	int currentPos = 0;
	vector<string> tokens;

	// loop through string until we reach the end
	while((currentPos = str.find_first_of(delimiters, prev)) != string::npos){
		if(currentPos > prev){
			tokens.push_back(str.substr(prev, currentPos - prev));
		}
		prev = currentPos + 1;
	}
	// if characters are remaining, save to vector
	if(prev < str.length()){
		tokens.push_back(str.substr(prev, string::npos));
	}
	return tokens;
}

int vectorEquality(vector<double>a,vector<double>b)
{
	if(a == b)
	{
		return 1;		
	}
	else
	{	
		return -1;
	}
}

double calcEucledianDist(vector<double> elem,vector <double> queryElem)
{
	double res=0.0;
	vector<double>::iterator it1 = queryElem.begin();
	for(vector<double>::iterator it2 = elem.begin();it2 != elem.end(); ++it2)
	{
		double y = (*it2)-(*it1);
		double x = pow(y,2);
		res += x;
		++it1;
	}
	double result = sqrt(res);
	return result;
}

double cosine_similarity_vectors(std::vector<double> A, std::vector<double>B)
{
    double mul = 0.0;
    double d_a = 0.0;
    double d_b = 0.0 ;

    if (A.size() != B.size())
    {
        throw std::logic_error("Vector A and Vector B are not the same size");
    }

    // Prevent Division by zero
    if (A.size() < 1)
    {
        throw std::logic_error("Vector A and Vector B are empty");
    }

    std::vector<double>::iterator B_iter = B.begin();
    std::vector<double>::iterator A_iter = A.begin();
    for( ; A_iter != A.end(); A_iter++ , B_iter++ )
    {
        mul += *A_iter * *B_iter;
        d_a += *A_iter * *A_iter;
        d_b += *B_iter * *B_iter;
    }

    if (d_a == 0.0f || d_b == 0.0f)
    {
        return 0;
    }

    double ti = mul / (sqrt(d_a) * sqrt(d_b));
	return ti;
}

double cosine_distance_vectors(std::vector<double> A, std::vector<double>B)
{
    double mul = 0.0;
    double d_a = 0.0;
    double d_b = 0.0 ;

    if (A.size() != B.size())
    {
        throw std::logic_error("Vector A and Vector B are not the same size");
    }

    // Prevent Division by zero
    if (A.size() < 1)
    {
        throw std::logic_error("Vector A and Vector B are empty");
    }

    std::vector<double>::iterator B_iter = B.begin();
    std::vector<double>::iterator A_iter = A.begin();
    for( ; A_iter != A.end(); A_iter++ , B_iter++ )
    {
        mul += *A_iter * *B_iter;
        d_a += *A_iter * *A_iter;
        d_b += *B_iter * *B_iter;
    }

    if (d_a == 0.0f || d_b == 0.0f)
    {
        return 0;
    }

    double ti = mul / (sqrt(d_a) * sqrt(d_b));
	return (1.0-ti);
}

int hammingDistance(int n1, int n2) 
{ 
    int x = n1 ^ n2; 
    int setBits = 0; 
  
    while (x > 0) { 
        setBits += x & 1; 
        x >>= 1; 
    } 
  
    return setBits; 
} 

int hdCounterFun(int hashTableSize,int index,int hdDist)//count the NN with hdDist hamming distance
{
	int hdCounter=0;
	for(int c=0;c<hashTableSize;c++)	
	{
		if(hammingDistance(index,c)==hdDist)	
		{
			hdCounter++;
		}	
	}
	return hdCounter;
}



