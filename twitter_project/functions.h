#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <vector>
#include <cstdlib>
#include <iterator>
#include <functional>
#include <cstring>
#include <algorithm>    
#include <cmath>
#include <numeric>


using namespace std;


int lineCounter(char* path1);//input file
void readConfig(char* path,int &k,int &hf,int &L);
int lineCounter2(char* path1); //query file
int mod1(long long int f1 , int M , int HTsize);//lsh
int mod2(long long int f1 , int M);//hypercube
int convertBinaryToDecimal(long long n);
vector <string> tokenize(const string& str, const string& delimiters);//tokenize a line
double Rfunction(char* path);//get radius from query file
int metricfunction(char* path); //get metric from input file
int vectorEquality(vector<double> a,vector<double>b);
double calcEucledianDist(vector<double> elem,vector <double> queryElem);
double cosine_similarity_vectors(std::vector<double> A, std::vector<double>B);
double cosine_distance_vectors(std::vector<double> A, std::vector<double>B);
int hammingDistance(int n1, int n2);
int hdCounterFun(int hashTableSize,int index,int hdDist);
#endif
