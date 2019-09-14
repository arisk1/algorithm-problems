#ifndef UPDATE_H
#define UPDATE_H

void kmeans(hashTable &clusters,int k,vector <double> cen[]);
void pam(hashTable &clusters,int k,vector <double> cen[],Elements * data,int counterOfLines,double newobj[],double oldobj[],int help[],int metricN);
#endif
