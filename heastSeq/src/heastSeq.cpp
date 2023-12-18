#include <iostream>
#include <execution>
#include <algorithm>
#include <unistd.h>
#include <vector>
#include <chrono>
#include "writer.hpp"

using namespace std;
using std::vector;

// Inline is usefull to copy the function because if we have a foreach and a lambda function that call this function, this function is on stack, so to have the function defined on the device, the inline indicate that the function must be copied on the device...
int inline i2x(int index, int size) {
	return index % size;
}

int inline i2y(int index, int size) {
	return index / size;
}

int inline xy2i(int x, int y, int size) {
	return x * size + y;
}


int main(int argc, char * argv[]) {

	// Get the time
	auto start_time = std::chrono::high_resolution_clock::now();

	// Initialise default iteration and default size
	int max_iter = 100;
	int size = 128;

	// Get options of user
	int option;
	while((option = getopt(argc, argv, "s:i:")) != -1) {
		switch (option) {
			case 's':
				size = atoi(optarg);
				if (size == 0) {
					cerr << "Error: size must be a positive number !" << endl;
					cout << "Usage: ./"<< argv[0] << endl;
					cout << "	-i [number of iterations]" << endl;
					cout << "	-s [size of the squared grid]" << endl;
				}
				break;
			case 'i':
				max_iter = atoi(optarg);
				if (max_iter == 0) {
					cerr << "Error: number of iterations must be a positive number !" << endl;
					cout << "Usage: ./"<< argv[0] << endl;
					cout << "	-i [number of iterations]" << endl;
					cout << "	-s [size of the squared grid]" << endl;
				}
				break;
			case '?':
				cout << "Usage: ./"<< argv[0] << endl;
				cout << "	-i [number of iterations]" << endl;
				cout << "	-s [size of the squared grid]" << endl;
				break;
		}
	}


	// Create and initalize a new grid, like in the tp3
	auto create_grid = [](int size) {
		vector<double> grid;
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++) {
				if (i == 0 || j == 0 || i == size - 1 || j == size - 1)
					grid.push_back(1.);
				else grid.push_back(0.);
			}
		}
		return grid;
	};

	// Initialize a grid to stock results of heast equation
	vector<double> grid_2 (size * size, 0.);

	// Initialize a grid which is the last state of the grid.
	vector<double> grid = create_grid(size);

	// Initialize values usefull to compute heast equation
	auto hx = 1./size;
	auto hy = 1./size;
	auto C = 1.;
	auto dt = 0.25*hx*hx/C;
	auto diagx = -2.0 + hx*hx/(2*C*dt);
	auto diagy = -2.0 + hy*hy/(2*C*dt);
	auto weightx = C*dt/(hx*hx);
	auto weighty = C*dt/(hy*hy);

	// Compute the heast equation the right number of times
	for(int iT = 0; iT < max_iter;iT++)
	{
		// Code parallel here.
		// Can use par_useq because there is no concurrency problems
		// since the values of grid aren't modified in computation
		for_each(std::execution::par_unseq, grid_2.begin(), grid_2.end(),
			[start = grid_2.data(), size, grid = grid.data(), diagx, diagy, weightx, weighty](double &item) {
				// Get and convert index of item of grid_2 into 2d index.
				int index = (int) (&item - start);
				int x = i2x(index, size);
				int y = i2y(index, size);
				// Verify that we aren't in border
				if (x == 0 || y == 0 || x == size - 1 || y == size - 1)
					item = *(grid + index);
				// Compute heast equation
				else
					item = weightx*(*(grid + xy2i(x-1, y, size))
					+ *(grid + xy2i(x+1, y, size))
					+ *(grid + xy2i(x, y, size)) * diagx)
					+ weighty * (*(grid + xy2i(x, y-1, size))
					+ *(grid + xy2i(x, y+1, size))
					+ *(grid + xy2i(x, y, size))*diagy);
			});
		// Swap the two grid to have in grid the last state of the grid
		swap(grid_2, grid);
	}

	// Get the time
	auto end_time = std::chrono::high_resolution_clock::now();

	// Calculate execution time
	auto execution_time = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);

	// Write the results into a bmp file
	write_to_bmp(size, grid, max_iter, 0, 1);

	// Print execution time
	cout << "Execution time: " << execution_time.count()/1000. << endl;

	// Print number of iterations
	cout << "Iterations: " << max_iter << endl;

	// Print grid size
	cout << "Grid size: " << size << "x" << size << endl;

	return 0;
}

