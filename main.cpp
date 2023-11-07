#include <iostream>
#include "Grid.h"
#include "write.h"
#include <mpi.h>

using namespace std;

int main(int argc, char * argv[]) {
	if (argc <  2) {
	    cerr << "Error ! Usage: ./tp3 grid_dimension time" << endl;
	}
	Grid grid(atoi(argv[1]), atoi(argv[1]));
	// grid.next_step();
	// grid.swap(newgrid);
	// int n = grid.get_indice(atoi(argv[1]) - 1, atoi(argv[1]) - 1);
	// int * indices = grid.get_indices(n);
	// cout << "Indice " << n << " Indices 	
	// Initialize MPI
	MPI_Init(NULL, NULL);

	// Get rank of process and number of process
	int rank = 0;
	int world_size = 0;
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &world_size);

	if (grid.rows * grid.columns % world_size != 0) {
		cerr << "Error ! The grid is not divisible by the number of porcess ! " << endl;
		exit(EXIT_FAILURE);
	}

	int nb_elements_to_compute = grid.rows * grid.columns / world_size;
	grid.print_line_grid();
	vector<double>  recvbuf(nb_elements_to_compute, 0.);

	int recvcount = 0;

	cout << grid.calculate_element(rank) << endl;

	MPI_Scatter(grid.grid_line.data(), nb_elements_to_compute, MPI_DOUBLE, recvbuf.data(), nb_elements_to_compute, MPI_DOUBLE, 0, MPI_COMM_WORLD);

	vector<double> newgridline(nb_elements_to_compute, 0.);
	for (int i = 0; i < nb_elements_to_compute; i++) {
		newgridline[i] = grid.calculate_element(i + rank);
	}





	

	// Destroy MPI environment
	MPI_Finalize();
}

    // grid.state_grid_after_time(atoi(argv[2]));
    // grid.print_grid();
    // write_to_bmp(grid, atoi(argv[2]));
