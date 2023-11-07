#!/bin/sh
#SBATCH --job-name Michel_TP2          # Permit us to find easily our job
#SBATCH --output ./out/Michel_TP2-out.o%j    # Outputs will be written here
#SBATCH --error ./err/Michel_TP2-err.e%j     # Errors will be written here
#SBATCH --ntasks 16                    # Number of tasks in our job
#SBATCH --cpus-per-task 1              # Number of cpus per tasks
#SBATCH --partition debug-cpu          # Partition to use
#SBATCH --time 15:00                   # Maximum time execution

# Load modules for compiling and run program
module load foss
module load CUDA

echo $SLURM_NODELIST

# Compile program
make
# Run program. If the parameter is not given to execute an exercise, we print an error which will be in ./err/Michel_TP2-err.e%j
# Else, we execute program
if [ -n "$1" ]; then
	srun --mpi=pmi2 ./tp2 $1
else
	echo "Error ! Usage of the script: ./run.sh [number of the exercise]" 1>&2
fi
