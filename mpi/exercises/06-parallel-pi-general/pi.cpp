// SPDX-FileCopyrightText: 2019 CSC - IT Center for Science Ltd. <www.csc.fi>
//
// SPDX-License-Identifier: MIT

#include <cstdio>
#include <cmath>
#include <mpi.h>

constexpr int n = 840;
constexpr int TAG = 0;

int main(int argc, char** argv)
{
  MPI_Init(&argc, &argv);
  int size, rank;
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  printf("Computing approximation to pi with N=%d\n", n);
  int istart, istop;
  /*if (rank == 0){
    istart = 1;
    istop = n / 2;
  } else {
    istart = n / 2 + 1;
    istop = n;
  }*/
  istart = n / size * rank + 1;
  istop = n / size * (rank + 1);

  double pi = 0.0;
  for (int i=istart; i <= istop; i++) {
    double x = (i - 0.5) / n;
    pi += 1.0 / (1.0 + x*x);
  }

  pi *= 4.0 / n;

  if (rank == 0){
    double pi_total = pi;
    double pi_recv = 0;
    for (int i = 1; i < size; i++){
    	MPI_Recv(&pi_recv, 1, MPI_DOUBLE, i, TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    	pi_total += pi_recv;
    }
    printf("Approximate pi=%18.16f (exact pi=%10.8f)\n", pi_total, M_PI);
  } else {
    MPI_Send(&pi, 1, MPI_DOUBLE, 0, TAG, MPI_COMM_WORLD); 
  }

  MPI_Finalize();
}
