#ifndef CLRECOMMEND_H
#define CLRECOMMEND_H

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

void normalize(vector <users> &users1);
void preRecommend(int p,tweetElem * data,coinElem* coinData,lexicon * lexiconData,int tweetCounter,int coinCounter,int lexiconCounter,char* outputpath);

#endif
