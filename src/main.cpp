#include <iostream>
#include <omp.h>

using namespace std;

int main(int argc, char * argv[]) {

	// Test if the user give the right number of parameters
	if (argc > 3) {
		cerr << "Error ! give the number of circumscribed rectangles !" << endl;
		cout << "Usage: " << argv[0] << " number of circumscribed rectanges [optionnal: number of threads]\nWarning ! All the numbers must be non negative !" << endl;
		return -1;
	}

	int n = 100000000;
	// Get the number of circumscribed rectangles
	if (argc == 2) {
		n = atoi(argv[1]);
		if (n <= 0) {
			cerr << "Error ! bad number value !" <<endl;
			cout << "Usage: " << argv[0] << " [optionnal: number of circumscribed rectanges] [optionnal: number of threads]\nWarning ! All the numbers must be non negative !" << endl;
			return -1;
		}
	}

	// Set the number of threads if the argument is given
	int nthread = 8;
	if (argc == 3) {
		nthread = atoi(argv[2]);
		if (nthread <= 0) {
			cerr << "Error ! bad number value !" <<endl;
			cout << "Usage: " << argv[0] << " number of circumscribed rectanges [optionnal: number of threads]\nWarning ! All the numbers must be non negative !" << endl;
			return -1;
		}
		omp_set_num_threads(nthread);

	}

	// Get the time
	double start = omp_get_wtime();

	// Define here our function f(x) = 4/(1 + x^2)
	// We have the result of the function 1/(1 + x^2) which give Pi/4
	// So I made 4/(1 + x^2) to have Pi
	auto f = [](double x) -> double {
		return 4./(1. + x * x);
	};

	// Define pi number to store result, and delta of the Riemann sum
	double pi = 0.;
	double delta = 1./n;

	// Calculate the approximation of Pi number
	// We make the sum of the area of each little circumscribed rectangle...
	// The area of a circumscribed rectange is given by delta * f(delta * number of current circumscribed rectangle)
	#pragma omp parallel
	{
		nthread = omp_get_num_threads();
		#pragma omp for reduction(+ :pi)
		for (int i = 1; i < n + 1; i++) {
			pi += delta * f(i*delta);
		}
	}
	/* TO FIX
	// Get the number of threads
	// We must be in parallel region to get the number of threads
	// or we just get one thread because it count the number of thread in execution
	nthread = omp_get_num_threads();
	*/

	cout << "Number of circumscribed rectangles: " << n << endl;
	// Print number of thread used
	cout << "Number of threads used: " << nthread << endl;

	// Print result of approximation
	cout << "Pi approximation: " << pi << endl;
	
	// Get the time
	double end = omp_get_wtime();

	// Print execution time
	cout << "Execution time: " << end - start << endl;

	return 0;



}
