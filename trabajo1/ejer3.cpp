#include <bits/stdc++.h>

using namespace std;

int main(){
    int MAX = 800;
    unsigned t0, t1;
    double tiempo;
    int A[MAX][MAX],B[MAX][MAX],C[MAX][MAX];

    for(int i =0;i<MAX;i++)
        for(int j=0;j<MAX;j++){
            A[i][j]=1+rand()%(101-1);
            B[i][j]=1+rand()%(101-1);
        }
            

    // multiplicar matrices por bloques  
    t0=clock();
    int bloque =10;
    for(int i0=0; i0<MAX; i0+=bloque)
		for(int j0=0; j0<MAX; j0+=bloque)
	        for(int z0=0; z0<MAX; z0+=bloque)
	            for (int i = i0; i < min(i0 + bloque, MAX); ++i)
	            	for (int j = j0; j < min(j0 + bloque, MAX); ++j)
	            		for (int k = z0; k < min(z0 + bloque, MAX); ++k)
	            			C[i][j] += A[i][k] * B[k][j];

    t1 = clock();
    tiempo = (double(t1-t0)/CLOCKS_PER_SEC);
    cout<<"Demora con "<< MAX <<" datos : "<< tiempo <<endl;
    t0 = t1 =0;

}