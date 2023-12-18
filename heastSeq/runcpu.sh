#!/bin/sh
#SBATCH --job-name Michel_TP7			# Permit us to find easily our job
#SBATCH --output ./out/Michel_TP7-out.o%j	# Outputs will be written here
#SBATCH --error ./err/Michel_TP7-err.e%j	# Errors will be written here
#SBATCH --ntasks 1				# Number of tasks in our job
#SBATCH --cpus-per-task 32
#SBATCH --partition shared-cpu			# Partition to use
#SBATCH --time 15:00				# Maximum time execution

# Load modules for compiling and run program
module load foss/2020b
module load tbb

echo $SLURM_NODELIST

make tp7_cpu

for s in 100 1000 10000; do
	for i in 1 2 4 8 16 32 64 128 256 512; do
		./tp7_cpu -s $s -i $i
	done
done
