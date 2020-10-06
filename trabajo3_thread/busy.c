#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#include "tiempo.h"

const int MAX_THREADS = 1024;

long thread_count;
long long n;
int flag;
double sum;

void* Thread_sum(void* rank);

void Get_args(int argc, char* argv[]);
void Usage(char* prog_name);
double Serial_pi(long long n);

int main(int argc, char* argv[]) {
   long       thread;  
   pthread_t* thread_handles;
   double start, finish, elapsed;
   
   Get_args(argc, argv);

   thread_handles = (pthread_t*) malloc (thread_count*sizeof(pthread_t)); 
   
   GET_TIME(start);
   sum = 0.0;
   flag = 0;
   for (thread = 0; thread < thread_count; thread++)  
      pthread_create(&thread_handles[thread], NULL,
          Thread_sum, (void*)thread);  

   for (thread = 0; thread < thread_count; thread++) 
      pthread_join(thread_handles[thread], NULL); 
   GET_TIME(finish);
   elapsed = finish - start;

   sum = 4.0*sum;
   printf("Numero de n = %lld de terminos usados,\n", n);
   printf("   Multi-threaded valor calculado para pi  = %.15f\n", sum);
   printf("   Tiempo de demora = %e secgundos\n", elapsed);
   printf(" -----------------------------------------------------------------\n");

   
   GET_TIME(start);
   sum = Serial_pi(n);
   GET_TIME(finish);
   elapsed = finish - start;
   printf(" Single-threaded valor calculado para pi = %.15f\n", sum);
   printf("   Tiempo de demora = %e secgundos\n", elapsed);
   printf(" -----------------------------------------------------------------\n");
   printf(" Valor con lalibreria Math = %.15f\n", 4.0*atan(1.0));
   
   free(thread_handles);
   return 0;
} 

void* Thread_sum(void* rank) {
   long my_rank = (long) rank;
   double factor;
   long long i;
   long long my_n = n/thread_count;
   long long my_first_i = my_n*my_rank;
   long long my_last_i = my_first_i + my_n;

   if (my_first_i % 2 == 0)
      factor = 1.0;
   else
      factor = -1.0;

   for (i = my_first_i; i < my_last_i; i++, factor = -factor) {
      while (flag != my_rank);
      sum += factor/(2*i+1);  
      flag = (flag+1) % thread_count;
   }

   return NULL;
}

double Serial_pi(long long n) {
   double sum = 0.0;
   long long i;
   double factor = 1.0;

   for (i = 0; i < n; i++, factor = -factor) {
      sum += factor/(2*i+1);
   }
   return 4.0*sum;

} 


void Get_args(int argc, char* argv[]) {
   if (argc != 3) Usage(argv[0]);
   thread_count = strtol(argv[1], NULL, 10);  
   if (thread_count <= 0 || thread_count > MAX_THREADS) Usage(argv[0]);
   n = strtoll(argv[2], NULL, 10);
   if (n <= 0) Usage(argv[0]);
} 


void Usage(char* prog_name) {
   fprintf(stderr, "usage: %s <number of threads> <n>\n", prog_name);
   fprintf(stderr, "   n is the number of terms and should be >= 1\n");
   fprintf(stderr, "   n should be evenly divisible by the number of threads\n");
   exit(0);
}
