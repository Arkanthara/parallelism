#!/bin/sh
#SBATCH --job-name Michel_TP6			# Permit us to find easily our job
#SBATCH --output ./out/Michel_TP6-out.o%j	# Outputs will be written here
#SBATCH --error ./err/Michel_TP6-err.e%j	# Errors will be written here
#SBATCH --ntasks 1				# Number of tasks in our job
#SBATCH --cpus-per-task 32
#SBATCH --partition shared-cpu			# Partition to use
#SBATCH --time 60:00				# Maximum time execution

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


# Vary number of threads for a number of iterations fixed to 1024
# Thread number
for j in 8 16 32 64; do
	# Chunk size
	for i in 1 2 4 8 16 32 64 128 256 512 1024 2048; do
		make define_chunk_size CHUNK_SIZE=$i
		make
		echo "Region 1"
		./tp6_static -i 1024 -n $j
		./tp6_dynamic -i 1024 -n $j
		
		echo "Region 2"
		./tp6_static -c 0.3 0.3 0.5 0.5 -i 1024 -n $j
		./tp6_dynamic -c 0.3 0.3 0.5 0.5 -i 1024 -n $j
		
		echo "Region 3"
		./tp6_static -c -2 -2 2 2 -i 1024 -n $j
		./tp6_dynamic -c -2 -2 2 2 -i 1024 -n $j
	done
done

# Vary number of iterations for a thread number fixed to 32
# Number of iterations
for k in 128 256 512 1024; do
	# Chunk size
	for i in 1 2 4 8 16 32 64 128 256 512 1024 2048; do
		make define_chunk_size CHUNK_SIZE=$i
		make
		echo "Region 1"
		./tp6_static -i $k -n 32
		./tp6_dynamic -i $k -n 32
		
		echo "Region 2"
		./tp6_static -c 0.3 0.3 0.5 0.5 -i $k -n 32
		./tp6_dynamic -c 0.3 0.3 0.5 0.5 -i $k -n 32
		
		echo "Region 3"
		./tp6_static -c -2 -2 2 2 -i $k -n 32
		./tp6_dynamic -c -2 -2 2 2 -i $k -n 32
	done
done
