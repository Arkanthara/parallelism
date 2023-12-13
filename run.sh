#!/bin/sh
#SBATCH --job-name Michel_TP6			# Permit us to find easily our job
#SBATCH --output ./out/Michel_TP6-out.o%j	# Outputs will be written here
#SBATCH --error ./err/Michel_TP6-err.e%j	# Errors will be written here
#SBATCH --ntasks 1				# Number of tasks in our job
#SBATCH --cpus-per-task 32
#SBATCH --partition shared-cpu			# Partition to use
#SBATCH --time 30:00				# Maximum time execution

# Load modules for compiling and run program
module load foss
module load CUDA

echo $SLURM_NODELIST

# Set OMP_NUM_THREADS to the same value as --cpus-per-task
# with a fallback in case it isn't set.
# SLURM_CPUS_PER_TASK is set to the value of --cpus-per-task, but only if --cpus-per-task is explicitly set
# if [ -n "$SLURM_CPUS_PER_TASK" ]; then
#   omp_threads=$SLURM_CPUS_PER_TASK
# else
#   omp_threads=1
# fi
# export OMP_NUM_THREADS=$omp_threads

# iter=100
# 
# if [ -n "$1" ]; then
# 	iter=$1
# fi

# Run program
for k in 64 128 256 512 1024; do
	for i in 1 2 4 8 16 32 64 128 256 512 1024 2048; do
		for j in 1 2 4 8 16 32 64 128; do
			make define_chunk_size CHUNK_SIZE=$i
			make
			echo "Region 1"
			./tp6_static -i $k -n $j
			./tp6_dynamic -i $k -n $j
			
			echo "Region 2"
			./tp6_static -c 0.3 0.3 0.5 0.5 -i $k -n $j
			./tp6_dynamic -c 0.3 0.3 0.5 0.5 -i $k -n $j
			
			echo "Region 3"
			./tp6_static -c -2 -2 2 2 -i $k -n $j
			./tp6_dynamic -c -2 -2 2 2 -i $k -n $j
		done
	done
done
