#include <iostream>
//#include <execution>
#include <algorithm>
#include <unistd.h>
#include <vector>

using namespace std;
using std::vector;

// Inline is usefull to copy the function because if we have a foreach and a lambda function that call this function, this function is on stack, so to have the function defined on the device, the inline indicate that the function must be copied on the device...
int inline i2x(int index, int size) {
	return index / size;
}

int inline i2y(int index, int size) {
	return index % size;
}


int main(int argc, char * argv[]) {

	int iter = 100;
	int size = 128;
	int option;
	while((option = getopt(argc, argv, "s:t:")) != -1) {
		switch (option) {
			case 's':
				size = atoi(optarg);
				if (size == 0) {
					cerr << "Error" << endl;
				}
				break;
			case 't':
				iter = atoi(optarg);
				if (iter == 0) {
					cerr << "Error" << endl;
				}
				break;
			case '?':
				cout << "Usage: " << endl;
				break;
		}
	}

	// If we don't put inline, the function is defined on stack, so we can't use it on gpus...
	

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

	print_grid(create_grid(8), 8);


}

