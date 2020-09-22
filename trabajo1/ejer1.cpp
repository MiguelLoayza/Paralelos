#include <bits/stdc++.h>

using namespace std;

int MAX = 1000;

int main(){

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
    tiempo = (double(t1-t0)/CLOCKS_PER_SEC);
    cout<<"1er for demora :"<< tiempo <<endl;
    t0 = t1 =0;


    t0=clock();   //Segundo bucle

    auto begin2 = std::chrono::high_resolution_clock::now();
    for(int j=0;j<MAX;j++)
        for(int i=0;i<MAX;i++)
            y[i]+=A[i][j]*x[j];

    t1 = clock();
    tiempo = (double(t1-t0)/CLOCKS_PER_SEC);
    cout<<"2do for demora :"<< tiempo <<endl;   

}
