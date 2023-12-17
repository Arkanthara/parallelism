#include <iostream>
#include <execution>
#include <algorithm>
#include <unistd.h>
#include <vector>
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

	// Allow to print a grid.
	// Usefull to verify if the initialization of the grid is correct
	auto print_grid = [](vector<double> grid, int size) {
		int index = 0;
		for (int i = 0; i < size; i ++) {
			for (int j = 0; j < size; j ++) {
				cout << grid[index] << " ";
				index ++;
			}
			cout << endl;
		}
	};

	// Initialize a grid to stock results of heast equation
	vector<double> grid_2 (size * size, 0.);

	// Initialize a grid which is the last state of the grid.
	vector<double> grid = create_grid(size);

	// Initialize values usefull to compute heast equation
	double hx = 1./size;
	double hy = 1./size;
	double C = 1.;
	double dt = 0.25*hx*hx/C;
	double diagx = -2.0 + hx*hx/(2*C*dt);
	double diagy = -2.0 + hy*hy/(2*C*dt);
	double weightx = C*dt/(hx*hx);
	double weighty = C*dt/(hy*hy);

	// Compute the heast equation the right number of times
	for(int iT = 0; iT < max_iter;iT++)
	{
		// Code parallel here.
		// Can use par_useq because there is no concurrency problems
		// since the values of grid aren't modified in computation
		for_each(std::execution::par_unseq, grid_2.begin(), grid_2.end(),
			[start = grid_2.data(), size, grid, diagx, diagy, weightx, weighty](double& item) {
				// Get and convert index of item of grid_2 into 2d index.
				int index = &item - start;
				int x = i2x(index, size);
				int y = i2y(index, size);
				// Verify that we aren't in border
				if (x == 0 || y == 0 || x == size - 1 || y == size - 1)
					item = grid[index];
				// Compute heast equation
				else
					item = weightx*(grid[xy2i(x-1, y, size)]
					+ grid[xy2i(x+1, y, size)]
					+ grid[xy2i(x, y, size)]*diagx)
					+ weighty*(grid[xy2i(x, y-1, size)]
					+ grid[xy2i(x, y+1, size)]
					+ grid[xy2i(x, y, size)]*diagy);
			});
		// Swap the two grid to have in grid the last state of the grid
		swap(grid_2, grid);
	}
	// Write the results into a bmp file
	write_to_bmp(size, grid, max_iter, 0, 1);
}

