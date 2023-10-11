#include <mpi.h>
#include <string.h>
#define N 20


int main(void) {

	MPI_Status status;

	MPI_Init(NULL, NULL);

	int mask = 1;

	int world_rank = 0;

	MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

	int world_size = 0;

	MPI_Comm_size(MPI_COMM_WORLD, &world_size);

	char * text = "Hello world !\0";
	int size = strlen(text);

	char buffer[N];

	while (world_size > mask) {
		int process = world_rank ^ mask;
		if (process > world_rank) {
			MPI_Recv(buffer, N, MPI_CHAR, process, 0, MPI_COMM_WORLD, &status);
			printf("Processor %d received %s from processor %d\n", world_rank, buffer, process);
		}
		else {
			MPI_Send(text, size, MPI_CHAR, process, 0, MPI_COMM_WORLD);
		}
		mask = mask << 1;
	}

	MPI_Finalize();

	return 0;
}
