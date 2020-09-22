#include <bits/stdc++.h>

using namespace std;

int main(){
    int MAX = 1000;
    unsigned t0, t1;
    double tiempo;
    int A[MAX][MAX];
    int x[MAX];
    int y[MAX];
    for(int i =0;i<MAX;i++)
        for(int j=0;j<MAX;j++)
            A[i][j]=1+rand()%(101-1);
       
       
    for(int i=0;i<MAX;i++)
   	    x[i]=1+rand()%(101-1);
   
    t0=clock();   //Primer bucle
    for(int i=0;i<MAX;i++)
        for(int j=0;j<MAX;j++)
            y[i]+=A[i][j]*x[j];
    t1 = clock();
    tiempo = (double(t1-t0)/CLOCKS_PER_SEC)*1000;
    cout<<"1er Bucle demora :"<< tiempo <<endl;
    t0 = t1 =0;

    t0=clock();   //Segundo bucle
    for(int j=0;j<MAX;j++)
        for(int i=0;i<MAX;i++)
            y[i]+=A[i][j]*x[j];

    t1 = clock();
    tiempo = (double(t1-t0)/CLOCKS_PER_SEC)*1000;
    cout<<"2do Bucle demora :"<< tiempo <<endl;   
}
