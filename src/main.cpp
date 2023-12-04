#include <iostream>
#include <vector>
#include <complex>
#include <omp.h>
#include <unistd.h>
#include "writer.hpp"

using namespace std;
using std::vector;
using std::complex;


int main(int argc, char * argv[]) {

	// Get the time
	double start = omp_get_wtime();
	
	// Define top left coordinate and bottom right coordinate
	// Default value are respectively (-2, -2) and (2, 2)
	vector<double> tl(2, -2.);
	vector<double> br(2, 2.);
	vector<double> pFractal(1000*1000, 0);

	// Define the number of iterations
	int iterations = 100;

	int option, nthreads;

	// Indicate we don't want that getopt print if the option is not known, because we want to have negative numbers as parameter
	// and negative numbers are recognized as unknow option...
	opterr = 0;
	while ((option = getopt(argc, argv, "i:n:c:h")) != -1) {
		switch (option) {
			case 'i':
				iterations = atoi(optarg);
				if (iterations <= 0) {
					cerr << "Error ! number of iterations must be greater than 0" << endl;
					cout << "Usage: " << argv[0] << " -i [iterations] -n [number of threads] -c [tl_x tl_y br_x br_y]" << endl;
					return -1;
				}
				break;
			case 'n':
				nthreads = atoi(optarg);
				if (nthreads <= 0) {
					cerr << "Error ! Number of threads must be positive" << endl;
					cout << "Usage: " << argv[0] << " -i [iterations] -n [number of threads] -c [tl_x tl_y br_x br_y]" << endl;
					return -1;
				}
				omp_set_num_threads(nthreads);
				break;
			case 'c':
				if (argc - optind < 3) {
					cerr << "Error ! You must give tl_x tl_y br_x br_y and there is not enought arguments" << endl;
					cout << "Usage: " << argv[0] << " -i [iterations] -n [number of threads] -c [tl_x tl_y br_x br_y]" << endl;
					return -1;
				}
				tl[0] = stod(argv[optind - 1]);
				tl[1] = stod(argv[optind]);
				br[0] = stod(argv[optind + 1]);
				br[1] = stod(argv[optind + 2]);
				if (tl[0] >= br[0] || tl[1] >= br[1]) {
					cerr << "Error ! bad coordinate values ! Coordinate of top left (tl) must be less than bottom right (br) coordinates"<< endl;
					cout << "Usage: " << argv[0] << " -i [iterations] -n [number of threads] -c [tl_x tl_y br_x br_y]" << endl;
					return -1;
				}
				break;
			case 'h':
				cout << "Usage: " << argv[0] << " -i [iterations] -n [number of threads] -c [tl_x tl_y br_x br_y]" << endl;
				return -1;
		}
	}

	// Define scale
	double x_scale = (br[0] - tl[0]) / 1000.;
	double y_scale = (br[1] - tl[1]) / 1000.;

	// Calculate our fractal. Collapse is used to merge the two for loop.
	#pragma omp parallel
	{
		// Get number of threads
		nthreads = omp_get_num_threads();

		// Merge two for loop into a big for loop and divide work between all active threads
		#pragma omp for collapse(2)
		for (int y = 0; y < 1000; y++) {
			for (int x = 0; x < 1000; x++) {
				complex<double> c(x * x_scale + tl[0], y * y_scale + tl[1]);
				complex<double> z(0, 0);
				int n = 0;
				while (abs(z) < 2. && n < iterations) {
					z = (z * z) + c;
					n++;
				}
				pFractal[y * 1000 + x] = (double) n / (double) iterations;
			}
		}
	}


	// Usefull to see the result obtained
	write_to_bmp(1000, pFractal, iterations, 0, 1);

	// Get the time
	double end = omp_get_wtime();

	// Print execution time
	cout << "Execution time: " << end - start << endl;

	// Print number of threads
	cout << "Number of threads: " << nthreads << endl;

	// Print number of iterations
	cout << "Number of iterations: " << iterations << endl;

	return 0;
}
