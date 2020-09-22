#include <bits/stdc++.h>

using namespace std;

int main(){
    int MAX = 100;
    unsigned t0, t1;
    double tiempo;
    int A[MAX][MAX],B[MAX][MAX],C[MAX][MAX];

    for(int i =0;i<MAX;i++)
        for(int j=0;j<MAX;j++){
            A[i][j]=1+rand()%(101-1);
            B[i][j]=1+rand()%(101-1);
        }
            

    // multiplicar matrices clasica  
    t0=clock();   //
    for (int i=1;i<=MAX;i++)
        for (int j=1;j<=MAX;j++){ 
            C[i][j]=0;
            for (int k=1;k<=MAX;k++)
                C[i][j]=C[i][j]+A[i][k]*B[k][j];
          }
    t1 = clock();
    tiempo = (double(t1-t0)/CLOCKS_PER_SEC);
    cout<<"Demora con "<< MAX <<" datos : "<< tiempo <<endl;
    t0 = t1 =0;

}