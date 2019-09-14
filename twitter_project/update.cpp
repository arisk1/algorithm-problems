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

using namespace std;

void kmeans(hashTable &clusters,int k,vector <double> cen[])
{
	for(int i=0;i<k;i++)//for every cluster
	{
		vector<Elements*> x = clusters.getVector(i);
		if(x.size()==0) continue; 
		vector<Elements*>::iterator it = x.begin();
		vector <double> res = (*it)->getVectorElem();
		int counter=0;
		for(vector<Elements*>::iterator it2 = x.begin()+1;it2 != x.end(); ++it2)
		{
			vector <double> y = (*it2)->getVectorElem();
			vector<double>::iterator it3 = y.begin();
			for(vector<double>::iterator it4 = res.begin();it4 != res.end(); ++it4)
			{
				(*it4) = (*it4) + (*it3);
				++it3; 
			}
			counter++;
		}
		vector<double>::iterator itCen = cen[i].begin();
		for(vector<double>::iterator it5 = res.begin();it5 != res.end(); ++it5) //compute new centroid
		{
			(*it5) = (*it5) / (counter);
			(*itCen) = (*it5);
			++itCen;
		}
		
	}
}


void pam(hashTable &clusters,int k,vector <double> cen[],Elements * data,int counterOfLines,double newobj[],double oldobj[],int help[],int metricN)
{
	double obj[k];
	double nobj[k];
	for(int i=0;i<k;i++){newobj[i]=0.0;}
	for(int i=0;i<k;i++){nobj[i]=oldobj[i];}
	for(int i=0;i<k;i++) //for every cluster
	{
		int flag=0;
		for(int yy=0;yy<k;yy++){if(help[yy] == i) flag=1;}
		if(flag==1){flag=0;continue;}
		vector<Elements*> x = clusters.getVector(i);
		vector <double> oldCentroid = cen[i]; //the centroid we gave
		for(vector<Elements*>::iterator it = x.begin();it != x.end(); ++it)
		{
			vector <double> newCentroid = (*it)->getVectorElem();
			for(int i=0;i<k;i++){obj[i]=0.0;}
			for(vector<Elements*>::iterator it1 = x.begin();it1 != x.end(); ++it1)
			{
				vector <double> y = (*it1)->getVectorElem();
				double dist; //find dist and caluclate objective
				if(metricN==1)
					dist = calcEucledianDist(y,newCentroid);
				else
					dist = cosine_distance_vectors(y,newCentroid);
				obj[i] += dist;
			}
			//double dist1;
			//if(metricN==1)
			//	dist1 = calcEucledianDist(oldCentroid,newCentroid);
			//else
			//	dist1=cosine_similarity_vectors(oldCentroid,newCentroid);
			//obj[i] += dist1;		
			if(obj[i] < nobj[i]) //compare objectives to get the "best" centroids
			{
				cen[i] = newCentroid;
				newobj[i] = obj[i];
				nobj[i]=obj[i];
			}
			
		}
	}
}










