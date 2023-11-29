#!/bin/sh
#SBATCH --job-name Michel_TP2          # Permit us to find easily our job
#SBATCH --output ./out/Michel_TP2-out.o%j    # Outputs will be written here
#SBATCH --error ./err/Michel_TP2-err.e%j     # Errors will be written here
#SBATCH --partition debug-cpu          # Partition to use
#SBATCH --time 15:00                   # Maximum time execution

# Load modules for compiling and run program
module load foss
module load CUDA

echo $SLURM_NODELIST

# Compile program
make
# Run program. If the parameter is not given to execute an exercise, we print an error which will be in ./err/Michel_TP2-err.e%j
if [ -n "$1" ]; then
	echo "$1 64x64 10^0 to 10^5 iterations"
	srun --mpi=pmi2 ./tp3 64 1
	srun --mpi=pmi2 ./tp3 64 10
	srun --mpi=pmi2 ./tp3 64 100
	srun --mpi=pmi2 ./tp3 64 1000
	srun --mpi=pmi2 ./tp3 64 10000
	srun --mpi=pmi2 ./tp3 64 100000
	echo "$1 128x128 10^0 to 10^5 iterations"
	srun --mpi=pmi2 ./tp3 128 1
	srun --mpi=pmi2 ./tp3 128 10
	srun --mpi=pmi2 ./tp3 128 100
	srun --mpi=pmi2 ./tp3 128 1000
	srun --mpi=pmi2 ./tp3 128 10000
	srun --mpi=pmi2 ./tp3 128 100000
	echo "$1 256x256 10^0 to 10^5 iterations"
	srun --mpi=pmi2 ./tp3 256 1
	srun --mpi=pmi2 ./tp3 256 10
	srun --mpi=pmi2 ./tp3 256 100
	srun --mpi=pmi2 ./tp3 256 1000
	srun --mpi=pmi2 ./tp3 256 10000
	srun --mpi=pmi2 ./tp3 256 100000
else
	echo "Usage: sbatch -n nb run.sh nb"
fi
