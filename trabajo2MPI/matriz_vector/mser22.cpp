#include <bits/stdc++.h>
#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <time.h>

using namespace std;

void LLenarMatriz(int ){

}

int main(void){
    MPI_Comm comm;
    double start, finish, loc_elapsed, elapsed;
    int my_rank,comm_sz;
    comm = MPI_COMM_WORLD;
    
    MPI_Init(NULL, NULL);
	MPI_Comm_rank(comm, &my_rank);
	MPI_Comm_size(comm, &comm_sz); 

    int MAX = 8000;
 
    int *A = NULL;
    int *x = NULL;
    int *y = NULL;

    A = new int[MAX*MAX];
    x = new int[MAX];
    y = new int[MAX];

    for (int i = 0; i < MAX; i++)
      for (int j = 0; j < MAX; j++) 
        A[i*MAX + j] = 1+rand()%(101-1);
    
    for(int i=0;i<MAX;i++)
   	    x[i]=1+rand()%(101-1);

    //tiempo
    
    MPI_Barrier(comm);
    start = MPI_Wtime();
    
    int *x2;
    x2 = new int[MAX];
    MPI_Allgather(x, MAX, MPI_INT, x2, MAX, MPI_DOUBLE, comm);

    int m=MAX;
    int n=MAX;
    for (int k = 0; k < m; k++) {
        y[k] = 0;
        for (int l = 0; l < n; l++){
            y[k] += A[(k*n)+l]*x[l];
        }
    }
   
    finish = MPI_Wtime();
    loc_elapsed = finish-start;
    MPI_Reduce(&loc_elapsed, &elapsed, 1, MPI_DOUBLE, MPI_MAX, 0, comm);
    
    if (my_rank == 0)
      cout<<"Tiempo de demora = "<< elapsed<<endl;

    delete [] A; // liberamos la memoria 
    delete [] x;
    delete [] y;
    A = NULL;
    x = NULL;
    y = NULL;

    MPI_Finalize();
}
