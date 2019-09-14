#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <cstring>
#include <random>
#include <chrono>
#include "functions.h"
#include "classes.h"
#include "hashT.h"

using namespace std;

hashTable::hashTable(int size)
{
	hTable = new vector<Elements*> [size];		
}

void hashTable::insertHT(Elements *&elem,int pos)
{
	hTable[pos].push_back(elem);	
}

void hashTable::clearVec(int pos)
{
	hTable[pos].clear();

}

void hashTable::reinsertHT(Elements *&elem,int pos)
{
	for(vector<Elements*>::iterator it = hTable[pos].begin();it != hTable[pos].end(); ++it)
	{
		(*it)=elem;
	}	
}

void hashTable::printHT(int hashTableSize,hashTable *hashTable1)
{
	for(int i=0;i<hashTableSize;i++)
	{
		vector<Elements*> px = hashTable1->getVector(i);
		int vectorSize1 = px.size();
		cout<< "---" << i <<"---"<<endl;
		for(int y=0;y<vectorSize1;y++)	
		{
			vector<double> aa = px[y]->getVectorElem();
			for(vector<double>::iterator it = aa.begin();it != aa.end(); ++it)
			{
					cout << (*it) ;
			}
			cout <<endl;
		}	
	}
}
vector <Elements*> hashTable::getVector(int pos)
{
	vector<Elements*> px=hTable[pos];
	return px;
}

hashTable::~hashTable()
{
	delete[] this->hTable;
	cout << "Deleted HashTable" << endl;
}


void TandV(default_random_engine &e,vector<double> &vs,vector<double> &ts,int k,int numOfDim,int w) //crete v's an t's for hashtable
{

	std::normal_distribution<double> distrN(0.0,1.0);
	std::uniform_real_distribution<double> distrR(0,w);
	for(int i = 0;i<k;i++)
	{
		for (int y=0;y<numOfDim;y++)
		{
			vs.push_back(distrN(e));
		}
		ts.push_back(distrR(e));
	}
}

void Ri1(default_random_engine &e,vector<double> &ris,int k,int numOfDim) //find r's for cosine method
{
	std::normal_distribution<double> distrN(0.0,1.0);
	for(int i = 0;i<k;i++)
	{
		for (int y=0;y<numOfDim;y++)
		{
			ris.push_back(distrN(e));
		}
	}
}

int hashF(default_random_engine &e,int numOfDim,int w,int k,Elements *data,int HTsize,vector<gElements> &gVec,vector<double> &vs,vector<double> &ts)//hashfunction lsh euclidean
{
	std::uniform_int_distribution<int> RiGenerator(1,w);
	vector <double> dt = data->getVectorElem();
	vector <double> gvector;
	long  double product = 0.0;
	double rslt;
	double result;
	vector <double>::iterator itv = vs.begin();
	for(int i = 0;i<k;i++)
	{
	//	vector <double>::iterator itv = vs.begin();
		vector <double>::iterator itt = ts.begin();
		for(vector<double>::iterator itp = dt.begin();itp != dt.end(); ++itp)
		{
			product = product + ((*itv) * (*itp));
			itv++;	
		}
	//	cout << "||" << product  << endl;
		rslt = ( product + (*itt) ) / w ;
		itt++;
		//cout << "f1" << rslt << endl; 
		result = floor(rslt);
		//cout << "f2" << result << endl;
		gvector.push_back(result);
	}

	//cout << vs.size() << endl; //exit(-1);

	gElements g1;
	g1.gsetValues(data->getID(),gvector); 
	gVec.push_back(g1);
	
	double f1=0;
	int M = (int)(pow(2.0,32.0)-5);
	for(vector<double>::iterator it = gvector.begin();it != gvector.end(); ++it)
	{
		f1 = f1 + (*it)*RiGenerator(e);
	}
	int fresult=mod1(f1,M,HTsize);
	//cout <<"l"<< f1 << endl;
	//cout <<"k"<< fresult << endl;
	return fresult;
}

int ghashF(default_random_engine &e,int numOfDim,int w,int k,gElements *data,int HTsize,vector<gElements> &gVec,vector<double> &vs,vector<double> &ts)//hashfunction lsh euclidean
{
	std::uniform_int_distribution<int> RiGenerator(1,w);
	vector <double> dt = data->ggetVectorElem();
	vector <double> gvector;
	long  double product = 0.0;
	double rslt;
	double result;
	vector <double>::iterator itv = vs.begin();
	for(int i = 0;i<k;i++)
	{
	//	vector <double>::iterator itv = vs.begin();
		vector <double>::iterator itt = ts.begin();
		for(vector<double>::iterator itp = dt.begin();itp != dt.end(); ++itp)
		{
			product = product + ((*itv) * (*itp));
			itv++;	
		}
	//	cout << "||" << product  << endl;
		rslt = ( product + (*itt) ) / w ;
		itt++;
		result = floor(rslt);
		gvector.push_back(result);
	}
	//cout << vs.size() << endl; //exit(-1);

	gElements g1;
	g1.gsetValues(data->ggetID(),gvector); 
	gVec.push_back(g1);
	
	double f1=0;
	int M = (int)(pow(2.0,32.0)-5);
	for(vector<double>::iterator it = gvector.begin();it != gvector.end(); ++it)
	{
		f1 = f1 + (*it)*RiGenerator(e);
	}
	int fresult=mod1(f1,M,HTsize);
//	cout << f1 << endl;
//	cout << fresult << endl;
	return fresult;
}

