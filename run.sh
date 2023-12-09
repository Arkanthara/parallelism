#!/bin/sh
#SBATCH --job-name Michel_TP6          # Permit us to find easily our job
#SBATCH --output ./out/Michel_TP6-out.o%j    # Outputs will be written here
#SBATCH --error ./err/Michel_TP6-err.e%j     # Errors will be written here
#SBATCH --ntasks 1                     # Number of tasks in our job
#SBATCH --cpus-per-task 16             # Number of cpus per tasks
#SBATCH --partition debug-cpu          # Partition to use
#SBATCH --time 15:00                   # Maximum time execution

# Load modules for compiling and run program
module load foss

echo $SLURM_NODELIST

# Compile program
make
# Run program. If the parameters aren't given to execute the program, we print an error which will be in ./err/Michel_TP6-err.e%j
# Else, we execute program, variyng number of threads
srun ./tp6_static
srun ./tp6_dynamic
