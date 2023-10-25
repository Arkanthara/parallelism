#include <mpi.h>
#include <string.h>
#include <iostream>

using namespace std;

int exercise_1(void) {

        MPI_Init(NULL, NULL);

        MPI_Status status;

        int world_rank = 0;
        MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

        int world_size = 0;
        MPI_Comm_size(MPI_COMM_WORLD, &world_size);

        char * text = "Hello world !";
        int size = strlen(text);

        if (world_rank == 0) {
                for (int i = 1; i < world_size; i++) {
                        MPI_Send(text, size, MPI_CHAR, i, 0, MPI_COMM_WORLD);
                }
        }
        else {
                char buffer[size];
                MPI_Recv(buffer, size, MPI_CHAR, 0, 0, MPI_COMM_WORLD, &status);
                cout << "Message received by processor " << world_rank << " from processor 0: " << buffer << endl;
        }

        MPI_Finalize();

        return 0;
}

int exercise_2(void) {

        MPI_Init(NULL, NULL);

        MPI_Status status;

        int world_rank = 0;
        MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

        int world_size = 0;
        MPI_Comm_size(MPI_COMM_WORLD, &world_size);

        // Text to send
        char * text = "Hello World !";
        int size = strlen(text);

        // Buffer for receive message
        char buffer[size];

        MPI_Send(text, size, MPI_CHAR, (world_rank + 1) % world_size, 0, MPI_COMM_WORLD);
        MPI_Recv(buffer, size, MPI_CHAR, (world_rank + world_size - 1) % world_size, 0, MPI_COMM_WORLD, &status);
        cout << "Processor " << world_rank <<  " receive from processor " << (world_rank + world_size - 1) % world_size << " the message: " << buffer << endl;

        MPI_Finalize();

        return 0;
}

int exercise_3(void) {

	MPI_Status status;

	MPI_Init(NULL, NULL);

	int world_rank = 0;

	MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

	int world_size = 0;

	MPI_Comm_size(MPI_COMM_WORLD, &world_size);

	char * text = "Hello world !";
	int size = strlen(text);

	char buffer[size];
        
	int mask = 1;
        
	while (world_size > mask) {
		int process = world_rank ^ mask;
		if (process > world_rank) {
			MPI_Recv(buffer, size, MPI_CHAR, process, 0, MPI_COMM_WORLD, &status);
			cout << "Processor " << world_rank <<" received " << buffer << " from processor " << process << endl;
		}
		else {
			MPI_Send(text, size, MPI_CHAR, process, 0, MPI_COMM_WORLD);
		}
		mask = mask << 1;
	}

	MPI_Finalize();

	return 0;
}