int hashFHC(default_random_engine &e,int numOfDim,int w,int k,Elements *data,int HTsize,vector<gElements> &gVec,vector<double> &vs,vector<double> &ts)//hashfunction hypercube euclidean
{
	//cout << "6" << endl;
	std::uniform_int_distribution<int> RiGenerator(1,w);
	vector <double> dt = data->getVectorElem();
	vector <double> gvector;
	long  double product = 0.0;
	double rslt;
	double result;
	int x1 = 2;
	//cout << "7" << endl;
	vector <double>::iterator itv = vs.begin();
	for(int i = 0;i<k;i++)
	{
	//	vector <double>::iterator itv = vs.begin();
		//cout << "7.1" << endl;
		vector <double>::iterator itt = ts.begin();
		for(vector<double>::iterator itp = dt.begin();itp != dt.end(); ++itp)
		{
			product = product + ((*itv) * (*itp));
			itv++;	
		}
		rslt = ( product + (*itt) ) / w ;
		itt++;
		result = floor(rslt);
		int f1=mod2(result,x1);
		//cout << f1 << endl;
		gvector.push_back(f1);
	}
	//cout << "8" << endl;
	gElements g1;
	g1.gsetValues(data->getID(),gvector); 
	gVec.push_back(g1);
	
	int binary1=0;
	int hl = (pow(10,k))/10;
	for(vector<double>::iterator it11 = gvector.begin();it11 != gvector.end(); ++it11)
	{
		binary1 = binary1 + (*it11)*hl;
		hl = hl / 10;
	//	cout << (*it11);
	}
	//cout << endl;
	int fresult= convertBinaryToDecimal(binary1);
	
//	cout << f1 << endl;
//	cout << fresult << endl;
	return fresult;
}

int ghashFHC(default_random_engine &e,int numOfDim,int w,int k,gElements *data,int HTsize,vector<gElements> &gVec,vector<double> &vs,vector<double> &ts)//hashfunction hypercube euclidean
{
	//cout << "6" << endl;
	std::uniform_int_distribution<int> RiGenerator(1,w);
	vector <double> dt = data->ggetVectorElem();
	vector <double> gvector;
	long  double product = 0.0;
	double rslt;
	double result;
	int x1 = 2;
	//cout << "7" << endl;
	vector <double>::iterator itv = vs.begin();
	for(int i = 0;i<k;i++)
	{
	//	vector <double>::iterator itv = vs.begin();
		//cout << "7.1" << endl;
		vector <double>::iterator itt = ts.begin();
		for(vector<double>::iterator itp = dt.begin();itp != dt.end(); ++itp)
		{
			product = product + ((*itv) * (*itp));
			itv++;	
		}
		rslt = ( product + (*itt) ) / w ;
		itt++;
		result = floor(rslt);
		int f1=mod2(result,x1);
		//cout << f1 << endl;
		gvector.push_back(f1);
	}
	//cout << "8" << endl;
	gElements g1;
	g1.gsetValues(data->ggetID(),gvector); 
	gVec.push_back(g1);
	
	int binary1=0;
	int hl = (pow(10,k))/10;
	for(vector<double>::iterator it11 = gvector.begin();it11 != gvector.end(); ++it11)
	{
		binary1 = binary1 + (*it11)*hl;
		hl = hl / 10;
	//	cout << (*it11);
	}
	//cout << endl;
	int fresult= convertBinaryToDecimal(binary1);
	
//	cout << f1 << endl;
//	cout << fresult << endl;
	return fresult;
}

int hashF2(int numOfDim,int k,Elements *data,int HTsize,vector<gElements> &gVec,vector<double> &ris)//hashfuctions for cosine  lsh and hypercube
{
	vector <double> dt = data->getVectorElem();
	vector <double> gvector;
	double result;
	long  double product = 0.0;
	vector <double>::iterator itr = ris.begin();
	for(int i = 0;i<k;i++)
	{
		for(vector<double>::iterator itp = dt.begin();itp != dt.end(); ++itp)
		{
			product = product + ((*itr) * (*itp));
			itr++;	
		}
		if( product >= 0){result = 1;}
		else {result = 0;}
		gvector.push_back(result);
	}
	gElements g1;
	g1.gsetValues(data->getID(),gvector); 
	gVec.push_back(g1);
	int binary1=0;
	int hl = (pow(10,k))/10;
	for(vector<double>::iterator it11 = gvector.begin();it11 != gvector.end(); ++it11)
	{
		binary1 = binary1 + (*it11)*hl;
		hl = hl / 10;
	//	cout << (*it11);
	}
	int fresult= convertBinaryToDecimal(binary1);
	//cout<<"}"<<binary1<<"|"<<fresult<<endl;
	return fresult;
}

int ghashF2(int numOfDim,int k,gElements *data,int HTsize,vector<gElements> &gVec,vector<double> &ris)//hashfuctions for cosine  lsh and hypercube
{
	vector <double> dt = data->ggetVectorElem();
	vector <double> gvector;
	double result;
	long  double product = 0.0;
	vector <double>::iterator itr = ris.begin();
	for(int i = 0;i<k;i++)
	{
		for(vector<double>::iterator itp = dt.begin();itp != dt.end(); ++itp)
		{
			product = product + ((*itr) * (*itp));
			itr++;	
		}
		if( product >= 0){result = 1;}
		else {result = 0;}
		gvector.push_back(result);
	}
	gElements g1;
	g1.gsetValues(data->ggetID(),gvector); 
	gVec.push_back(g1);
	int binary1=0;
	int hl = (pow(10,k))/10;
	for(vector<double>::iterator it11 = gvector.begin();it11 != gvector.end(); ++it11)
	{
		binary1 = binary1 + (*it11)*hl;
		hl = hl / 10;
	//	cout << (*it11);
	}
	int fresult= convertBinaryToDecimal(binary1);
	//cout<<"}"<<binary1<<"|"<<fresult<<endl;
	return fresult;
}










