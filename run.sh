#!/bin/sh
#SBATCH --job-name Michel_TP2          # Permit us to find easily our job
#SBATCH --output Michel_TP2-out.o%j    # This is the file where the outputs will be written
#SBATCH --error Michel_TP2-err.e%j     # This is the file where the errors will be written
#SBATCH --ntasks 16                    # Number of tasks in our job
#SBATCH --cpus-per-task 1              # Number of cpus per tasks
#SBATCH --partition debug-cpu          # Partition to use
#SBATCH --time 15:00                   # Maximum time execution

module load foss
module load CUDA

echo $SLURM_NODELIST

srun --mpi=pmi2 ./tp2 $1
