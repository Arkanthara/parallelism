#include "exercises.h"
#include <string.h>
#include <iostream>

using namespace std;

int main(int argc, char * argv[]) {

	if (argc != 2) {
		cerr << "Error !" << endl << "Usage of the program: <command to execute the program> <number of the exercise>" << endl << "Example: runmpi tp2 2" << endl;
		return -1;
	}

	int exercise_number = atoi(argv[1]);

	switch (exercise_number) {
		case 1:
			exercise_1();
			break;
		case 2:
			exercise_2();
			break;
		case 3:
			exercise_3();
			break;
		default:
                        cerr << "Error !" << endl << "Usage of the program: <command to execute the program> <number of the exercise>" << endl << "Example: runmpi tp2 2" << endl;
			return -1;

	}

	return 0;

}