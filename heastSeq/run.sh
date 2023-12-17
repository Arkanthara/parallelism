#!/bin/sh
#SBATCH --job-name Michel_TP6			# Permit us to find easily our job
#SBATCH --output ./out/Michel_TP6-out.o%j	# Outputs will be written here
#SBATCH --error ./err/Michel_TP6-err.e%j	# Errors will be written here
#SBATCH --ntasks 1				# Number of tasks in our job
#SBATCH --cpus-per-task 32
#SBATCH --partition shared-cpu			# Partition to use
#SBATCH --time 15:00				# Maximum time execution

# Load modules for compiling and run program
module load foss
module load CUDA

echo $SLURM_NODELIST

make cpu
