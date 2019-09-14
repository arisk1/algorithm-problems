#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <cstring>
#include "functions.h"
#include "classes.h"
#include "hashT.h"
using namespace std;

void Elements::setCID(int i)
{
	this->cid = i;
}

void Elements::setValues(int randID,vector<string> &d) 
{
	//this->id =randID;
	//for(vector<string>::iterator it = d.begin();it != d.end(); ++it)
	//{
	//	double x = stod((*it),NULL);
	//	dt.push_back(x);
	//}
	this->id =atoi((d[0]).c_str());
	for(vector<string>::iterator it = d.begin()+1;it != d.end(); ++it)
	{
		double x = stod((*it),NULL);
		dt.push_back(x);
	}
}

void Elements::setValues2(int randID,vector<double> &d) 
{
	this->id =randID;
	for(vector<double>::iterator it = d.begin();it != d.end(); ++it)
	{
		double x = (*it);
		dt.push_back(x);
	}
}



int Elements::getID()
{
	return id;
}

int Elements::getCID()
{
	return cid;
}

vector<double> Elements::getVectorElem()
{
	vector <double> px;
	for(vector<double>::iterator it = dt.begin();it != dt.end(); ++it)
	{
		px.push_back((*it));
	}
	return px;
}

void tweetElem::twsetValues(int randID,vector<string> &d) 
{
	this->id =atoi((d[0]).c_str());
	this->twid =atoi((d[1]).c_str());
	for(vector<string>::iterator it = d.begin()+2;it != d.end(); ++it)
	{
		//double x = stod((*it),NULL);
		dt.push_back(*it);
	}
}

int tweetElem::twgetID()
{
	return id;
}

int tweetElem::twgetTWID()
{
	return twid;
}

vector<string> tweetElem::twgetVectorElem()
{
	vector <string> px;
	for(vector<string>::iterator it = dt.begin();it != dt.end(); ++it)
	{
		px.push_back((*it));
	}
	return px;
}

void coinElem::setCoin(int id,vector<string> &d)
{
	this->id = id;
	for(vector<string>::iterator it = d.begin();it != d.end(); ++it)
	{
		//double x = stod((*it),NULL);
		coin.push_back(*it);
	}
}

int coinElem::getCoinID()
{
	return id;
}

vector <string> coinElem::getCoin()
{
	vector <string> px;
	for(vector<string>::iterator it = coin.begin();it != coin.end(); ++it)
	{
		px.push_back((*it));
	}
	return px;
}

void lexicon::setLexis(vector<string> &d)
{
	vector<string>::iterator it = d.begin();
	this->lexis = (*it);
	it++;
	this->mark = stod((*it),NULL);
}

double lexicon::getLexisMark()
{
	return mark;
}

string lexicon::getLexis()
{
	return lexis;
}

void users::setU(int userid,int tweetid,double score,int coins,vector<int> coinIDs)
{
	this->id = userid;
	this->tweet_id = tweetid;
	for(int i=0;i<coins;i++)
	{
		int flag=0;
		for(vector<int>::iterator it1 = coinIDs.begin();it1 != coinIDs.end(); ++it1)
		{
			if(i == (*it1))
			{
				u.push_back(score);
				flag=1;
				break;			
			}
		}
		if(flag==0)
		{
			double a = INFINITY;
			u.push_back(a);			
		}
	}
}

void users::modifyVec(double score,int coins,vector<int> coinIDs)
{
	vector<double>::iterator it = u.begin();
	for(int i=0;i<coins;i++)
	{
		for(vector<int>::iterator it1 = coinIDs.begin();it1 != coinIDs.end(); ++it1)
		{
			if(i == (*it1))
			{
				(*it) += score;
				break;			
			}
		}
		it++;
	}
}

void users::modifyVec2(double x,int y,int iter)
{
	if(y==1)
	{
		for(vector<double>::iterator itd1 = u.begin();itd1 != u.end(); ++itd1)
		{
			if((*itd1)!= INFINITY)
			{	
				(*itd1) = (*itd1) - x;
				iter++;
			}
			else
			{
				//cout << "empa" << (*itd1) ;
				u.at(iter) = 0;
				iter++;		
			}
		}
	}
	else if(y==0)
	{
		for(vector<double>::iterator itd2 = u.begin();itd2 != u.end(); ++itd2)
		{
			(*itd2) = 0;
		}
	}


}
int users::getUserID()
{
	return id;
}

