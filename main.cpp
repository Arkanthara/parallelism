#include <iostream>
#include "Grid.h"
#include <vector>
#include <mpi.h>

using namespace std;
using std::vector;

int main(int argc, char * argv[]) {
	// Initialize MPI
	MPI_Init(&argc, &argv);
	if (argc <  2) {
	    cerr << "Error ! Usage: ./tp3 grid_dimension time" << endl;
	}

	// Get rank of process and number of process
	int rank = 0;
	int world_size = 0;
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &world_size);

	int size = atoi(argv[1]);
	vector<double> grid;
	if (rank == 0) {
		grid = create_grid(size);
		if (grid.size() % world_size != 0) {
			cerr << "Error ! The grid is not divisible by the number of porcess ! " << endl;
			exit(EXIT_FAILURE);
		}
		print_grid(grid, size);
	}

	int nb_elements_to_compute = size*size / world_size;
	vector<double>  recvbuf(nb_elements_to_compute, 0.);

	MPI_Scatter(grid.data(), nb_elements_to_compute, MPI_DOUBLE, recvbuf.data(), nb_elements_to_compute, MPI_DOUBLE, 0, MPI_COMM_WORLD);

	vector<double> newgridline(nb_elements_to_compute, 0.);
	for (int i = 0; i < nb_elements_to_compute; i++) {
//		newgridline[i] = compute_element(i + rank*nb_elements_to_compute, grid, size);
		cout << recvbuf[i] << " " ;
	}
	cout << endl << endl;

	MPI_Gather(newgridline.data(), size, MPI_DOUBLE, grid.data(), grid.size(), MPI_DOUBLE, 0, MPI_COMM_WORLD);
	if (rank == 0) {
		print_grid(grid, size);
	}	

	// Destroy MPI environment
	MPI_Finalize();
}

    // grid.state_grid_after_time(atoi(argv[2]));
    // grid.print_grid();
    // write_to_bmp(grid, atoi(argv[2]));
