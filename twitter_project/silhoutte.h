#ifndef SILHOUTTE_H
#define SILHOUTTE_H

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

double computeSilhoutte(hashTable &clusters,vector <double> centroids[],int i,int k,int metricN);
int findCentroid(vector <double> centroid , int counterOfLines,Elements *data);

#endif