int users::getTweetID()
{
	return tweet_id;
}

vector <double> users::getUArray()
{
	vector <double> px;
	for(vector<double>::iterator it = u.begin();it != u.end(); ++it)
	{
		px.push_back((*it));
	}
	return px;
}

void gElements::gsetValues(int id,vector<double> &d)
{
	this->gid =id;
	for(vector<double>::iterator it = d.begin();it != d.end(); ++it)
	{
		double x = (*it);
		gdt.push_back(x);
	}
	/*	this->id =atoi((d[0]).c_str());
	for(vector<string>::iterator it = d.begin()+1;it != d.end(); ++it)
	{
		int x = atoi((*it).c_str());
		dt.push_back(x);
	}*/

}

int gElements::ggetID()
{
	return gid;
}

vector<double> gElements::ggetVectorElem()
{
	vector <double> px;
	for(vector<double>::iterator it = gdt.begin();it != gdt.end(); ++it)
	{
		px.push_back((*it));
	}
	return px;
}
int readTweetFile(tweetElem *data,char* path1,int help) //read input file and store elements to Data array
{
	vector <string> tokens1;
	string delims = " \n\t,	\r";
	string line;
	ifstream myfile1(path1);
	int iter=0;
	int cc=0;
	int dim=0; //number of dimensions
	if(myfile1.is_open())
	{
		if(help == 0){getline(myfile1,line);} //jump the first line
		while(getline(myfile1,line))
		{
			tokens1=tokenize ( line, delims );
			data[iter].twsetValues(iter,tokens1);
			int x = data[iter].twgetID();
			int y = data[iter].twgetTWID();
			vector<string> dt = data[iter].twgetVectorElem();
			//cout << x << "|" << y << "|" ;
			for(vector<string>::iterator it = dt.begin();it != dt.end(); ++it)
			{
				cc++;
			//	cout << (*it);
			}
			//cout << endl;
			iter++;
			dim = cc; //number of dimension in each line
			cc=0;
		}
		myfile1.close();
	}
	else
	{
		cout << "Unable to open!" << endl;
	}
	return dim;
}

int readCoinBase(coinElem *data,char* path1) //read input file and store elements to Data array
{
	vector <string> tokens1;
	string delims = " \n\t,	\r";
	string line;
	ifstream myfile1(path1);
	int iter=0;
	int cc=0;
	int dim=0; //number of dimensions
	if(myfile1.is_open())
	{
		while(getline(myfile1,line))
		{
			tokens1=tokenize ( line, delims );
			data[iter].setCoin(iter,tokens1);
			int x = data[iter].getCoinID();
			vector<string> dt = data[iter].getCoin();
			//cout << x << ";" ;
			for(vector<string>::iterator it = dt.begin();it != dt.end(); ++it)
			{
				//cout << (*it);
				cc++;
			}
			//cout << endl;
			iter++;
			dim = cc; //number of dimension in each line
			cc=0;
		}
		myfile1.close();
	}
	else
	{
		cout << "Unable to open!" << endl;
	}
	return dim;
}

int readLexicon(lexicon *data,char* path1) //read input file and store elements to Data array
{
	vector <string> tokens1;
	string delims = "\n\t\r";
	string line;
	ifstream myfile1(path1);
	int iter=0;
	if(myfile1.is_open())
	{
		while(getline(myfile1,line))
		{
			tokens1=tokenize ( line, delims );
			data[iter].setLexis(tokens1);
			string a = data[iter].getLexis();
			//cout << a << ";";
			double m = data[iter].getLexisMark();
			//cout << m << endl;
			iter++;
		}
		myfile1.close();
	}
	else
	{
		cout << "Unable to open!" << endl;
	}
	return 1;
}
int read1(Elements *data,char* path1) //read input file and store elements to Data array
{
	vector <string> tokens1;
	string delims = " \n\t,	";
	string line;
	ifstream myfile1(path1);
	int iter=0;
	int cc=0;
	int dim=0; //number of dimensions
	if(myfile1.is_open())
	{
		while(getline(myfile1,line))
		{
			tokens1=tokenize ( line, delims );
			data[iter].setValues(iter,tokens1);
			int x = data[iter].getID();
			vector<double> dt = data[iter].getVectorElem();
			for(vector<double>::iterator it = dt.begin();it != dt.end(); ++it)
			{
				cc++;
			}
			iter++;
			dim = cc; //number of dimension in each line
			cc=0;
		}
		myfile1.close();
	}
	else
	{
		cout << "Unable to open!" << endl;
	}
	return dim;
}

