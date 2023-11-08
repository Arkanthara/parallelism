#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include "writer.h"
#include <mpi.h>

using namespace std;
using std::vector;

const int max_iter =1e5;

vector<double> convert_to_1D(vector<vector<double>> grid, int size) {
	vector<double> grid_line(size * size, 0.);
	for (int i = 0; i < size; i ++) {
		for (int j = 0; j < size; j ++) {
			grid_line[i*size + j] = grid[i][j];
		}
	}
	return grid_line;
}

vector<vector<double>> convert_to_2D(vector<double> grid_line, vector<vector<double>> grid, int size) {
	int n = 0;
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			grid[i][j] = grid_line[n];
			n++;
		}
	}
	return grid;
}

vector<vector<double>> put_into_2D(vector<vector<double>> grid, vector<double> grid_line, int nb_columns, int rank, int size) {
	int n = 0;
	for (int i = rank*nb_columns; i < rank*nb_columns +  nb_columns; i++) {
		for (int j = 0; j < size; j++) {
			grid[i][j] = grid_line[n];
			n++;
		}
	}
	return grid;
}

void print_line(vector<double> grid_line, int size) {
	for (int i = 0; i < size ; i++) {
		cout << grid_line[i] << " ";
	}
	cout << endl;
}

void print_grid(vector<vector<double>> grid, int size) {
	for (int i = 0; i < size; i ++) {
		for (int j = 0; j < size; j ++)
			cout << grid[i][j] << " ";
		cout << endl;
	}
}


vector<vector<double>> create_grid(int size) {
	vector<vector<double>> grid;
	grid.resize(size);
	for (int i = 0; i < size; i ++) {
		grid[i].resize(size);
		for (int j = 0; j < size; j ++) {
			if (i == 0 || j == 0 || i == size - 1 || j == size - 1)
				grid[i][j] = 1.;
			else grid[i][j] = 0.;
		}
	}
	return grid;
}

