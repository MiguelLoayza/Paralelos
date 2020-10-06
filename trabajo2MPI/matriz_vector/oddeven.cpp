#include <bits/stdc++.h>
#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <time.h>

using namespace std;

void Odd_even_sort(
      int  a[]  /* in/out */, 
      int  n    /* in     */) {
   int phase, i, temp;

   for (phase = 0; phase < n; phase++) 
      if (phase % 2 == 0) { /* Even phase */
         for (i = 1; i < n; i += 2) 
            if (a[i-1] > a[i]) {
               temp = a[i];
               a[i] = a[i-1];
               a[i-1] = temp;
            }
      } else { /* Odd phase */
         for (i = 1; i < n-1; i += 2)
            if (a[i] > a[i+1]) {
               temp = a[i];
               a[i] = a[i+1];
               a[i+1] = temp;
            }
      }
} 

int main(){
    MPI_Comm comm;
    double start, finish, loc_elapsed, elapsed;
    int my_rank,comm_sz;
    comm = MPI_COMM_WORLD;
    
    MPI_Init(NULL, NULL);
	MPI_Comm_rank(comm, &my_rank);
	MPI_Comm_size(comm, &comm_sz); 

    int  n;
    int* a;
    
    a = new int[n];

    n=100;

    for(int i=0;i<n;i++)
   	    a[i]=1+rand()%(101-1);
    

    MPI_Barrier(comm);
    start = MPI_Wtime();
    
    Odd_even_sort(a, n);
   
    finish = MPI_Wtime();
    loc_elapsed = finish-start;
    MPI_Reduce(&loc_elapsed, &elapsed, 1, MPI_DOUBLE, MPI_MAX, 0, comm);
    
    if (my_rank == 0)
      cout<<"Tiempo de demora = "<< elapsed * 1000 <<endl;

    delete [] a;
    a = NULL;

    MPI_Finalize();
    return 0;
}


