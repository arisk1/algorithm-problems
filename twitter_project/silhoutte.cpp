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

double computeSilhoutte(hashTable &clusters,vector <double> centroids[],int i,int k,int metricN)
{
		vector<Elements*> x = clusters.getVector(i);
		int sizeCluster = x.size();
		if(sizeCluster == 0) {return -5;}
		double result  = 0.0;
		for(vector<Elements*>::iterator it = x.begin();it != x.end(); ++it)
		{
			double res=0.0;
			double secres = 0.0;
			vector <double> y = (*it)->getVectorElem();
			double dist1=0.0;
			int minC;
			for(int z=0;z<k;z++)
			{
				if(z!=i)
				{
					vector<double> x1 = centroids[z];
					if(metricN==1)
						dist1 = calcEucledianDist(x1,y);
					else
						dist1=cosine_distance_vectors(x1,y);
					minC = z;
				}
			}
			for(int z=0;z<k;z++) //find second min centroid
			{
				if(z!=i)
				{
					double min;
					vector<double> x1 = centroids[z];
					if(metricN==1)
						min = calcEucledianDist(x1,y);
					else
						min= cosine_distance_vectors(x1,y);
					if(min < dist1)
					{
						dist1 = min;
						minC = z;
					}
				}
			}
			vector<Elements*> x1 = clusters.getVector(minC);
			int sizeCluster2 = x1.size();	
			for(vector<Elements*>::iterator it2 = x1.begin();it2 != x1.end(); ++it2) //compute bi
			{
				double dist;
				vector <double> y2 = (*it2)->getVectorElem();
				if(metricN==1)
					dist = calcEucledianDist(y,y2);
				else
					dist =  cosine_distance_vectors(y,y2);
				secres += dist;
			}
			for(vector<Elements*>::iterator it2 = x.begin();it2 != x.end(); ++it2) //compute ai
			{
				double dist;
				vector <double> y2 = (*it2)->getVectorElem();
				if(metricN==1)
					dist = calcEucledianDist(y,y2);
				else
					dist =  cosine_distance_vectors(y,y2);
				res += dist;
			}
			double ai = res / sizeCluster;
			double bi = secres / sizeCluster2;
			double maxaibi=0.0; //find max of ai , bi
			if(ai > bi)
				maxaibi = ai;
			else
				maxaibi = bi;
			if(maxaibi == 0)
			{
				result += 0;
			}
			else 
			{	
				result += (bi - ai)/(maxaibi);
			}
		}
		if(sizeCluster!= 0 )
		{
			result = result / sizeCluster;
		}
		return result;
}

int findCentroid(vector <double> centroid , int counterOfLines,Elements *data)
{
	int pos=-1;
	for(int i=0;i<counterOfLines;i++)
	{
		vector<double> x = data[i].getVectorElem();	
		double dist = vectorEquality(centroid , x);
		if(dist == 1)
		{
			pos=i;
			break;
		}
	}
	return pos;
}



