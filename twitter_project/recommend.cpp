#include "recommend.h"

bool checkPegs(vector <double> array) //check if a vector is full of zeros 
{
	for(vector<double>::iterator it2 = array.begin();it2 != array.end(); ++it2)
	{
		if((*it2) != 0.0)
		{
			return false;
		}
		if((*it2) != 0)
		{
			return false;
		}
	}
	return true;
}

void makeOutput1(char* outputpath,int z, Elements * newData,tweetElem * data,vector<int> NNids[],vector <int> kcoins[],coinElem* coinData,int size,int p, int coinCounter,double time,double time2,hashTable &clusters,vector <double> centroids[],int k,hashTable &clusters1,vector <double> centroids1[],int k1,int tweetCounter,hashTable &clusters2,vector <double> centroids2[],int k2)
{
		//////////////////////////////////////////////lsh/////////////////////////////////////////////////////////////////////
	ofstream myfile(outputpath); //create outputfile
 	myfile.is_open();	
	myfile << "Cosine LSH" << endl;
	//int iter=0;
	vector <MyDist> * coinsIDs;
	coinsIDs = new vector<MyDist> [size];
	for(int q=0;q<size;q++)
	{
		//find similarity between user and the p closest to him
		vector <double> userVector = newData[q].getVectorElem();
		int vsz = userVector.size();
		//get the id from the nearest neighbors
		double  sumSimilarity = 0.0;
		double sum = 0.0;
		int iter=0;
		int zerof=0;
		if(!checkPegs(userVector)){zerof=1;}
		while(iter < vsz) //create the recommandation vector CoinsIDs which contains the vectors with coins that the users did not refer to
		{
			sumSimilarity = 0.0;
			sum = 0.0;
			if(zerof == 1)
			{
				for(vector<int>::iterator it2 = NNids[q].begin();it2 != NNids[q].end(); ++it2)
				{		
					int idnn = (*it2);
					for(int q1=0;q1<size;q1++)
					{	
						int idnn2 = newData[q1].getID();
						if(idnn == idnn2)
						{
							//find similarity
							vector <double> NNvector = newData[q1].getVectorElem();
							double sm = cosine_similarity_vectors(userVector,NNvector);		
							//add to the sum similarities 	
							sumSimilarity += sm;
							//make the sum of similarity * element of vector 
							sum = sum + (NNvector[iter] * sm);
							break;
						}
					}
				}
			}
			int flg=0;
			for(vector<int>::iterator it22 = kcoins[q].begin();it22 != kcoins[q].end(); ++it22) //if the user refered to that coin dont add it to the CoinsIDs
			{
				if(iter == (*it22))
				{
					flg = 1;
				}
			}
			if(flg==0)	
			{
				if(sumSimilarity>0)
				{
					MyDist help(iter,sum/sumSimilarity);
					coinsIDs[q].push_back(help);
				}	
				else
				{
					MyDist help(iter,0);
					coinsIDs[q].push_back(help);
				}		
			}
			iter++;		
		}
	}
	for(int q=0;q<size;q++)
	{
		std::sort (coinsIDs[q].begin(), coinsIDs[q].end(),max_cosine());//sort cosine similarity
	}
	myfile << "problem A" << endl;
	for(int q=0;q<size;q++)
	{
		myfile << "<u" << q+1 << ">   " ; 
		vector<MyDist>::iterator it123 = coinsIDs[q].begin();
		for(int i=0;i<5;i++)
		{
			for(int y=0;y<coinCounter;y++)
			{
				if((*it123).id == coinData[y].getCoinID())
				{
					vector <string> crypto = coinData[y].getCoin();
					vector<string>::iterator cit = crypto.begin();
					myfile << (*cit) << "   "  ;break;
				}
			}
			it123++;
		}
		myfile << endl;
	}
	myfile << "problem B" << endl;
	//create the C j's 
	std::clock_t start11,stop11;
	start11 = std::clock();
	Elements * Cj1;
	Cj1 = new Elements[k1];
	vector <double> * h1;
	vector <int> valid1; //valid are the clusters that are not empty
	h1 = new vector <double>[k1];

	for(int i=0;i<k1;i++)
	{
		vector<Elements*> x1 = clusters1.getVector(i);
		int size1 = x1.size();
		if(size1==0){/*cout << "EMPTY_CLUSTER" << endl;*/continue;}
		int iter = 0;
		while(iter < coinCounter)
		{
			double sum = 0.0;
			for(vector<Elements*>::iterator itx1 = x1.begin();itx1 != x1.end(); ++itx1)
			{
				int tweetid1 = (*itx1)->getID();
				vector <double> uv;
				for(int y=0;y<tweetCounter;y++) // search for tweet id in new dataset
				{
					if(data[y].twgetTWID() == tweetid1) 
					{
						int id1 = data[y].twgetID();
						for(int z=0;z<size;z++)
						{
							if(id1 == newData[z].getID())
							{	
								uv = newData[z].getVectorElem();
								break;
							}
						}
						break;
					}
				}
				sum += uv[iter];
			}
			h1[i].push_back(sum);
			iter++;
		}
		Cj1[i].setValues2(i,h1[i]); //create the Cjs for each cluster
		valid1.push_back(i); 
	}

	vector <MyDist> * coinsIDsA2h; //contains the p nearest cjs to the user vector
	coinsIDsA2h = new vector<MyDist> [size];
	for(int i=0;i<size;i++)
	{
		vector <double> userVector = newData[i].getVectorElem();
		vector <double> v;
		int iter=0;
		for(int y=0;y<k1;y++)
		{
			for(vector<int>::iterator it = valid1.begin();it != valid1.end(); ++it)
			{
				if((*it) == y)
				{	
					vector <double> v1 = Cj1[y].getVectorElem();
 					double newmin = cosine_distance_vectors(userVector,v1);
					MyDist help(y,newmin);
					coinsIDsA2h[i].push_back(help);
					break;
				}
			}
		}
	}

	for(int q=0;q<size;q++)
	{
		std::sort (coinsIDsA2h[q].begin(), coinsIDsA2h[q].end(),min_dist()); //sort distnces
	}
	vector <MyDist> * coinsIDsA2;
	coinsIDsA2 = new vector<MyDist> [size];

	for(int q=0;q<size;q++)
	{
		//find similarity between user and the p closest to him
		vector <double> userVector = newData[q].getVectorElem();
		int vsz = userVector.size();
		//get the id from the nearest neighbors
		double  sumSimilarity = 0.0;
		double sum = 0.0;
		int iter=0;
		int pcounter=0;
		int zerof=0;
		if(!checkPegs(userVector)){zerof=1;}
		while(iter < vsz) //same block as above
		{
			sumSimilarity = 0.0;
			sum = 0.0;
			if(zerof==1)
			{
				for(vector<MyDist>::iterator it321 = coinsIDsA2h[q].begin();it321!= coinsIDsA2h[q].end(); ++it321)
				{		
						//find similarity
						int idnn = (*it321).id;
						vector <double> NNvector = Cj1[idnn].getVectorElem();
						double sm = cosine_similarity_vectors(userVector,NNvector);		
						//add to the sum similarities 	
						sumSimilarity += sm;
						//make the sum of similarity * element of vector 
						sum = sum + (NNvector[iter] * sm);
						pcounter++;
						if(pcounter==p){ break;} //when we get the P closest Cjs for each user break
				}
			}
			int flg=0;
			for(vector<int>::iterator it43 = kcoins[q].begin();it43 != kcoins[q].end(); ++it43)
			{
				if(iter == (*it43))
				{
					flg = 1;
				}
			}
			if(flg==0)	
			{
				if(sumSimilarity>0)
				{
					MyDist help(iter,sum/sumSimilarity);
					coinsIDsA2[q].push_back(help);
				}	
				else
				{
					MyDist help(iter,0);
					coinsIDsA2[q].push_back(help);
				}		
			}
			iter++;		
		}
	} 

	for(int q=0;q<size;q++)
	{
		std::sort (coinsIDsA2[q].begin(), coinsIDsA2[q].end(),max_cosine());//sort cosine similarity
	}
	for(int q=0;q<size;q++)
	{
		myfile << "<u" << q+1 << ">   " ; 
		vector<MyDist>::iterator it123 = coinsIDsA2[q].begin();
		for(int i=0;i<2;i++)
		{
			for(int y=0;y<coinCounter;y++)
			{
				if((*it123).id == coinData[y].getCoinID())
				{
					vector <string> crypto = coinData[y].getCoin();
					vector<string>::iterator cit = crypto.begin();
					myfile << (*cit) << "   "  ;break;
				}
			}
			it123++;
		}
		myfile << endl;
	}
	stop11 = std::clock();
	double time121 = (stop11 - start11) / (double)(CLOCKS_PER_SEC / 1000);
	myfile << "Execution Time<" << time + time121 << ">" << endl ; 
	//////////////////////////////////////////////clustering/////////////////////////////////////////////////////////////////////
	myfile << "problem A" << endl;
	
	std::clock_t start1,stop1;
	start1 = std::clock();
	int * Cids;
	Cids = new int [size];
	for(int i=0;i<size;i++)
	{Cids[i] = -1;}
	vector <MyDist> * coinsIDsB1;
	coinsIDsB1 = new vector<MyDist> [size];
	for(int i=0;i<size;i++)
	{
		int flg1=0;
		for(int y=0;y<k1;y++)
		{
			vector<Elements*> x1 = clusters.getVector(y);
			int size1 = x1.size();
			if(size1==0){/*cout << "EMPTY_CLUSTER" << endl;*/continue;}
			for(vector<Elements*>::iterator itx1 = x1.begin();itx1 != x1.end(); ++itx1)
			{
				int id = (*itx1)->getID();
				if(newData[i].getID() == id)
				{
					Cids[i] = y; //cluster that the user belongs
					flg1=1;
					break;
				}
			}
			if(flg1==1){ break;}
		}		
	}
	for(int i=0;i<size;i++)
	{if(Cids[i]==-1){cout << Cids[i] << ":" << i << endl;}}//exit(-1);
	//for every user we get the users from the same cluster to recommend
	for(int i=0;i<size;i++)
	{
		int clusterID = Cids[i];
		//cout << clusterID << endl;
		int userID = newData[i].getID();
		cout << "UserID:" << userID << endl;
		vector <double> userVector = newData[i].getVectorElem();
		int vsz = userVector.size();
		vector<Elements*> x1 = clusters.getVector(clusterID);
		int iter=0;
		double sumSimilarity = 0.0;
		double sum = 0.0;
		int zerof=0;
		if(!checkPegs(userVector)){zerof =1;}
		while(iter < vsz)
		{
			sumSimilarity = 0.0;
			sum = 0.0;
			if(zerof == 1)
			{
				for(vector<Elements*>::iterator itx1 = x1.begin();itx1 != x1.end(); ++itx1)
				{
					if(checkPegs((*itx1)->getVectorElem())){continue;}
					if( (*itx1)->getID() != userID )
					{
						int idnn = (*itx1)->getID();
						for(int q1=0;q1<size;q1++)
						{	
							int idnn2 = newData[q1].getID();
							if(idnn == idnn2)
							{
								//find similarity
								vector <double> vector = newData[q1].getVectorElem();
								double sm = cosine_similarity_vectors(userVector,vector);		
								//add to the sum similarities 	
								sumSimilarity += sm;
								//make the sum of similarity * element of vector 
								sum = sum + (vector[iter] * sm);
								break;
							}
						}
					}		
				}
			}
			int flg=0;
			for(vector<int>::iterator it22 = kcoins[i].begin();it22 != kcoins[i].end(); ++it22)
			{
				if(iter == (*it22))
				{
					flg = 1;
				}
			}
			if(flg==0)	
			{
				if(sumSimilarity>0)
				{
					MyDist help(iter,sum/sumSimilarity);
					coinsIDsB1[i].push_back(help);
				}	
				else
				{
					MyDist help(iter,0);
					coinsIDsB1[i].push_back(help);
				}		
			}
			iter++;	
		}
	}
	for(int q=0;q<size;q++)
	{
		std::sort (coinsIDsB1[q].begin(), coinsIDsB1[q].end(),max_cosine());//sort cosine similarity
	}
	for(int q=0;q<size;q++)
	{
		myfile << "<u" << q+1 << ">   " ; 
		vector<MyDist>::iterator it123 = coinsIDsB1[q].begin();
		for(int i=0;i<5;i++)
		{
			for(int y=0;y<coinCounter;y++)
			{
				if((*it123).id == coinData[y].getCoinID())
				{
					vector <string> crypto = coinData[y].getCoin();
					vector<string>::iterator cit = crypto.begin();
					myfile << (*cit) << "   "  ;break;
				}
			}
			it123++;
		}
		myfile << endl;
	}

	myfile << "problem B" << endl;
	//create the C j's 
	Elements * Cj;
	Cj = new Elements[k2];
	vector <double> * h;
	vector <int> valid; //valid are the clusters that are not empty
	h = new vector <double>[k2];
	
	for(int i=0;i<k2;i++)
	{
		vector<Elements*> x1 = clusters2.getVector(i);
		int size1 = x1.size();
		if(size1==0){/*cout << "EMPTY_CLUSTER" << endl;*/continue;}
		int iter = 0;
		while(iter < coinCounter)
		{
			double sum = 0.0;
			for(vector<Elements*>::iterator itx1 = x1.begin();itx1 != x1.end(); ++itx1)
			{
				int tweetid1 = (*itx1)->getID();
				vector <double> uv;
				for(int y=0;y<tweetCounter;y++) // search for tweet id in new dataset
				{
					if(data[y].twgetTWID() == tweetid1) 
					{
						int id1 = data[y].twgetID();
						for(int z=0;z<size;z++)
						{
							if(id1 == newData[z].getID())
							{	
								uv = newData[z].getVectorElem();
								break;
							}
						}
						break;
					}
				}
				sum += uv[iter];
			}
			h[i].push_back(sum);
			iter++;
		}
		Cj[i].setValues2(i,h[i]);
		valid.push_back(i);
		//cout << "h1[]:"<<h[i].size()  << ":" << i << endl;
	}

	vector <MyDist> * coinsIDsB2h;
	coinsIDsB2h = new vector<MyDist> [size];
	for(int i=0;i<size;i++)
	{
		vector <double> userVector = newData[i].getVectorElem();
		vector <double> v;
		int iter=0;
		for(int y=0;y<k2;y++)
		{
			for(vector<int>::iterator it = valid.begin();it != valid.end(); ++it)
			{
				if((*it) == y)
				{	
					vector <double> v1 = Cj[y].getVectorElem();
 					double newmin = calcEucledianDist(userVector,v1);
					MyDist help(y,newmin);
					coinsIDsB2h[i].push_back(help);
					break;
				}
			}
		}
	}

	for(int q=0;q<size;q++)
	{
		std::sort (coinsIDsB2h[q].begin(), coinsIDsB2h[q].end(),min_dist()); //sort distnces
	}
	vector <MyDist> * coinsIDsB2;
	coinsIDsB2 = new vector<MyDist> [size];

	for(int q=0;q<size;q++)
	{
		//find similarity between user and the p closest to him
		vector <double> userVector = newData[q].getVectorElem();
		int vsz = userVector.size();
		//get the id from the nearest neighbors
		double  sumSimilarity = 0.0;
		double sum = 0.0;
		int iter=0;
		int pcounter=0;
		int zerof = 0;
		if(!checkPegs(userVector)){zerof = 1;}
		while(iter < vsz) //same block as above
		{
			sumSimilarity = 0.0;
			sum = 0.0;
			if(zerof == 1)
			{
				for(vector<MyDist>::iterator it321 = coinsIDsB2h[q].begin();it321!= coinsIDsB2h[q].end(); ++it321)
				{		
						//find similarity
						int idnn = (*it321).id;
						vector <double> NNvector = Cj[idnn].getVectorElem();
						double sm = cosine_similarity_vectors(userVector,NNvector);		
						//add to the sum similarities 	
						sumSimilarity += sm;
						//make the sum of similarity * element of vector 
						sum = sum + (NNvector[iter] * sm);
						pcounter++;
						if(pcounter==1){ break;}
				}
			}
			int flg=0;
			for(vector<int>::iterator it43 = kcoins[q].begin();it43 != kcoins[q].end(); ++it43)
			{
				if(iter == (*it43))
				{
					flg = 1;
				}
			}
			if(flg==0)	
			{
				if(sumSimilarity>0)
				{
					MyDist help(iter,sum/sumSimilarity);
					coinsIDsB2[q].push_back(help);
				}	
				else
				{
					MyDist help(iter,0);
					coinsIDsB2[q].push_back(help);
				}		
			}
			iter++;		
		}
	} 

	for(int q=0;q<size;q++)
	{
		std::sort (coinsIDsB2[q].begin(), coinsIDsB2[q].end(),max_cosine());//sort cosine similarity
	}
	for(int q=0;q<size;q++)
	{
		myfile << "<u" << q+1 << ">   " ; 
		vector<MyDist>::iterator it123 = coinsIDsB2[q].begin();
		for(int i=0;i<2;i++)
		{
			for(int y=0;y<coinCounter;y++)
			{
				if((*it123).id == coinData[y].getCoinID())
				{
					vector <string> crypto = coinData[y].getCoin();
					vector<string>::iterator cit = crypto.begin();
					myfile << (*cit) << "   "  ;break;
				}
			}
			it123++;
		}
		myfile << endl;
	}	

	stop1 = std::clock();
	double time12 = (stop1 - start1) / (double)(CLOCKS_PER_SEC / 1000);
	myfile << "Execution Time  <" << time2 + time12 << ">" << endl ; 
	
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	myfile.close();
	delete[] coinsIDs;
	delete[] coinsIDsB1;
	delete[] coinsIDsB2h;
	delete[] coinsIDsB2;
	delete[] coinsIDsA2h;
	delete[] coinsIDsA2;
	delete[] h;
	delete[] h1;
	delete[] Cj;
	delete[] Cj1;
	delete[] Cids;
}