int read2(Elements *Qdata,char* path2) //read query file and store elements to QData array
{
	vector <string> Qtokens1;
	string delims = " \n\t";
	string Qline;
	int Qiter=0;
	int Qcc=0;
	int Qdim=0; //number of dimensions
	ifstream myfile2(path2);
 	if(myfile2.is_open())
	{
		//getline(myfile2,Qline); //proti grammh tou radius
		while(getline(myfile2,Qline))
		{
			Qtokens1=tokenize ( Qline, delims );
			//we get and extra 0 in the end of the vector and we have
			// to pop it out so we use pop_back()
			Qtokens1.pop_back();
			Qdata[Qiter].setValues(Qiter,Qtokens1);
			int Qx = Qdata[Qiter].getID();
			vector<double> Qdt = Qdata[Qiter].getVectorElem();
			for(vector<double>::iterator it = Qdt.begin();it != Qdt.end(); ++it)
			{
				Qcc++;
				//cout << (*it);
			}
			
			Qiter++;
			Qdim = Qcc; //number of dimension in each line
			Qcc=0; 
		}

		myfile2.close();
	}
	else
	{
		cout << "Unable to open!" << endl;
	}
	return Qdim;
}

void searchLSH(int search3L,vector<Elements*> x,vector<gElements> &gVec,vector<double> y2,int metric,gElements *Qdata,vector<MyDist> eucDistances[],int L,int z)
{
	search3L = 0; //search in bucket until 3L
	for(vector<Elements*>::iterator it = x.begin();it != x.end(); ++it)
	{
		int id1 = (*it)->getID(); //element id
		if(metric == 1) // eucledian
		{
			for(vector<gElements>::iterator it1 = gVec.begin();it1 != gVec.end(); ++it1)
			{
				int id2 = (*it1).ggetID(); // id from g vector
				if(id1 == id2)
				{
					vector<double> y1 = (*it1).ggetVectorElem(); //g from g vector
					if(vectorEquality(y1,y2)==1) //are y1 and y2 equal?
					{
						search3L++;
						if(metric == 1) //0 is for euclediean distance
						{
							vector<double> elem = (*it)->getVectorElem();
							vector<double> queryElem = Qdata->ggetVectorElem();
							double eucDist = calcEucledianDist(elem,queryElem);//calculate euclidean distance
							MyDist help((*it)->getID(),eucDist);
							eucDistances[z].push_back(help);
						}
					
					}	
					break;															
				}
			}
		}
		else //cosine
		{
			vector<double> elem = (*it)->getVectorElem();
			vector<double> queryElem = Qdata->ggetVectorElem();
			double cosineDist =cosine_similarity_vectors(elem,queryElem);//calculate cosine
			MyDist help((*it)->getID(),cosineDist);
			//if(cosineDist > 0)cout << "DIST:" << cosineDist << endl;
			eucDistances[z].push_back(help);
			search3L++;
		
		}
		if(search3L == (10*L))
		{
			break; //found elements in bucket with same g 
		}
	}
}

