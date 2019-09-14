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
#include "silhoutte.h"

using namespace std;
void combination1(hashTable &clusters,vector <double> centroids[],int k,int counterOfLines,default_random_engine &e,Elements *data,int metricN,char* outputpath,int c)
{
	std::clock_t start,stop; //start clock
	start = std::clock();
	cout<< ">>Executing combination I1A1U1" << endl;
	string str = "I1A1U1";
	vector <int> thesis = randomK(e,k,counterOfLines); //random centroid points
	vector<int>::iterator it10 = thesis.begin();
	for(int i=0;i<k;i++) //get actual centroids
	{
		//cout << (*it10) << endl;
		vector <double> thesisElem = data[(*it10)].getVectorElem();
		for(vector<double>::iterator it1 = thesisElem.begin();it1!= thesisElem.end(); ++it1)
		{
			centroids[i].push_back((*it1));
		}
		++it10;
	}
	//firstrun
	int tries=0;
	while(1)
	{
		tries++;
		cout <<"Try#"<< tries << endl;
		for(int c=0;c<k;c++) 
		{
			clusters.clearVec(c);
		}
		fillclustersLoyds(centroids,k,data,clusters,counterOfLines,1,metricN);
		double obj [k];	//compute old objective
		for(int i=0;i<k;i++){obj[i]=0.0;}
		for(int i=0;i<k;i++)
		{
			vector<Elements*> x = clusters.getVector(i);
			vector<Elements*>::iterator it = x.begin();
			for(vector<Elements*>::iterator it2 = x.begin();it2 != x.end(); ++it2)
			{
				vector <double> y = (*it2)->getVectorElem();
				double dist ;
				if(metricN ==1)
					dist = calcEucledianDist(y,centroids[i]);
				else
					dist = cosine_distance_vectors(y,centroids[i]);
				dist = pow(dist,2);
				obj[i] += dist;
			}
		}
		kmeans(clusters,k,centroids);
	
		double obj2 [k];	//compute new objective
		for(int i=0;i<k;i++){obj2[i]=0.0;}
		for(int i=0;i<k;i++)
		{
			vector<Elements*> x = clusters.getVector(i);
			vector<Elements*>::iterator it = x.begin();
			for(vector<Elements*>::iterator it2 = x.begin();it2 != x.end(); ++it2)
			{
				vector <double> y = (*it2)->getVectorElem();
				double dist;	
				if(metricN==1)
					dist = calcEucledianDist(y,centroids[i]);
				else
					dist=cosine_distance_vectors(y,centroids[i]);
				dist = pow(dist,2);
				obj2[i] += dist;
			}
		}

		int counter=0;	
		for(int ii=0;ii<k;ii++) //compare objectives 
		{
			if(obj2[ii] == 0.0) {counter++;	continue;}
			if( (obj2[ii]>=(1.0-0.01)*obj[ii] && obj2[ii] <= obj[ii]) || (obj[ii]==obj2[ii] )|| (obj2 > obj && obj2[ii]<=(1.0-0.01)*obj[ii]) )
			{
				counter++;	
			}
		}
		//cout << "counter:" <<counter<< endl;
		if(counter==k) break;
	}
	//compute silhouttes
	/*if(c==1){
	for(int i=0;i<k;i++) //compute silhouttes
		{ vector <Elements*> x= clusters.getVector(i);cout <<"i:" << i <<"|" <<x.size()<<endl;}exit(-1);}
	stop = std::clock(); //stop clock*/
	/*if(c==1)
	{
		vector <double> silhouttes;
		for(int i=0;i<k;i++) //compute silhouttes
		{
			cout << "computing_silhoutte:" << i  ;
			double si = computeSilhoutte(clusters,centroids,i,k,metricN);
			cout <<", Silhoutte#" << i  << ":" ;
			if(si==-5) {cout << "empty_cluster" << endl;}
			else{cout << si << endl;}
			silhouttes.push_back(si);	
		} 
	}*/
	double TimeTotal = (stop - start) / (double)(CLOCKS_PER_SEC / 1000);
}




















	

