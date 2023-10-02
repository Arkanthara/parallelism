# TP1

#### Author: Michel Donnet

### Explanation

The MPI programm is used for exchanging messages between multiple computers running a parallel programm accross distributed memory.

So for each processor which is running, we want to print "Hello World" and informations about the processor into the console.

At the begining of the programm, we initialize the MPI execution environment, which permits to use multiple processors and run multiple instances of our programm.

Then, we takes informations about the current processor, like it rank, it name and the number of processors

Finally, we print all informations and terminate MPI execution environment.

### Challenges encountered

At the begining, I can't run my programm because I don't initialize the mpi environment. But the commands "$ module load mpi", "$ mpic++ tp1.cpp" for compile my program, and
"$ mpirun -np 4 a.out" to run the programm with 4 processors fix my problem.

### Functions used

int MPI_Init(int *argc, char ***argv): Initialize the MPI execution environment

int MPI_Comm_size(MPI_Comm comm, int *size): Returns the size (int * size) of the group associated with a communicator (MPI_Comm comm). In our code, we use MPI_COMM_WORLD which is
the default communicator that contains all processes available for use.

int MPI_Comm_rank(MPI_Comm comm, int *rank): Determines the rank of the calling process in the communicator. Same comment

int MPI_Get_processor_name(char *name, int *resultlen): Give the name of the processor into char * name and store the length of the name in resultlen

int MPI_Finalize(): Terminates MPI execution environment.





