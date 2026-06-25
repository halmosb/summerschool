// SPDX-FileCopyrightText: 2010 CSC - IT Center for Science Ltd. <www.csc.fi>
//
// SPDX-License-Identifier: MIT

#include <iostream>
#include <mpi.h>

int main(int argc, char *argv[])
{
    int size, rank;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    
    int resultlen;
    char name[MPI_MAX_PROCESSOR_NAME];
    MPI_Get_processor_name(name, &resultlen);


    // TODO: say hello! in parallel
    std::cout << "I am rank: " << rank << " on node" << name << "!";
    std::cout << std::endl;
    if (rank == 0){
	    std::cout << MPI_MAX_PROCESSOR_NAME <<" - I am rank " << rank << " and the total number of ranks is " << size << std::endl;
    }
    else if(rank == size - 1){
    	std::cout << "I'm the last but not least" << std::endl;
    }
    else if(rank == 42){
    	std::cout << "I'm the Answer to the Ultimate Question of Life, the Universe, and Everything!" <<std::endl;
    }
    MPI_Finalize();
}
