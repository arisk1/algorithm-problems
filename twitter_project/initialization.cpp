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


vector <int> randomK(default_random_engine &e,int k,int counterOfLines)
{
	std::uniform_real_distribution<double> distrR(0,counterOfLines); 
	vector <int> thesis;
	for(int i=0;i<k;i++)
	{
		thesis.push_back(distrR(e)); //choose random data points as centroids
	}
	return thesis;
}

void kmeansPlusPlus(default_random_engine &e,int k,int counterOfLines,Elements *data,vector <double> cen[],int metricN) 
{
	std::uniform_real_distribution<double> distrR(0,counterOfLines);
	int *thesis;
	thesis = new int [k];
	for(int i=0;i<k;i++){thesis[i]=-1;}
	int t = 1;
	//choose random first centroid
	thesis[0] = distrR(e);
	vector <double> dt = data[thesis[0]].getVectorElem();
	for(vector<double>::iterator it = dt.begin();it != dt.end();++it)
	{
		cen[0].push_back((*it));
	}
	int ceni=0;
	while(t < k)
	{
		//create the p with D distances
		//and choose new centroids
		int *thesisData; //parallel array with pos to dataset
		thesisData = new int [counterOfLines-t];
		for(int i=0;i<counterOfLines-t;i++)
		{
			thesisData[i] = i+t;
		}
		double * p;
		p = new double [counterOfLines-t];
		vector <double> distances;
		for(int i =0;i<counterOfLines-t;i++)
		{
			vector <double> vec = data[thesisData[i]].getVectorElem();
			double mind;
			if(metricN==1)
				mind = calcEucledianDist(vec,cen[0]);	
			else
				mind=cosine_distance_vectors(vec,cen[0]);
			for(int z=1;z<=ceni;z++){
				double mind2;
				if(metricN==1)
					mind2 = calcEucledianDist(vec,cen[z]);
				else
					mind2 = cosine_distance_vectors(vec,cen[z]);
				if( mind2 < mind)
					mind = mind2;											
			}
			distances.push_back(mind);
		}
		vector <double> help = distances;
		std::sort (help.begin(), help.end(), std::greater<double>());
		vector <double>::iterator maxit = help.begin(); 
		for(int i=0;i<(counterOfLines-t);i++) //compute di
		{
			double sum = 0.0;
			vector <double>::iterator it = distances.begin();
			if(i==0){sum = pow((*it),2); }
			for(int y=0;y<i;y++)
			{
				sum += pow((*it),2);
				++it;
			}
			p[i] = sum/(*maxit);

		}
		std::uniform_real_distribution<double> distrR1(0, p[counterOfLines-t-1]);
		int rchoose = distrR1(e);
		ceni++;
		for(int i=0;i<counterOfLines-t;i++)
		{
			if(rchoose < p[0]){thesis[ceni] = thesisData[0];break;}
			if((rchoose > p[i]) && (rchoose < p[i+1]))
			{
				thesis[ceni] = thesisData[i+1]; //points to the new centroid
				break;
			}
		}
		vector <double> aaa = data[thesis[ceni]].getVectorElem();
		for(vector<double>::iterator ait = aaa.begin();ait != aaa.end();++ait)
		{
			cen[ceni].push_back(*ait);
		}
		delete[] thesisData;
		delete[] p;
		t++;
	}

}


