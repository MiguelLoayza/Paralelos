#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "tiempo.h"

#define BARRIER_COUNT 100

int thread_count;
int barrier_thread_count = 0;
pthread_mutex_t barrier_mutex;
pthread_cond_t ok_to_proceed;

void Usage(char* prog_name);
void *Thread_work(void* rank);

int main(int argc, char* argv[]) {
   long       thread;
   pthread_t* thread_handles; 
   double start, finish;

   if (argc != 2)
      Usage(argv[0]);
   thread_count = strtol(argv[1], NULL, 10);

   thread_handles = malloc (thread_count*sizeof(pthread_t));
   pthread_mutex_init(&barrier_mutex, NULL);
   pthread_cond_init(&ok_to_proceed, NULL);

   GET_TIME(start);
   for (thread = 0; thread < thread_count; thread++)
      pthread_create(&thread_handles[thread], NULL,
          Thread_work, (void*) thread);

   for (thread = 0; thread < thread_count; thread++) {
      pthread_join(thread_handles[thread], NULL);
   }
   GET_TIME(finish);
   printf("Elapsed time = %e seconds\n", finish - start);

   pthread_mutex_destroy(&barrier_mutex);
   pthread_cond_destroy(&ok_to_proceed);
   free(thread_handles);
   return 0;
} 

void Usage(char* prog_name) {

   fprintf(stderr, "usage: %s <number of threads>\n", prog_name);
   exit(0);
} 

void *Thread_work(void* rank) {

   long my_rank = (long) rank; 

   int i;

   for (i = 0; i < BARRIER_COUNT; i++) {
      pthread_mutex_lock(&barrier_mutex);
      barrier_thread_count++;
      if (barrier_thread_count == thread_count) {
         barrier_thread_count = 0;
         fflush(stdout);
         pthread_cond_broadcast(&ok_to_proceed);
      } else {
         // Esperar desbloquea el mutex y pone el hilo a dormir.
         // Ponga esperar en el ciclo while en caso de que algún otro
         // evento despierta hilo
         while (pthread_cond_wait(&ok_to_proceed, &barrier_mutex) != 0);
         // Mutex se vuelve a bloquear en este punto.
         fflush(stdout);
      }
      pthread_mutex_unlock(&barrier_mutex);

      if (my_rank == 0) {
         fflush(stdout);
      }

   }

   return NULL;
}
