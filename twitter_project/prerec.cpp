#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <algorithm>   
#include <bits/stdc++.h>  
#include "functions.h"
#include "classes.h"
#include "hashT.h"
#include "initialization.h"
#include "assignments.h"
#include "update.h"
#include "combinations.h"
#include "prerec.h"
#include "silhoutte.h"
#include "recommend.h"

void normalize(vector <users> &Users1) //normalize the vectors 
{

	for(vector<users>::iterator itu = Users1.begin();itu != Users1.end(); ++itu)
	{
		vector <double> u = (*itu).getUArray();
		//calculate average
		int avCounter=0;	
		double a=0.0;
		for(vector<double>::iterator itd = u.begin();itd != u.end(); ++itd)
		{
			if((*itd)!= INFINITY)
			{
				a += (*itd);
				avCounter++;
			}
		}
		if(avCounter > 0) //if the tweet has >=1 referece to a coin 
		{	
			double average = a / avCounter;
			//cout << average << endl;
			int iter=0;
			(*itu).modifyVec2(average,1,iter);
		}
		else //if no reference to a coin
		{
			(*itu).modifyVec2(0,0,0);
		}
	}
}

void preRecommend(int p,tweetElem * data,coinElem* coinData,lexicon * lexiconData,int tweetCounter,int coinCounter,int lexiconCounter,char* outputpath)
{
	std::clock_t start,stop;
	start = std::clock();
	//create the users class
	vector <users> Users1;
	//find the sentiment score of a tweet 
	for(int i=0;i<tweetCounter;i++)
	{
		int userID = data[i].twgetID();
		int tweetID = data[i].twgetTWID();
		vector <string> tweet = data[i].twgetVectorElem();
		double sentimentScore=0.0;
		vector <int> coinIDs;
		for(vector<string>::iterator it = tweet.begin();it != tweet.end(); ++it)
		{
			for(int y=0;y<lexiconCounter;y++)
			{
				string str1 = lexiconData[y].getLexis();
				if( str1 == (*it) )
				{
					double m = lexiconData[y].getLexisMark();
					sentimentScore += m;
					break;				
				}
			}
			//find the coins referenced in the tweet 
			for(int z=0;z<coinCounter;z++)
			{
				vector <string> coins = coinData[z].getCoin();
				for(vector<string>::iterator it1 = coins.begin();it1 != coins.end(); ++it1)
				{
					if((*it)==(*it1))
					{
						coinIDs.push_back(z);			
					}
				}
			}
		}
		int alpha = 15;
		if(sentimentScore != 0)
		{
			sentimentScore = sentimentScore / sqrt( (pow(sentimentScore,2) + alpha) );
		}
		cout <<"iteration:" << i << "|score:" << sentimentScore << "|" << endl;
		sort( coinIDs.begin(), coinIDs.end() );
		coinIDs.erase( unique( coinIDs.begin(), coinIDs.end() ), coinIDs.end() );
		//fill the users vector
		//first time we check if its empty so we pushback the first element 
		if(Users1.empty()) 
		{
			users userElem;
			userElem.setU(userID,tweetID,sentimentScore,coinCounter,coinIDs);
			Users1.push_back(userElem);
		}
		//seaRCH IF  the userid already exist in class users vector
		if(i>=1)
		{
			int flg=0;
			for(vector<users>::iterator it2 = Users1.begin();it2 != Users1.end(); ++it2)
			{
				int x1 = (*it2).getUserID();
				if(x1 == userID)
				{
					(*it2).modifyVec(sentimentScore,coinCounter,coinIDs);
					//cout << "change only vector >>" << x1 << endl;	
					flg=1;
					break;		
				}
			}
			if(flg==0)
			{//if it makes it here it means it does not exist, so we make a new userElem
				users userElem;
				userElem.setU(userID,tweetID,sentimentScore,coinCounter,coinIDs);
				Users1.push_back(userElem);	
			}
		}
		coinIDs.clear(); //this vector contains the ids of coins that user refered to.
	} 
	//normalize the users vector
	vector <users> Users2 = Users1; //users not normalized
	normalize(Users1);
	int sz = Users1.size();
	
	//make an array of  vector with known coins to users
	//so we can use them for the recommandation
	vector <int> * kcoins;
	kcoins = new vector<int> [sz];
	vector<users>::iterator ituser1 = Users2.begin();
	for(int i=0;i<sz;i++)
	{
		vector <double> userdata1 = (*ituser1).getUArray();
		vector<double>::iterator it123 = userdata1.begin();
		for(int y = 0;y < coinCounter; y++)
		{
			if((*it123) != INFINITY)
			{
				kcoins[i].push_back(y);
			}
			it123++;
		}
		ituser1++;
		sort(kcoins[i].begin(), kcoins[i].end() );
		kcoins[i].erase( unique( kcoins[i].begin(), kcoins[i].end() ), kcoins[i].end() );	
	}
	cout << "LSH Recommandation. . . " << endl;
	//find the P closest users 
	//with cosine-lsh
	//we convert users to Elements class
	Elements * newData;
	newData = new Elements[sz];
	int gIter=0;	
	int dim;
	//int c11=0;
	for(vector<users>::iterator it2 = Users1.begin();it2 != Users1.end(); ++it2)
	{
		int sameid = (*it2).getUserID();
		int tid = (*it2).getTweetID();
		vector <double> samev = (*it2).getUArray();
		dim = samev.size();
		//if(!checkPegs(samev)){c11++;}
		newData[gIter].setValues2(sameid,samev);
		newData[gIter].setCID(tid);
		gIter++;
	}
	//cout << c11 << endl; exit(-1);
	unsigned seed = std::chrono::steady_clock::now().time_since_epoch().count();
	std::default_random_engine e(seed);
	int L=5;
	int hf=4;
	int hashTableSize = pow(2,hf);
	/*--------------------------------------------CREATE HASHTABLE----------------------------------------------*/
	int w=4;	
	vector<gElements> *gVec; //g vec is not used in our case . but we create it anyway through the hashf
	gVec = new vector<gElements> [L];
	vector<double> *ris;//array of vectors to store random r's for cosine
	ris = new vector<double> [L];
	for(int ii2=0;ii2<L;ii2++) //we create the r's for cosine method
	{
		Ri1(e,ris[ii2],hf,dim);
	}
	int index;
	hashTable hashTableL[L](hashTableSize); //create L hashTables with hashTableSize size
	for(int i=0;i<L;i++) //insert elements to L hashtables
	{ 
		for (int z=0;z<sz;z++)
		{
			Elements *p = &newData[z];
			//We make the gVector inside hashfuction which contains the Gs and the Id
			index = hashF2(dim,hf,&newData[z],hashTableSize,gVec[i],ris[i]);
			hashTableL[i].insertHT(p,index); //insert element to the position
		}
		//print hashtable
		//hashTableL[i].printHT(hashTableSize,&hashTableL[i]);
	}
	/*-------------------------------------------- SEARCH IN HASHTABLES LSH-----------------------------------------------*/
	gElements *Qdata; //array of elements classes
	Qdata = new gElements[sz];
	for(int i=0;i<sz;i++)
	{
		int idd = newData[i].getID();
		vector <double> d = newData[i].getVectorElem();
		Qdata[i].gsetValues(idd,d);
	}
	vector<MyDist> *Distances;	//euclidean Distances
	Distances = new vector<MyDist> [sz];
	vector<gElements> QgVec; //the g family for the query 
	int search3L=0;
	for(int i=0;i<L;i++)
	{
		for (int z=0;z<sz;z++)
		{		
			index=ghashF2(dim,hf,&Qdata[z],hashTableSize,QgVec,ris[i]);
			vector<gElements>::iterator it2 = QgVec.begin();
			vector<double> y2 = (*it2).ggetVectorElem(); // g from query 
			vector<Elements*> x = hashTableL[i].getVector(index);
			if(x.size() == 0) //we chech if the hashTable bucket is empty		
			{cout<<"EmptyBucket!go the the next iteration"<<endl;continue;}
			searchLSH(search3L,x,gVec[i],y2,0,&Qdata[z],Distances,L,z); //search hashTables for cosine  method
			QgVec.clear(); //clear Gfamily for query an get the next query
		}
	}
	for(int q=0;q<sz;q++)
	{
		std::sort (Distances[q].begin(), Distances[q].end(),max_cosine()); //sort similarities
	}
	//create an array of vectors with the IDs of the P closest neighbors
	vector <int> * NNids;
	NNids = new vector<int> [sz];
	for(int q=0;q<sz;q++)
	{
			int pcounter=0;
			vector<MyDist>::iterator it11 = Distances[q].begin();
			vector<MyDist>::iterator it22 = it11++;
			while( pcounter < p )
			{
				if((Qdata[q].ggetID() == (*it11).id))
				{
					while(Qdata[q].ggetID() == (*it11).id){it11++;}	
					it22 = it11+1;
				}	
				if((Qdata[q].ggetID() == (*it22).id))
				{
					while(Qdata[q].ggetID() == (*it22).id){it22++;}	
				}	
				while((*it11).id == (*it22).id )
				{
					it22++;
				}
				NNids[q].push_back((*it11).id);
				it11 = it22;
				pcounter++;
			}
	}
	//we got the p nearest neighbors 
	//for each user 
	int z = 1;
	stop = std::clock();
	double TimeTotal1 = (stop - start) / (double)(CLOCKS_PER_SEC / 1000);
	//////////////////////////////////////////////////////////IMPLEMENT PROJECT 2////////////////////////////////////////////////////////////////////////////
	cout << "Executing project 2. . ." << endl;

	char inputp2[1000];strcpy(inputp2,"twitter_dataset_small_v2.csv");
	char configp2[1000];strcpy(configp2,"cluster.conf");
	int metricNp2 = 0;	//for lsh recommandation
	int metricNp2b2 = 1;	//for clustering recommandation
	int counterOfLinesp2 = lineCounter(inputp2);
	Elements  *datap2;
	datap2 = new Elements[counterOfLinesp2];
	int dimp2 = read1(datap2,inputp2);
	//cout << config << endl;
	int kp2,hfp2,Lp2,hashTableSizep2;
	readConfig(configp2,kp2,hfp2,Lp2); 
	hashTable clustersA2(kp2); // A2
	vector <double> * centroidsA2;	// A2
	centroidsA2 = new vector <double> [kp2]; //A2
	int kp2b2 = kp2;
	hashTable clustersB2(kp2b2); //B2
	vector <double> * centroidsB2;	//B2
	centroidsB2 = new vector <double> [kp2b2]; //B2
	combination1(clustersA2,centroidsA2,kp2,counterOfLinesp2,e,datap2,metricNp2,outputpath,0);	//we got cluster and centroids from project 2 for 1.B
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	cout << "CLUSTERING. . . " << endl;
	combination1(clustersB2,centroidsB2,kp2b2,counterOfLinesp2,e,datap2,metricNp2b2,outputpath,0);	//we got cluster and centroids from project 2 for 2.B	
	int k1 = 10;
	std::clock_t start1,stop1;
	start1 = std::clock();
	hashTable clustersB1(k1);
	vector <double> * centroidsB1;
	centroidsB1 = new vector <double> [k1];
	combination1(clustersB1,centroidsB1,k1,sz,e,newData,1,outputpath,1); //we run combination from project 2 for the normalized vectors of users
	stop1 = std::clock();
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//we got the cluster and the centroids.
	double TimeTotal2 = (stop1 - start1) / (double)(CLOCKS_PER_SEC / 1000);
	cout << "Doing the recommandation and making the output file. . . " << endl;
	makeOutput1(outputpath,z,newData,data,NNids,kcoins,coinData,sz,p,coinCounter,TimeTotal1,TimeTotal2,clustersB1,centroidsB1,k1,clustersA2,centroidsA2,kp2,tweetCounter,clustersB2,centroidsB2,kp2b2);
	delete[] newData;
	delete[] gVec;	
	delete[] ris;
	delete[] Qdata;
	delete[] Distances;
	delete[] kcoins;
	delete[] NNids;
	delete[] centroidsB1;
	delete[] centroidsA2;
	delete[] centroidsB2;
}
