#include <bits/stdc++.h>
#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <time.h>

using namespace std;

void Get_dims(int* m_p,int* local_m_p, int* n_p, int* local_n_p, int my_rank ,int comm_sz ,MPI_Comm  comm ,int max) {
    
    if (my_rank == 0) {
      *m_p = max;
      *n_p = max;
   }

   MPI_Bcast(m_p, 1, MPI_INT, 0, comm);
   MPI_Bcast(n_p, 1, MPI_INT, 0, comm);

   *local_m_p = *m_p/comm_sz;
   *local_n_p = *n_p/comm_sz;
}

void Mat_vect_mult(
      int    local_A[] , 
      int    local_x[] , 
      int    local_y[] ,
      int       local_m   , 
      int       n         ,
      int       local_n   ,
      MPI_Comm  comm      ) {
    
    int *x;
    x= new int[n];
    MPI_Allgather(local_x, local_n, MPI_INT, x, local_n, MPI_INT, comm);
    
    for (int k = 0; k < local_m; k++) {
        local_y[k] = 0;
        for (int l = 0; l < n; l++){
            local_y[k] += local_A[k*n+l]*x[l];
        }
    }
    delete [] x;
    x = NULL;
}


int main(void){
    MPI_Comm comm;
    double start, finish, loc_elapsed, elapsed;
    int m, local_m, n, local_n;
    int my_rank,comm_sz;
    comm = MPI_COMM_WORLD;
    
    MPI_Init(NULL, NULL);
	MPI_Comm_rank(comm, &my_rank);
	MPI_Comm_size(comm, &comm_sz); 

    int MAX = 8192;
    Get_dims(&m, &local_m, &n, &local_n, my_rank, comm_sz, comm,MAX);
    
 
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
    
    Mat_vect_mult(A, x, y, local_m, n, local_n, comm);
   
    finish = MPI_Wtime();
    loc_elapsed = finish-start;
    MPI_Reduce(&loc_elapsed, &elapsed, 1, MPI_DOUBLE, MPI_MAX, 0, comm);
    
    if (my_rank == 0)
      cout<<"Tiempo de demora = "<< elapsed * 1000 <<endl;

    delete [] A; // liberamos la memoria 
    delete [] x;
    delete [] y;
    A = NULL;
    x = NULL;
    y = NULL;

    MPI_Finalize();
    return 0;
}


/*
int main(){
    int MAX = 8000;
    unsigned t0, t1;
    double tiempo;

    int *A = NULL;
    int *x = NULL;
    int *y = NULL;

    A = new int[MAX*MAX];
    x = new int[MAX];
    y = new int[MAX];

    for(int i =0;i<MAX*MAX;i++)
        A[i]=1+rand()%(101-1);
    
    for(int i=0;i<MAX;i++)
   	    x[i]=1+rand()%(101-1);

    t0=clock();   //Primer bucle
    for (int k = 0; k < MAX; k++) {
        y[k] = 0;
        for (int l = 0; l < MAX; l++)
            y[k] += A[(k*MAX)+l]*x[l];
    }

    t1 = clock();
    tiempo = (double(t1-t0)/CLOCKS_PER_SEC)*1000;
    cout<<"1er Bucle demora :"<< tiempo <<endl;
    //printf("%d",tiempo);
    t0 = t1 =0;

    delete [] A; // liberamos la memoria de la cadena
    delete [] x;
    delete [] y;
    A = NULL;
    x = NULL;
    y = NULL;
}

*/