#include <iostream>
#include <omp.h>

using namespace std;

int main(int argc, char * argv[]) {

	// Test if parameters are correct
	if (argc < 2 || argc > 3) {
		cerr << "Error ! give the number of circumscribed rectangle !" << endl;
		cout << "Usage: " << argv[0] << " number (must be non negative...)" << endl;
		return -1;
	}
	int n = atoi(argv[1]);
	if (n <= 0) {
		cerr << "Error ! bad number value !" <<endl;
		cout << "Usage: " << argv[0] << " number (must be non negative...)" << endl;
		return -1;
	}

	int nthread;
	if (argc == 3) {
		nthread = atoi(argv[2]);
		if (nthread <= 0) {
			cerr << "Error ! bad number value !" <<endl;
			cout << "Usage: " << argv[0] << " number (must be non negative...)" << endl;
			return -1;
		}
		omp_set_num_threads(nthread);

	}

	#pragma omp parallel
	{
		nthread = omp_get_num_threads();
	}
	cout << "Executing program with " << nthread << " threads" << endl;

	double start = omp_get_wtime();

	// Define here our function f(x) = 4/(1 + x^2)
	auto f = [](double x) -> double {
		return 4./(1. + x * x);
	};

	// Define pi number to store result, and delta of the Riemann sum
	double pi = 0.;
	double delta = 1./n;

	// Calculate the approximation of Pi number
	// We make the sum of the area of each little circumscribed rectangle...
	// The area of a circumscribed rectange is given by delta * f(delta * number of current circumscribed rectangle)
	#pragma omp parallel for
	for (int i = 1; i < n + 1; i++) {
		pi += delta * f(i*delta);
	}

	// Print output
	cout << "Pi approximation: " << pi << endl;
	
	double end = omp_get_wtime();

	cout << "Execution time: " << end - start << endl;

	return 0;



}
