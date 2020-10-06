#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {
  const int PING_PONG_limite = 15; // cantidad de rebotes

  MPI_Init(NULL, NULL);

  int world_rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
  int world_size;
  MPI_Comm_size(MPI_COMM_WORLD, &world_size);

  int rebotes = 0;
  int partner_rank = (world_rank + 1) % 2; //asignacion del rank
  while (rebotes < PING_PONG_limite) {
    if (world_rank == rebotes % 2) {
      rebotes++;
      MPI_Send(&rebotes, 1, MPI_INT, partner_rank, 0, MPI_COMM_WORLD);
      printf("%d Enviando y creciendo (rebotes) %d del proceso %d\n", world_rank, rebotes, partner_rank);
    } 
    else {
      MPI_Recv(&rebotes, 1, MPI_INT, partner_rank, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
      printf("%d Reciviendo (rebotes) %d del proceso %d\n", world_rank, rebotes, partner_rank);
    }
  }
  MPI_Finalize();
}