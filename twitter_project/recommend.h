#ifndef RECOMMEND_H
#define RECOMMEND_H

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
bool checkPegs(vector <double> array); //check if a vector is full of zeros

void makeOutput1(char* outputpath,int z, Elements * newData,tweetElem * data,vector<int> NNids[],vector <int> kcoins[],coinElem* coinData,int size,int p, int coinCounter,double time,double time2,hashTable &clusters,vector <double> centroids[],int k,hashTable &clusters1,vector <double> centroids1[],int k1,int tweetCounter,hashTable &clusters2,vector <double> centroids2[],int k2);
#endif
