#!/bin/sh
#SBATCH --job-name Michel_TP6			# Permit us to find easily our job
#SBATCH --output ./out/Michel_TP6-out.o%j	# Outputs will be written here
#SBATCH --error ./err/Michel_TP6-err.e%j	# Errors will be written here
#SBATCH --nodes 1				# Number of nodes used (on baobab, a node allow to use 14 cores)
#SBATCH --ntasks 1				# Number of tasks in our job
#SBATCH --cpus-per-task 14			# Number of cpus per tasks
#SBATCH --partition debug-cpu			# Partition to use
#SBATCH --time 15:00				# Maximum time execution

# Load modules for compiling and run program
module load foss
module load CUDA

echo $SLURM_NODELIST

# Compile program
make

# Set OMP_NUM_THREADS to the same value as --cpus-per-task
# with a fallback in case it isn't set.
# SLURM_CPUS_PER_TASK is set to the value of --cpus-per-task, but only if --cpus-per-task is explicitly set
if [ -n "$SLURM_CPUS_PER_TASK" ]; then
  omp_threads=$SLURM_CPUS_PER_TASK
else
  omp_threads=1
fi
export OMP_NUM_THREADS=$omp_threads

# Run program
./tp6_static
./tp6_dynamic
