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

void fillclustersLoyds(vector <double> cen[],int k,Elements *data,hashTable &clusters,int counterOfLines,int num,int metricN)
{
	for(int i=0;i<counterOfLines;i++) // for every data
	{
		//cout << "11" << endl;
		vector <double> pdata = data[i].getVectorElem();
		vector <double> distances;
		for(int y=0;y<k;y++)
		{
			vector <double> centroid; // get centroid of each cluster
			for(vector<double>::iterator it = cen[y].begin();it != cen[y].end(); ++it)
			{
				centroid.push_back((*it));
			}	
			double dist; // caluclate distance from centroid to data point
			if(metricN == 1)
				dist=calcEucledianDist(centroid,pdata);
			else
				dist = cosine_distance_vectors(centroid,pdata);
			//cout << "d" << dist << endl;
			distances.push_back(dist);
		}
		int posMin=0; //find the min distance from centroids
		int counter=1;
		vector<double>::iterator it2 = distances.begin();
		double distMin=(*it2);
		for(vector<double>::iterator it3 = distances.begin()+1;it3 != distances.end(); ++it3)
		{	
			if((*it3) < distMin) 
			{
				distMin = (*it3);
				posMin = counter;
			}
			counter++;
			//cout << (*it3) << endl;
		}
	//	cout << posMin << endl;
		Elements *pp = &data[i];
		clusters.insertHT(pp,posMin); //insert data point to clusters 
	}
}

//same with the loyds but we give the single cluster we want to change
void miniLoyds(vector <double> cen[],int k,Elements *data,hashTable &clusters,int counterOfLines,int i,int metricN)
{
		vector <double> pdata = data[i].getVectorElem();
		vector <double> distances;
		for(int y=0;y<k;y++)
		{
			vector <double> centroid;
			for(vector<double>::iterator it = cen[y].begin();it != cen[y].end(); ++it)
			{
				centroid.push_back((*it));
			}
			double dist;
			if(metricN==1)
				dist=calcEucledianDist(centroid,pdata);
			else
				dist=cosine_distance_vectors(centroid,pdata);
			distances.push_back(dist);
		}
		int posMin=0;
		int counter=1;
		vector<double>::iterator it2 = distances.begin();
		double distMin=(*it2);
		for(vector<double>::iterator it3 = distances.begin()+1;it3 != distances.end(); ++it3)
		{	
			if((*it3) < distMin) 
			{
				distMin = (*it3);
				posMin = counter;
			}
			counter++;
		}
		Elements *pp = &data[i];
		clusters.insertHT(pp,posMin);
}