int searchHC(int M,vector<Elements*> x,vector<gElements> &gVec,vector<double> y2,int metric,gElements *Qdata,vector<MyDist> eucDistances[],int z)
{
	int flg=0; //search until you find M elements
	for(vector<Elements*>::iterator it = x.begin();it != x.end(); ++it)
	{
		int id1 = (*it)->getID(); //element id
		for(vector<gElements>::iterator it1 = gVec.begin();it1 != gVec.end(); ++it1)
		{
		int id2 = (*it1).ggetID(); // id from g vector
			if(id1 == id2)
			{
				vector<double> y1 = (*it1).ggetVectorElem(); //g from g vector
				if(vectorEquality(y1,y2)==1)
				{
					flg++;
					if(metric == 1) //0 is for euclediean distance
					{
						vector<double> elem = (*it)->getVectorElem();
						vector<double> queryElem = Qdata->ggetVectorElem();
						double eucDist = calcEucledianDist(elem,queryElem);//calculate eucledian diastance
						MyDist help((*it)->getID(),eucDist);
						eucDistances[z].push_back(help);
					}
					else
					{
						vector<double> elem = (*it)->getVectorElem();
						vector<double> queryElem = Qdata->ggetVectorElem();
						double cosineDist =cosine_similarity_vectors(elem,queryElem);//calculate cosine 
						MyDist help((*it)->getID(),cosineDist);
						eucDistances[z].push_back(help);
					}
				}	
				break;															
			}
		}
		if(flg == M)
		{
			break; //found M elements in bucket
		}
	}
	return flg;
}

vector<double> Esearch(int QcounterOfLines,int counterOfLines,Elements *data,Elements *Qdata,vector<double> EeucDistances[],int metric)//exhasustive search in one hashtable
{
	std::clock_t startQ,stopQ;	
	vector <double> times;
	for (int z=0;z<QcounterOfLines;z++)
	{
		startQ = std::clock();
		vector<double> query = Qdata[z].getVectorElem();
		for (int i=0;i<counterOfLines;i++) //number of queries
		{
			double x;
			vector<double> elem = data[i].getVectorElem();
			if(metric==1) x = calcEucledianDist(query,elem); //calucate euclidean distance
			else x =cosine_similarity_vectors(query,elem); //calculate cosine similarity
			EeucDistances[z].push_back(x);
		}
		if(metric==1) std::sort (EeucDistances[z].begin(),EeucDistances[z].end()); //sort the euclidean distance vector (min)
		else std::sort (EeucDistances[z].begin(),EeucDistances[z].end(),greater <double> ()); //sort the cosine similarity vector (max)
		stopQ = std::clock();
		double stopstart = (stopQ - startQ) / (double)(CLOCKS_PER_SEC / 1000);
		times.push_back(stopstart);
	}
	return times; //return the time needed for each query to do its exhasustive search
}

void sortAndPrintNN(int L,vector<MyDist> eucDistances[],vector<double> EDistances[],int r,char* outputpath,Elements *Qdata,double time,vector<double> times,vector<double> times2)
{
	ofstream myfile(outputpath); //create outputfile
 	myfile.is_open();	
	for(int q=0;q<L;q++)
	{
		std::sort (eucDistances[q].begin(), eucDistances[q].end(),min_dist()); //sort eucledian distnces
	}
	vector<MyDist>::iterator it89 = eucDistances[0].begin();
	double min_app = (*it89).dist; //minimun aproximate distance
	vector<double>::iterator it98 = EDistances[0].begin();
	double min_true = (*it98); // real minimum distance
	vector<double>::iterator it13 = times.begin();
	vector<double>::iterator it14 = times2.begin();
	if(r==0)
	{
		for(int qq=0;qq<L;qq++)
		{
			myfile << "Query: "<<Qdata[qq].getID()<<endl;
			vector<MyDist>::iterator it11 = eucDistances[qq].begin();
			vector<double>::iterator it12 = EDistances[qq].begin();
			myfile << "Nearest neighbor: " << (*it11).id << endl;
			myfile << "distanceLSH: "<<(*it11).dist<<endl;	
			myfile << "distanceTrue:" <<(*it12) <<endl;
			myfile << "tLSH:" << (*it13) << endl;
			myfile << "tTrue:" << (*it14) << endl;
			it13++;
			it14++;
			if((*it11).dist < min_app) min_app = (*it11).dist;
			if((*it12) < min_true) min_true = (*it12);
			myfile << endl;
		}
	}
	else
	{
		for(int y=0;y<L;y++)
		{
			myfile << "Query: "<<Qdata[y].getID()<<endl;
			myfile << "R-near neighbors:";
			for(vector<MyDist>::iterator it1 = eucDistances[y].begin();it1 != eucDistances[y].end(); ++it1)
			{
				if( (*it1).dist<= r )
				{
					myfile <<(*it1).id<< endl;
				}
			}
			vector<MyDist>::iterator it11 = eucDistances[y].begin();
			vector<double>::iterator it12 = EDistances[y].begin();
			myfile << "Nearest neighbor: " << (*it11).id << endl;
			myfile << "distanceLSH: "<<(*it11).dist<<endl;	
			myfile << "distanceTrue:" <<(*it12) <<endl;
			myfile << "tLSH:" << (*it13) << endl;
			myfile << "tTrue:" << (*it14) << endl;
			it13++;
			it14++;
			if((*it11).dist < min_app) min_app = (*it11).dist;
			if((*it12) < min_true) min_true = (*it12);
			myfile << endl;
			
		}
	}	
	myfile<<"\n" << endl;
	myfile << "Max Approximate Ratio:" << min_app/min_true<<endl;
	myfile << "Average Search Time:" << time / L << endl;	
		
}

