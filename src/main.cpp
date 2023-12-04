#include <iostream>
#include <vector>
#include <complex>
#include <omp.h>
#include "writer.hpp"

using namespace std;
using std::vector;
using std::complex;


int main(int argc, char * argv[]) {

	// Define top left coordinate and bottom right coordinate
	// Default value are respectively (0, 0) and (1000, 1000)
	vector<int> tl(2, -2);
	vector<int> br(2, 2);
	vector<double> pFractal(1000*1000, 0);


	int iterations = 1000;
	int nthreads;

	// Get the time
	double start = omp_get_wtime();

	// If there is no input of the user, we init top left to (0, 0)
	if (argc == 5) {
		tl[0] = atoi(argv[1]);
		tl[1] = atoi(argv[2]);
		br[0] = atoi(argv[3]);
		br[1] = atoi(argv[4]);
		if (tl[0] >= br[0] || tl[1] >= br[1]) {
			cerr << "Error ! bad coordinate values ! Coordinate of top left (tl) must be less than bottom right (br) coordinate"<< endl;
			cout << "Usage: " << argv[0] << " [optionnal: number of threads] [optionnal: tl_x tl_y br_x br_y]" << endl;
			return -1;
		}
	}

	else if (argc == 2) {
		nthreads = atoi(argv[1]);
		if (nthreads == 0) {
			cerr << "Error ! You must give a number of threads greater than 0 !" << endl;
			cout << "Usage: " << argv[0] << " [optionnal: number of threads] [optionnal: tl_x tl_y br_x br_y]" << endl;
			return -1;
		}
		omp_set_num_threads(nthreads);
	}
	
	else if (argc == 3) {
		nthreads = atoi(argv[1]);
		if (nthreads == 0) {
			cerr << "Error ! You must give a number of threads greater than 0 !" << endl;
			cout << "Usage: " << argv[0] << " [optionnal: number of threads] [optionnal: tl_x tl_y br_x br_y]" << endl;
			return -1;
		}
		omp_set_num_threads(nthreads);
		iterations = atoi(argv[2]);
		if (iterations <= 0)  {
			cerr << "Error ! Number of iterations must more than 0 !" << endl;
			return -1;
		}
	}

	else if (argc == 6) {
		nthreads = atoi(argv[1]);
		if (nthreads == 0) {
			cerr << "Error ! You must give a number of threads greater than 0 !" << endl;
			cout << "Usage: " << argv[0] << " [optionnal: number of threads] [optionnal: tl_x tl_y br_x br_y]" << endl;
			return -1;
		}
		omp_set_num_threads(nthreads);
		tl[0] = atoi(argv[2]);
		tl[1] = atoi(argv[3]);
		br[0] = atoi(argv[4]);
		br[1] = atoi(argv[5]);
		if (tl[0] >= br[0] || tl[1] >= br[1]) {
			cerr << "Error ! bad coordinate values ! Coordinate of top left (tl) must be less than bottom right (br) coordinate"<< endl;
			cout << "Usage: " << argv[0] << " [optionnal: number of threads] [optionnal: tl_x tl_y br_x br_y]" << endl;
			return -1;
		}
	}
	

	// Define scale
	double x_scale = (br[0] - tl[0]) / 1000.;
	double y_scale = (br[1] - tl[1]) / 1000.;

	// Calculate our fractal. Collapse is used to merge the two for loop.
	#pragma omp parallel
	{
		nthreads = omp_get_num_threads();

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

	return 0;
}
