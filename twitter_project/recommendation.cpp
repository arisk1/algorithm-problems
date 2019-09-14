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

using namespace std;

int main(int argc , char* argv[])
{
	char input[1000];
	char coin_input[1000];
	strcpy(coin_input,"./coins_queries.csv");
	char lexicon_input[1000];
	strcpy(lexicon_input,"./vader_lexicon.csv");
	char config[1000];
	char outputpath[1000];
	char metric[1000];	
	int param,validate=0;
	if(argc == 5)
    {
		for( param=1 ; param<=3 ; param+=2 )
        {
			if(strcmp("-d",argv[param])==0)
            {
				strcpy(input,argv[param+1]);
            }
			else if(strcmp("-o",argv[param])==0)
            {
              strcpy(outputpath,argv[param+1]);
            }
			else {cout<<"entry error";return-1;}
		}		
    }
	else if(argc == 6)
    {
		for( param=1 ; param<=5 ; param+=2 )
        {
				if(strcmp("-d",argv[param])==0)
            {
				strcpy(input,argv[param+1]);
            }
			else if(strcmp("-o",argv[param])==0)
            {
              strcpy(outputpath,argv[param+1]);
            }
			else if(strcmp("-validate",argv[param])==0)
			{
				validate = 1;
			}
			else {cout<<"entry error";return-1;}
		}		
    }
	int flag = 0;
	while(1)
	{
		if(flag==1)
		{
			cout << "Exit . . . " <<endl;
			break;
		}
		double p1 = Rfunction(input);
		int P;
		int helpinput=0;
		if(p1==0.0){helpinput=1;P=20;}
		else{P=p1;}
		int counterOfLines = lineCounter(input);
		int counterOfCoins = lineCounter(coin_input);
		int counterOfLexicon = lineCounter(lexicon_input);
		cout <<"INPUT_FILE: "<< input <<endl;
		cout <<"OUTPUT_FILE: " << outputpath << endl;
		lexicon *lexiconData;
		lexiconData = new lexicon[counterOfLexicon];
		tweetElem *data;
		data = new tweetElem[counterOfLines];
		coinElem *coinData;
		coinData = new coinElem[counterOfCoins];
		int dim = readTweetFile(data,input,helpinput);
		int cb=readCoinBase(coinData,coin_input);
		int ld =readLexicon(lexiconData,lexicon_input);
		if(validate==1)
			cout <<"validation required"<<endl;
		else 
			cout << "validation not required"<<endl;
		cout << "ELEMENTS IN INPUT FILE -> " << counterOfLines << endl;
		cout << "COINS IN FILE -> " << counterOfCoins << endl;
		cout << "WORDS IN LEXICON ->" << counterOfLexicon << endl;
		cout << ">> Executing the following recommendation algorithms:" << endl;	
		cout << "	1. Cosine LSH Recommendation "<<endl;
		cout << "	2. Clustering Recommendation "<<endl;
		cout << "	type 5 to start:" ;
		int option;
		cin >> option;
		if(option ==5)
		{
			preRecommend(P,data,coinData,lexiconData,counterOfLines,counterOfCoins,counterOfLexicon,outputpath);
		}
		else
		{cout << "wrong entry" << endl;}
		delete[] data;
		delete[] lexiconData;
		delete[] coinData;
		flag=1;
	}
	

}
