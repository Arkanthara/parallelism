#include<mpi.h>
#include<string.h>
#define N 20

using namespace std;

int main() {

        MPI_Init(NULL, NULL);

        MPI_Status status;

        int world_rank = 0;
        MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

        int world_size = 0;
        MPI_Comm_size(MPI_COMM_WORLD, &world_size);

        char * text = "Hello world !\n\0";
        int size = strlen(text);

        if (world_rank == 0) {
                for (int i = 1; i < world_size; i++) {
                        MPI_Send(text, size, MPI_CHAR, i, 0, MPI_COMM_WORLD);
                }
        }
        else {
                char buffer[N];
                MPI_Recv(buffer, N, MPI_CHAR, 0, 0, MPI_COMM_WORLD, &status);
                printf("Message received by processor %d from processor 0: %s", world_rank, buffer);
        }

        MPI_Finalize();

        return 0;
}
