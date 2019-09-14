#ifndef ASSIGNMENTS_H
#define ASSINGMENTS_H


void fillclustersLoyds(vector <double> cen[],int k,Elements *data,hashTable &clusters,int counterOfLines,int num,int metricN);
void miniLoyds(vector <double> cen[],int k,Elements *data,hashTable &clusters,int counterOfLines,int i,int metricN);
void fillclustersLsh(int L,default_random_engine &e,vector <double> cen[],int k,Elements *data,hashTable &clusters,int counterOfLines,int num,int metricN,int dim,int hf);
void fillclustersHC(int L,default_random_engine &e,vector <double> cen[],int k,Elements *data,hashTable &clusters,int counterOfLines,int num,int metricN,int dim,int hf,int M,int probes);
#endif