int main(int argc, char* argv[])
{
	MPI_Init(NULL, NULL);
	// We verify that the user give us the size of the grid and the time to calculate state of the grid
        if (argc !=  3) {
                cerr << "Error ! Usage: ./tp3 grid_dimension time" << endl;
                return -1;
        }


	MPI_Request top_request, bottom_request;

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
	
	int rank = 0;
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	int world_size = 0;
	MPI_Comm_size(MPI_COMM_WORLD, &world_size);

	std::vector<std::vector<double>> U;
	std::vector<std::vector<double>> grid;
	
	U.resize(size);
	grid.resize(size);
	
	for(int i =0; i<size;++i)
	{
	    U[i].resize(size);
	    grid[i].resize(size);
	}
	
	//Assign
	for(int i =1; i< size-1; i++)
	    for(int j =1; j< size -1; j++)
	        {
	            U[i][j] = 0;
	            grid[i][j] = 0;
	        }
	// Top Bottom
	for(int i =0; i< size; i++)
	    {
	        U[i][0] = 1;
	        grid[i][0] = 1;
	        U[i][size-1] = 1;
	        grid[i][size-1] = 1;
	    }
	
	//Left Right
	 for(int i =0; i< size; i++)
	    {
	        U[0][i] = 1;
	        grid[0][i] = 1;
	        U[size-1][i] = 1;
	        grid[size -1][i] = 1;
	
	    }

	 auto grid_line = convert_to_1D(grid, size);

	// If the size of the grid is not compatible with the number of processors used, we print an error and quit the function
	if (size % world_size != 0) {
		cerr << "Error ! The grid is not divisible by the number of porcess ! " << endl;
		return -1;
	}
	
	int nb_columns = size / world_size;
	
	vector<double> recvbuf(nb_columns * size, 0.);
	for (int i = 0; i < time; i++) {
		MPI_Scatter(grid_line.data(), nb_columns * size, MPI_DOUBLE, recvbuf.data(), nb_columns * size, MPI_DOUBLE, 0, MPI_COMM_WORLD);
	
	//	grid = put_into_2D(grid, {2., 3., 4., 5., 6., 7., 8., 9., 4., 3., 2., 5., 3., 6., 3., 3.}, 2, 2, size);
	//	grid = put_into_2D(grid, {2., 3., 4., 5., 6., 7., 8., 9.}, 1, 2, size);
		grid = put_into_2D(grid, recvbuf, nb_columns, rank, size);
	
		vector<double> top_buffer(size, 0.);
		vector<double> bottom_buffer(size, 0.);
	
	//	if (rank > 0) {
	//                MPI_Isend(grid[0].data(), size, MPI_DOUBLE, rank - 1, 0, MPI_COMM_WORLD, &top_request);
	//                MPI_Irecv(grid[1].data(), size, MPI_DOUBLE, rank - 1, 0, MPI_COMM_WORLD, &top_request);
	//        }
	//
	//        // It's exactly the same thing, but the difference is rank + 1 and rank < world_size... It's symetric...
	//        if (rank < world_size - 1) {
	//                MPI_Isend(grid[0].data(), size, MPI_DOUBLE, rank + 1, 0, MPI_COMM_WORLD, &bottom_request);
	//                MPI_Irecv(grid[1].data(), size, MPI_DOUBLE, rank + 1, 0, MPI_COMM_WORLD, &bottom_request);
	//        }
	
		if (rank > 0) {
			MPI_Isend(grid[rank * nb_columns].data(), size, MPI_DOUBLE, rank - 1, 0, MPI_COMM_WORLD, &top_request);
			MPI_Irecv(grid[rank * nb_columns - 1].data(), size, MPI_DOUBLE, rank - 1, 0, MPI_COMM_WORLD, &top_request);
		}
		if (rank < world_size - 1) {
			MPI_Isend(grid[(rank + 1) * nb_columns - 1].data(), size, MPI_DOUBLE, rank + 1, 0, MPI_COMM_WORLD, &bottom_request);
			MPI_Irecv(grid[(rank + 1) * nb_columns].data(), size, MPI_DOUBLE, rank + 1, 0, MPI_COMM_WORLD, &bottom_request);
		}
	
		if (rank > 0) {
			MPI_Wait(&top_request, MPI_STATUS_IGNORE);
		}
		if (rank < world_size - 1) {
			MPI_Wait(&bottom_request, MPI_STATUS_IGNORE);
		}
	
		auto hx = 1./size;
		auto hy = 1./size;
		
		auto C = 1.;
		
		auto dt = 0.25*hx*hx/C;
		
		auto diagx = -2.0 + hx*hx/(2*C*dt);
		auto diagy = -2.0 + hy*hy/(2*C*dt);
		auto weightx = C*dt/(hx*hx);
		auto weighty = C*dt/(hy*hy);
		
		//FILL
		int n = 0;
	
		for (int i=rank*nb_columns;i<rank*nb_columns + nb_columns;i++) {
			for (int j=0;j<size;j++) {
				if (i == 0 || j == 0 || j == size - 1 || i == size - 1) recvbuf[n] = grid[i][j];
				else recvbuf[n] = weightx*(grid[i-1][j] + grid[i+1][j] + grid[i][j]*diagx) + weighty*(grid[i][j-1] + grid[i][j+1] + grid[i][j]*diagy);
				n++;
			}
		}
	//	if (rank == 0) {
	//		for (int i=0;i<nb_columns;i++) {
	//			for (int j=0;j<size;j++) {
	//				if (i == 0 || j == 0 || j == size - 1 || i == size - 1) recvbuf[n] = grid[i][j];
	//				else recvbuf[n] = weightx*(grid[i-1][j] + grid[i+1][j] + grid[i][j]*diagx) + weighty*(grid[i][j-1] + grid[i][j+1] + grid[i][j]*diagy);
	//				n++;
	//			}
	//		}
	//	}
	//	else if (rank == world_size - 1) {
	//		for (int i=rank*nb_columns;i<rank*nb_columns + nb_columns;i++) {
	//			for (int j=0;j<size;j++) {
	//				if (i == 0 || j == 0 || j == size - 1 || i == size - 1) recvbuf[n] = grid[i][j];
	//				else recvbuf[n] = weightx*(grid[i-1][j] + grid[i+1][j] + grid[i][j]*diagx) + weighty*(grid[i][j-1] + grid[i][j+1] + grid[i][j]*diagy);
	//				n++;
	//			}
	//		}
	//	}
	//	else {
	//		for (int i=rank*nb_columns;i<rank*nb_columns + nb_columns;i++) {
	//			for (int j=0;j<size;j++) {
	//				if (i == 0 || j == 0 || j == size - 1 || i == size - 1) recvbuf[n] = grid[i][j];
	//				else recvbuf[n] = weightx*(grid[i-1][j] + grid[i+1][j] + grid[i][j]*diagx) + weighty*(grid[i][j-1] + grid[i][j+1] + grid[i][j]*diagy);
	//				n++;
	//			}
	//		}
	//	
	//	}
	
		MPI_Gather(recvbuf.data(), nb_columns * size, MPI_DOUBLE, grid_line.data(), nb_columns * size, MPI_DOUBLE, 0, MPI_COMM_WORLD);
	}

	if (rank == 0) {
		grid = convert_to_2D(grid_line, grid, grid.size());
		write_to_bmp(size,grid,max_iter,0,1);
	}

	MPI_Finalize();
	
	
	return 0;

}

