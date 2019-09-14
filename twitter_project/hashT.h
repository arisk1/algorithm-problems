#ifndef HASHT_H
#define HASHT_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <cstring>
#include <random>
#include <chrono>
#include <cmath>

using namespace std;

class hashTable
{

	private:
		vector <Elements*> *hTable;
		int hashtablesize;
	public:
		hashTable(int size);
		void insertHT(Elements *&elem,int pos);
		void clearVec(int pos);
		void reinsertHT(Elements *&elem,int pos);
		void printHT(int hashTableSize,hashTable *hashTable1);
		vector <Elements*> getVector(int pos);		
		~hashTable();
};

int hashF(default_random_engine &e,int numOfDim,int w,int k,Elements *data,int HTsize,vector<gElements> &gVec,vector<double> &vs,vector<double> &ts);//euclidean lsh
int ghashF(default_random_engine &e,int numOfDim,int w,int k,gElements *data,int HTsize,vector<gElements> &gVec,vector<double> &vs,vector<double> &ts);//euclidean lsh
int hashFHC(default_random_engine &e,int numOfDim,int w,int k,Elements *data,int HTsize,vector<gElements> &gVec,vector<double> &vs,vector<double> &ts);//euclideanHyperc
int ghashFHC(default_random_engine &e,int numOfDim,int w,int k,gElements *data,int HTsize,vector<gElements> &gVec,vector<double> &vs,vector<double> &ts);//euclideanHyperc
void TandV(default_random_engine &e,vector<double> &vs,vector<double> &ts,int k,int numOfDim,int w);//crete v's an t's for hashtable
void Ri1(default_random_engine &e,vector<double> &ris,int k,int numOfDim);//create r's for cosine method
int hashF2(int numOfDim,int k,Elements *data,int HTsize,vector<gElements> &gVec,vector<double> &ris);//hashfuction for cosine lsh and hypercude
int ghashF2(int numOfDim,int k,gElements *data,int HTsize,vector<gElements> &gVec,vector<double> &ris);//hashfuction for cosine lsh and hypercude
#endif
