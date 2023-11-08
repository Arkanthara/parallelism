#include <iostream>
#include "Grid.h"
#include <vector>
#include <mpi.h>
#include "writer.h"

// Here I include algorithm to reverse some vectors
#include <algorithm>

using namespace std;

using std::vector;

int main(int argc, char * argv[]) {

	// Initialize MPI Environment
	MPI_Init(&argc, &argv);

	// Using for non-blocking communication between processors
	MPI_Request top_request , bottom_request ;

	// We verify that the user give us the size of the grid and the time to calculate state of the grid
	if (argc !=  3) {
		cerr << "Error ! Usage: ./tp3 grid_dimension time" << endl;
		return -1;
	}

	// Get rank of processor
	int rank = 0;
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	// Get total number of processors
	int world_size = 0;
	MPI_Comm_size(MPI_COMM_WORLD, &world_size);

	// Get the size given by the user. If atoi has an error, it return 0... We verify that the size is correct 
	int size = atoi(argv[1]);
	if (size <= 0) {
		cerr << "Bad size ! Usage: ./tp3 size time" << endl;
		return -1;
	}

	int time = atoi(argv[2]);
	if (time <= 0) {
		cerr << "Bad size ! Usage: ./tp3 size time" << endl;
		return -1;
	}

	// Why must we have a grid known by all the processes ???
	// Here I define the grid vector used to create a grid, and at the end to claim datas from all the processors...
	vector <double> grid (size*size);

	// If we are in the processor of rank 0, we make something... In fact the processor 0 will create a grid and split the grid to give a part of the grid to each processors
	if (rank == 0) {
		// If the size of the grid is not compatible with the number of processors used, we print an error and quit the function
		if (size % world_size != 0) {
			cerr << "Error ! The grid is not divisible by the number of porcess ! " << endl;
			return -1;
		}

		// Here I create my grid and I put it in a 1D vector !
		grid = create_grid(size);

		// Then I print the grid like a 2D vector
		// print_grid(grid, size);
	}

	// This variable indicates us how many columns we'd have per processor
	int nb_columns = size / world_size;

	// We prepare a buffer to receive datas send by processor 0
	vector<double>  recvbuf(size*nb_columns, 0.);

	for (int i = 0; i < time; i++) {

	// Can I put the scatter method just in processor 0 ?
	// We send chunks of an array to differents processors
	MPI_Scatter(grid.data(), size*nb_columns, MPI_DOUBLE, recvbuf.data(), size*nb_columns, MPI_DOUBLE, 0, MPI_COMM_WORLD);

	// We define a new vector where we will store our intermediate results
	vector<double> newgridline(size*nb_columns, 1.);

	// This two variables are used to add last or first column of processor of inferior or superior rank... Usefull to compute our function...
	vector<double> tmp(size, 0.);
	vector<double> tmp_2(size, 0.);

	// If rank is more than 0, we send our first column to the processor of our rank minus 1. So he could add this datas to the end of the vector used to compute blabla
	// And we receive the last column of the datas of the  processor of our rank minus 1, so we could add this data to the begining of our vector, but we don't make it now because we 
	// perhaps need to send the last column of our data to another processor...
	if (rank > 0) {
		MPI_Isend(first_column(recvbuf, size).data(), size, MPI_DOUBLE, rank - 1, 0, MPI_COMM_WORLD, &top_request);
		MPI_Irecv(tmp.data(), size, MPI_DOUBLE, rank - 1, 0, MPI_COMM_WORLD, &top_request);
	}

	// It's exactly the same thing, but the difference is rank + 1 and rank < world_size... It's symetric...
	if (rank < world_size - 1) {
		MPI_Isend(last_column(recvbuf, size).data(), size, MPI_DOUBLE, rank + 1, 0, MPI_COMM_WORLD, &bottom_request);
		MPI_Irecv(tmp_2.data(), size, MPI_DOUBLE, rank + 1, 0, MPI_COMM_WORLD, &bottom_request);
	}

	// This variable is usefull to determine if we need to make a shift because a column, usefull to compute, but not used to compute each values added, can be added to the
	// begining of the vector to compute...
	int index = 0;

	// Here, we wait for completion of non-blocking communication... And then, we add the data received to the begining of our vector
	if (rank > 0) {
		MPI_Wait (&top_request , MPI_STATUS_IGNORE );
		tmp.insert(tmp.end(), recvbuf.begin(), recvbuf.end());
		recvbuf = tmp;
		index = size;
	}


	// Here, we wait for completion of non-blocking communication... And then, we add the data received to the end of our vector
	if (rank < world_size - 1) {
		MPI_Wait (&bottom_request , MPI_STATUS_IGNORE );
		recvbuf.insert(recvbuf.end(), tmp_2.begin(), tmp_2.end());
	}

	// Here, we compute the result, with a shift if needed
	// If we are in the last processor, we don't have to compute the last column, so we skip it...
	if (rank == world_size - 1) {
		for (int i = 0; i < size*nb_columns - size; i++) {
			newgridline[i] = compute_element(i + index, recvbuf, size);
		}
		for (int i = 0; i < size; i++) {
			newgridline[(size - 1)*nb_columns] = recvbuf[(size - 1) * nb_columns];
		}
	}
	else {
		for (int i = 0; i < size*nb_columns; i++) {
			newgridline[i] = compute_element(i + index, recvbuf, size);
		}
	}

	// Here, we keep all datas of processors and the processor 0 put them into the result vector
	MPI_Gather(newgridline.data(), nb_columns * size, MPI_DOUBLE, grid.data(), nb_columns * size, MPI_DOUBLE, 0, MPI_COMM_WORLD);
	
	}

	// As it's the processor 0 which claimed datas, we just print the result if we are in processor 0...
	if (rank == 0) {
//		print_grid(grid, size);
		write_to_bmp(size, grid, time, *min_element(grid.begin(), grid.end()), *max_element(grid.begin(), grid.end()));

	}	

	// Destroy MPI environment
	MPI_Finalize();
}
