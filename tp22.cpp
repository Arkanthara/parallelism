#include<mpi.h>
#define N 20

using namespace std;

int main() {

        MPI_Init(NULL, NULL);

        MPI_Status status;

        int world_rank = 0;
        MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

        int world_size = 0;
        MPI_Comm_size(MPI_COMM_WORLD, &world_size);

        // Text to send
        char * text = "Hello World !\0";
        int size = strlen(text);

        // Buffer for receive message
        char buffer[N];

        MPI_Send(text, size, MPI_CHAR, (world_rank + 1) % 4, 0, MPI_COMM_WORLD);
        MPI_Recv(buffer, N, MPI_CHAR, (world_rank + 3) % 4, 0, MPI_COMM_WORLD, &status);
        printf("Processor %d receive from processor %d the message: %s\n", world_rank, (world_rank + 3) % 4, buffer);

        MPI_Finalize();

        return 0;
}