void fillclustersLsh(int L,default_random_engine &e,vector <double> cen[],int k,Elements *data,hashTable &clusters,int counterOfLines,int num,int metricN,int dim,int hf)
{
	int hashTableSize;
	if(metricN==1)
	{ 
		hashTableSize= (counterOfLines / 8); 
	}
	else	
	{
		hashTableSize = pow(2,hf);
	}
	/*--------------------------------------------CREATE HASHTABLE----------------------------------------------*/
	int w=4;	
	vector<gElements> *gVec; //array of vectors to store the G family
	gVec = new vector<gElements> [L];
	vector<double> *vs;	//array of vector to store the random V's for the L hashtables/euclidean
	vs = new vector<double> [L];
	vector<double> *ts;//array of vectors to store the ramdom L T's for the hashtables/euclidean
	ts = new vector<double> [L];
	vector<double> *ris;//array of vectors to store random r's for cosine
	ris = new vector<double> [L];
	if(metricN==1)
	{
		for(int ii=0;ii<L;ii++)		//we create k v's and k t's/ eucledian 
		{
			TandV(e,vs[ii],ts[ii],hf,dim,w);
		}
	}
	else
	{
		for(int ii2=0;ii2<L;ii2++) //we create the r's for cosine method
		{
			Ri1(e,ris[ii2],hf,dim);
		}
	}
	int index;
	hashTable hashTableL[L](hashTableSize); //create L hashTables with hashTableSize size
	for(int i=0;i<L;i++) //insert elements to L hashtables
	{ 
		for (int z=0;z<counterOfLines;z++)
		{
			Elements *p = &data[z];
			//We make the gVector inside hashfuction which contains the Gs and the Id
			if(metricN==1) index=hashF(e,dim,w,hf,&data[z],hashTableSize,gVec[i],vs[i],ts[i]);
			else index = hashF2(dim,hf,&data[z],hashTableSize,gVec[i],ris[i]);
			hashTableL[i].insertHT(p,index); //insert element to the position index
			//cout << index << "|";
		}
		//print hashtable
		//hashTableL[i].printHT(hashTableSize,&hashTableL[i]);
	}
	/*-------------------------------------------- SEARCH IN HASHTABLES LSH-----------------------------------------------*/
	cout << ">>LSH" <<endl;
	//fine the fist radius 
	//cout << "1" << endl;
	double minr;
	if(metricN==1)
		minr = calcEucledianDist(cen[0],cen[1]);
	else
		minr = cosine_distance_vectors(cen[0],cen[1]);
	for(int i=0;i<k;i++) //find and compute radius
	{
		for(int y=(i+1);y<k;y++)
		{
			double x;
			if(metricN==1){x = calcEucledianDist(cen[i],cen[y]);}
			else{x =cosine_distance_vectors(cen[i],cen[y]);}
			if(x<minr)
				minr = x;
		}
	}
	//cout << "2" << endl;
	double radii = minr/2;
	for(int i=0;i<counterOfLines;i++)
	{	
		data[i].setCID(-1);
	}
	gElements *Qdata; //array of elements classes
	Qdata = new gElements[k];
	for(int i=0;i<k;i++)
	{
		Qdata[i].gsetValues(i,cen[i]);
	}
	//cout << "3" << endl;
	vector<MyDist> *Distances;	//euclidean Distances
	Distances = new vector<MyDist> [k];
	vector<gElements> QgVec; //the g family for the query 
	int search3L=0;
	for(int i=0;i<L;i++)
	{
		for (int z=0;z<k;z++)
		{		
			if(metricN==1)index=ghashF(e,dim,w,hf,&Qdata[z],hashTableSize,QgVec,vs[i],ts[i]);	
			else index=ghashF2(dim,hf,&Qdata[z],hashTableSize,QgVec,ris[i]);
			vector<gElements>::iterator it2 = QgVec.begin();
			vector<double> y2 = (*it2).ggetVectorElem(); // g from query 
			vector<Elements*> x = hashTableL[i].getVector(index);
			if(x.size() == 0) //we chech if the hashTable bucket is empty		
			{cout<<"EmptyBucket!go the the next iteration"<<endl;continue;}
			if(metricN==1) searchLSH(search3L,x,gVec[i],y2,metricN,&Qdata[z],Distances,counterOfLines,z); //search hashTables for euclidian  method
			else searchLSH(search3L,x,gVec[i],y2,metricN,&Qdata[z],Distances,L,z); //search hashTables for cosine  method
			QgVec.clear(); //clear Gfamily for query an get the next query
		}
	}
	//cout << "4" << endl;
	int counterInserted=0;
	while(1) //do the assingment to the clusters 
	{
		cout << "Radius" << radii <<  endl;
		int copycounter=counterInserted;
		for(int i=0;i<k;i++)
		{
			for(vector<MyDist>::iterator it=Distances[i].begin();it!=Distances[i].end();++it)
			{
				//search for id in dataset
				int thesisOfID = searchID((*it).id,data,counterOfLines);
				if( (*it).dist<= radii )
				{
					if( data[thesisOfID].getCID() == -1 )
					{
						data[thesisOfID].setCID(i);
						counterInserted ++;
					}
					else if(data[thesisOfID].getCID() == i){}
					else 
					{
						vector <double> y1 = data[thesisOfID].getVectorElem();
						double nw;
						if(metricN == 1)
							nw = calcEucledianDist(cen[i],y1);
						else
							nw = cosine_distance_vectors(cen[i],y1);
						if(nw < (*it).dist)
							data[thesisOfID].setCID(i);
					}
				}
			}
		}
		radii = radii * 2;
		if(counterInserted!=0)
		{
			if(copycounter == counterInserted )
				break;
		}
		if(counterInserted == counterOfLines)
			break;
	}
	//cout << "5" << endl;
	//cout <<"#items inserted from lsh:" << counterInserted << endl;
	int co=0;
	for(int i=0;i<counterOfLines;i++)	
	{
		if(data[i].getCID() == -1)	
		{
			co++;
			miniLoyds(cen,k,data,clusters,counterOfLines,i,metricN);
		}
		else
		{
			Elements *pp = &data[i];
			clusters.insertHT(pp,data[i].getCID());
		}
	}
	//cout <<"#remaining items inserted with loyds:" << co << endl;
	
}

