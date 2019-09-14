#ifndef INITIALIZATION_H
#define INITIALIZATION_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <cstring>
#include <bits/stdc++.h> 

vector <int> randomK(default_random_engine &e,int k,int counterOfLines);
void kmeansPlusPlus(default_random_engine &e,int k,int counterOfLines,Elements *data,vector <double> cen[],int metricN); 
#endif
