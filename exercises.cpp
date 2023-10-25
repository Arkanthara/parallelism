#include <mpi.h>
#include <string.h>
#include <iostream>

using namespace std;

int exercise_1(void) {

        // Initialize MPI environment
        MPI_Init(NULL, NULL);

        MPI_Status status;

        // Get the rank of the processor and the total number of processors
        int world_rank = 0;
        MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

        int world_size = 0;
        MPI_Comm_size(MPI_COMM_WORLD, &world_size);

        // Initialize the message
        char * text = "Hello world !";
        int size = strlen(text);

        // Send message from processor 0 to other processors
        if (world_rank == 0) {
                for (int i = 1; i < world_size; i++) {
                        MPI_Send(text, size, MPI_CHAR, i, 0, MPI_COMM_WORLD);
                }
        }
        // Receive message by other processors
        else {
                char buffer[size];
                MPI_Recv(buffer, size, MPI_CHAR, 0, 0, MPI_COMM_WORLD, &status);
                cout << "Message received by processor " << world_rank << " from processor 0: " << buffer << endl;
        }

        // Destroy MPI environment
        MPI_Finalize();

        return 0;
}

int exercise_2(void) {

        // Initialize MPI environment
        MPI_Init(NULL, NULL);

        MPI_Status status;

        // Get the rank of the processor
        int world_rank = 0;
        MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

        // Get the total number of processors
        int world_size = 0;
        MPI_Comm_size(MPI_COMM_WORLD, &world_size);

        // Text to send
        char * text = "Hello World !";
        int size = strlen(text);

        // Buffer for receive message
        char buffer[size];

        // Send message to next processor and receive message from previous processor
        MPI_Send(text, size, MPI_CHAR, (world_rank + 1) % world_size, 0, MPI_COMM_WORLD);
        MPI_Recv(buffer, size, MPI_CHAR, (world_rank + world_size - 1) % world_size, 0, MPI_COMM_WORLD, &status);
        cout << "Processor " << world_rank <<  " receive from processor " << (world_rank + world_size - 1) % world_size << " the message: " << buffer << endl;

        // Destroy MPI environment
        MPI_Finalize();

        return 0;
}

int exercise_3(void) {

	MPI_Status status;

        // Initialize MPI environment
	MPI_Init(NULL, NULL);

        // Get the rank of the processor
	int world_rank = 0;
	MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

        // Get the total number of processors
	int world_size = 0;
	MPI_Comm_size(MPI_COMM_WORLD, &world_size);

        // Initialize message to send and buffer
	char * text = "Hello world !";
	int size = strlen(text);

	char buffer[size];
        
	int mask = 1;

        // Send message to processor which rank is different from just one bit of the current processor if the other processor's rank is smaller, else send message to this processor
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

        // Destroy MPI environment
	MPI_Finalize();

	return 0;
}


