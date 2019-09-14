#ifndef CLASSES_H
#define CLASSES_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <cstring>
#include<bits/stdc++.h> 



using namespace std;

class Elements //store input and query
{
	private:	
		int cid;
		int id;
		vector <double> dt;
	public:
		Elements(){};
		void setCID(int i);
		void setValues(int randID,vector<string> &d);
		void setValues2(int randID,vector<double> &d);
		int getID();
		int getCID();
		vector <double> getVectorElem();
		~Elements(){};
};

class tweetElem //store input and query
{
	private:	
		int id;
		int twid;
		vector <string> dt;
	public:
		tweetElem(){};
		void twsetValues(int randID,vector<string> &d);
		int twgetID();
		int twgetTWID();
		vector <string> twgetVectorElem();
		~tweetElem(){};
};

class coinElem
{
	private:
		int id;
		vector <string> coin;
	public:
		coinElem(){};
		void setCoin(int id,vector<string> &d);
		int getCoinID();
		vector <string> getCoin();
		~coinElem(){};
};

class lexicon
{
	private:
		string lexis;
		double mark;
	public:
		lexicon(){};
		void setLexis(vector<string> &d);
		double getLexisMark();
		string getLexis();
		~lexicon(){};
};

class users 
{
	private:
		int id;
		int tweet_id;
		vector <double>  u;
	public:
		users(){};
		void setU(int userid,int tweetid,double score,int coins,vector <int> coinIDs);
		void modifyVec(double score,int coins,vector <int> coinIDs);
		void modifyVec2(double x,int y,int iter);
		int getUserID();
		int getTweetID();
		vector <double> getUArray();
		~users(){};
};

class gElements // store g family
{
	private:	
		int gid;
		vector <double> gdt;
	public:
		gElements(){};
		void gsetValues(int randID,vector<double> &d);
		int ggetID();
		vector <double> ggetVectorElem();
		~gElements(){};
};

struct MyDist //store distances and cosine similaritis along with the input file's id
{
    int id;
	double dist;
    MyDist(int i,double d) : id(i),dist(d) {}
};

struct min_dist //operator for < sort .euclidean distance
{
    inline bool operator() (const MyDist& struct1, const MyDist& struct2)
    {
        return (struct1.dist < struct2.dist);
    }
};

struct max_cosine //operator for > sort .cosine similarity
{
    inline bool operator() (const MyDist& struct1, const MyDist& struct2)
    {
        return (struct1.dist > struct2.dist);
    }
};

int read1(Elements *data,char* path1); //input file
int readTweetFile(tweetElem *data,char* path1,int help); //read input file and store
int readCoinBase(coinElem *data,char* path1); //read input file and store
int readLexicon(lexicon *data,char* path1); //read input file and store elements
int read2(Elements *Qdata,char* path2); //quaery file
void searchLSH(int search3L,vector<Elements*> x,vector<gElements> &gVec,vector<double> y2,int metric,gElements *Qdata,vector<MyDist> eucDistances[],int L,int z);
int searchHC(int M,vector<Elements*> x,vector<gElements> &gVec,vector<double> y2,int metric,gElements *Qdata,vector<MyDist> eucDistances[],int z);
vector<double> Esearch(int QcounterOfLines,int counterOfLines,Elements *data,Elements *Qdata,vector<double> EeucDistances[],int metric);
void sortAndPrintNN(int L,vector<MyDist> eucDistances[],vector<double> EDistances[],int r,char* outputpath,Elements *Qdata,double time,vector<double> times,vector<double> times2);
void sortAndPrintCosine(int L,vector<MyDist> eucDistances[],vector<double> EDistances[],int r,char* outputpath,Elements *Qdata,double time,vector <double> times,vector<double> times2);
int searchID(int x,Elements *data,int counterOfLines);
#endif