void sortAndPrintCosine(int L,vector<MyDist> eucDistances[],vector<double> EDistances[],int r,char* outputpath,Elements *Qdata,double time,vector<double> times,vector<double> times2)
{
	
	ofstream myfile(outputpath); //create outputfile
 	myfile.is_open();	
	for(int q=0;q<L;q++)
	{
		std::sort (eucDistances[q].begin(), eucDistances[q].end(),max_cosine());//sort cosine similarity
	}
	vector<MyDist>::iterator it89 = eucDistances[0].begin();
	double max_app = (*it89).dist; //max approximate similarity
	vector<double>::iterator it98 = EDistances[0].begin();
	double max_true = (*it98); //real max cosine similarity
	vector<double>::iterator it13 = times.begin();
	vector<double>::iterator it14 = times2.begin();
	if(r==0)
	{
		for(int qq=0;qq<L;qq++)
		{
			myfile << "Query: "<<Qdata[qq].getID()<<endl;
			vector<MyDist>::iterator it11 = eucDistances[qq].begin();
			vector<double>::iterator it12 = EDistances[qq].begin();
			myfile << "Nearest cosine similarity neighbor: " << (*it11).id << endl;
			myfile << "cosineSimilarity: "<<(*it11).dist<<endl;	
			myfile << "cosineSimilarityTrue:" <<(*it12) <<endl;
			myfile << "tCOSINE:" << (*it13) << endl;
			myfile << "tTrue:" << (*it14) << endl;
			it13++;
			it14++;
			if((*it11).dist > max_app) max_app = (*it11).dist;
			if((*it12) > max_true) max_true = (*it12);
			myfile << endl;
		}
	}
	else
	{
		for(int y=0;y<L;y++)
		{
			myfile << "Query: "<<Qdata[y].getID()<<endl;
			myfile << "R-Cosine Similarity: ";
			for(vector<MyDist>::iterator it1 = eucDistances[y].begin();it1 != eucDistances[y].end(); ++it1)
			{
				if( (*it1).dist<= r )
				{
					myfile <<(*it1).id<< endl  ;	
				}
			}
			vector<MyDist>::iterator it11 = eucDistances[y].begin();
			vector<double>::iterator it12 = EDistances[y].begin();
			myfile << "Nearest cosine similarity neighbor: " << (*it11).id << endl;
			myfile << "cosineSimilarity: "<<(*it11).dist<<endl;	
			myfile << "cosineSimilarityTrue:" <<(*it12) <<endl;
			myfile << "tCOSINE:" << (*it13) << endl;
			myfile << "tTrue:" << (*it14) << endl;
			it13++;
			it14++;
			if((*it11).dist > max_app) max_app = (*it11).dist;
			if((*it12) > max_true) max_true = (*it12);
			myfile << endl;
		}
	}	
	myfile << "\n" << endl;
	myfile << "Max Approximate Ratio:" << max_app/max_true<<endl;;
	myfile << "Average Search Time:" << time / L << endl;	
}

int searchID(int x,Elements *data,int counterOfLines)
{
	for(int i=0;i<counterOfLines;i++)
	{
		if(x == data[i].getID())
			return i;
	}
}