void fillclustersHC(int L,default_random_engine &e,vector <double> cen[],int k,Elements *data,hashTable &clusters,int counterOfLines,int num,int metricN,int dim,int hf,int M,int probes)
{

	int hashTableSize;
	if(metricN==1)
	{ 
		hashTableSize= (counterOfLines / 8); 
	}
	else	
	{
		hashTableSize = pow(2,hf);
	}
	if(probes > hashTableSize-1) 
	{
		cout<<"entry error:";
		cout << "Accepted Values for probes:(1," << hashTableSize-1 << ")" <<endl;
		exit(-1);
	}
	//cout << "1" << endl;
	/*--------------------------------------------CREATE HASHTABLE----------------------------------------------*/
	int w=4;	
	vector<gElements> gVec;//vector to store the G family
	vector<double> vs; //vector to store the random V's
	vector<double> ts;// vector to store the ramdom  T's 
	vector<double> ris; //vectors to store random r's for cosine
	if(metricN==1)
	{
		TandV(e,vs,ts,hf,dim,w);//we create k v's and k t's/ eucledian 
	}
	else
	{
		Ri1(e,ris,hf,dim);//we create the r's for cosine method
	}
	int index;
	hashTable hashTableL(hashTableSize);//create hashTable with hashTableSize size
	for (int z=0;z<counterOfLines;z++)	//insert elements to hashtableL
	{
		Elements *p = &data[z];
		//We make the gVector inside hashfuction which contains the Gs and the Id
		if(metricN==1) index=hashFHC(e,dim,w,hf,&data[z],hashTableSize,gVec,vs,ts);
		else index = hashF2(dim,hf,&data[z],hashTableSize,gVec,ris);
		//cout << index << "|";
		hashTableL.insertHT(p,index);//insert element to the position index
	}
	//print hashtable
	//hashTableL.printHT(hashTableSize,&hashTableL);
	/*-------------------------------------------- SEARCH IN HASHTABLE-----------------------------------------------*/
	cout << ">>BINARY (0/1) HYPERCUBE" <<endl;
	//fine the fist radius 
	//cout << "1" << endl;
	double minr;
	if(metricN==1)
		minr = calcEucledianDist(cen[0],cen[1]);
	else
		minr =cosine_distance_vectors(cen[0],cen[1]);
	for(int i=0;i<k;i++) //find and compute radius
	{
		for(int y=(i+1);y<k;y++)
		{
			double x;
			if(metricN==1){x = calcEucledianDist(cen[i],cen[y]);}
			else{x =cosine_distance_vectors(cen[i],cen[y]);}
			if(x<minr)
				minr = x;
		}
	}
	//cout << "2" << endl;
	double radii = minr/2;
	for(int i=0;i<counterOfLines;i++)
	{	
		data[i].setCID(-1);
	}
	gElements *Qdata; //array of elements classes
	Qdata = new gElements[k];
	for(int i=0;i<k;i++)
	{
		Qdata[i].gsetValues(i,cen[i]);
	}
	vector<MyDist> *Distances; //euclidean Distances
	Distances = new vector<MyDist> [k];
	vector<gElements> QgVec;//the g family for the query 
	int Mfound1;
	int hdCounter;
	for (int z=0;z<k;z++)
	{
		int Mfound=0;//how many found in one bucket
		int maxProbes=0;//max number of probes
		int maxis=0; //variable to check for NN with hamming distance
		int hdDist=1;//hamming distance
		int hdCounterCopy=0;//counter for NN
		if(metricN==1) index=ghashFHC(e,dim,w,k,&Qdata[z],hashTableSize,QgVec,vs,ts);	
		else index=ghashF2(dim,k,&Qdata[z],hashTableSize,QgVec,ris);
		vector<gElements>::iterator it2 = QgVec.begin();
		vector<double> y2 = (*it2).ggetVectorElem(); // g from query 
		vector<Elements*> x = hashTableL.getVector(index);
		while(Mfound < M)
		{
			hdCounter=hdCounterFun(hashTableSize,index,hdDist);	//count NN's	
			if(x.size() != 0)//we chech if the hashTable bucket is empty
			{
				if(metricN==1) Mfound1=searchHC(M,x,gVec,y2,metricN,&Qdata[z],Distances,z);
				else Mfound1=searchHC(M,x,gVec,y2,metricN,&Qdata[z],Distances,z);
				Mfound += Mfound1;
			}
			if((Mfound<M) && (maxProbes < probes))
			{
				for(int i=maxis;i<hashTableSize;i++)
				{	
					int hd = hammingDistance(i,index);
					if(hd==hdDist)
					{
						hdCounterCopy++;
						x = hashTableL.getVector(i);
						maxProbes++;
						maxis=i+1; //not to check for hd==1 with the same i
						break;	
					}
				}
				//we checked the max NN's in hdDist so we append the hdDist by 1
				if(hdCounterCopy == hdCounter){hdDist++;maxis=0;hdCounterCopy=0;}
			}
			else{break;}//break the while
		}
		QgVec.clear(); //clear Gfamily for query an get the next query
	}
	//cout << "4" << endl;
	int counterInserted=0;
	while(1) //assingn data points to clusters
	{
		cout << "Radius" << radii <<  endl;
		int copycounter=counterInserted;
		for(int i=0;i<k;i++)
		{
			for(vector<MyDist>::iterator it=Distances[i].begin();it!=Distances[i].end();++it)
			{
				//cout << "id:" <<(*it).id << endl;
				//search for id in dataset
				int thesisOfID = searchID((*it).id,data,counterOfLines);
				if( (*it).dist<= radii )
				{
					if( data[thesisOfID].getCID() == -1 )
					{
						data[thesisOfID].setCID(i);
						counterInserted ++;
					}
					else if(data[thesisOfID].getCID() == i){}
					else 
					{
						vector <double> y1 = data[thesisOfID].getVectorElem();
						double nw;
						if(metricN == 1)
							nw = calcEucledianDist(cen[i],y1);
						else
							nw =cosine_distance_vectors(cen[i],y1);
						if(nw < (*it).dist)
							data[thesisOfID].setCID(i);
					}
				}
			}
		}
		radii = radii * 2;
		if(counterInserted!=0)
		{
			if(copycounter == counterInserted )
				break;
		}
		if(counterInserted == counterOfLines)
			break;
	}
	//cout << "5" << endl;
	//cout <<"#items inserted from hypercube:" << counterInserted << endl;
	int co=0;
	for(int i=0;i<counterOfLines;i++)	
	{
		if(data[i].getCID() == -1)	
		{
			co++;
			miniLoyds(cen,k,data,clusters,counterOfLines,i,metricN);
		}
		else
		{
			Elements *pp = &data[i];
			clusters.insertHT(pp,data[i].getCID());
		}
	}
	//cout <<"#remaining items inserted with loyds:" << co << endl;
}














