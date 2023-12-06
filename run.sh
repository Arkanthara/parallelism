#!/bin/sh
#SBATCH --job-name Michel_TP6          # Permit us to find easily our job
#SBATCH --output ./out/Michel_TP6-out.o%j    # Outputs will be written here
#SBATCH --error ./err/Michel_TP6-err.e%j     # Errors will be written here
#SBATCH --ntasks 1                     # Number of tasks in our job
#SBATCH --cpus-per-task 32             # Number of cpus per tasks
#SBATCH --partition debug-cpu          # Partition to use
#SBATCH --time 15:00                   # Maximum time execution

# Load modules for compiling and run program
module load foss

echo $SLURM_NODELIST

# Compile program
make
# Run program. If the parameters aren't given to execute the program, we print an error which will be in ./err/Michel_TP6-err.e%j
# Else, we execute program, variyng number of threads
if [ -n "$5" ]; then
	echo "Static execution"
	srun ./tp6 -c $1 $2 $3 $4 -i 256 -n 1 -s $5
	srun ./tp6 -c $1 $2 $3 $4 -i 256 -n 2 -s $5
	srun ./tp6 -c $1 $2 $3 $4 -i 256 -n 4 -s $5
	srun ./tp6 -c $1 $2 $3 $4 -i 256 -n 8 -s $5
	srun ./tp6 -c $1 $2 $3 $4 -i 256 -n 16 -s $5
	srun ./tp6 -c $1 $2 $3 $4 -i 256 -n 32 -s $5
	srun ./tp6 -c $1 $2 $3 $4 -i 256 -n 64 -s $5
	srun ./tp6 -c $1 $2 $3 $4 -i 256 -n 128 -s $5
	srun ./tp6 -c $1 $2 $3 $4 -i 256 -n 256 -s $5
	srun ./tp6 -c $1 $2 $3 $4 -i 256 -n 512 -s $5
	srun ./tp6 -c $1 $2 $3 $4 -i 256 -n 1024 -s $5
	srun ./tp6 -c $1 $2 $3 $4 -i 256 -n 2048 -s $5
	srun ./tp6 -c $1 $2 $3 $4 -i 256 -n 4096 -s $5
	srun ./tp6 -c $1 $2 $3 $4 -i 256 -n 8192 -s $5

	echo "Dynamic execution"
	srun ./tp6 -c $1 $2 $3 $4 -i 256 -n 1 -d $5
	srun ./tp6 -c $1 $2 $3 $4 -i 256 -n 2 -d $5
	srun ./tp6 -c $1 $2 $3 $4 -i 256 -n 4 -d $5
	srun ./tp6 -c $1 $2 $3 $4 -i 256 -n 8 -d $5
	srun ./tp6 -c $1 $2 $3 $4 -i 256 -n 16 -d $5
	srun ./tp6 -c $1 $2 $3 $4 -i 256 -n 32 -d $5
	srun ./tp6 -c $1 $2 $3 $4 -i 256 -n 64 -d $5
	srun ./tp6 -c $1 $2 $3 $4 -i 256 -n 128 -d $5
	srun ./tp6 -c $1 $2 $3 $4 -i 256 -n 256 -d $5
	srun ./tp6 -c $1 $2 $3 $4 -i 256 -n 512 -d $5
	srun ./tp6 -c $1 $2 $3 $4 -i 256 -n 1024 -d $5
	srun ./tp6 -c $1 $2 $3 $4 -i 256 -n 2048 -d $5
	srun ./tp6 -c $1 $2 $3 $4 -i 256 -n 4096 -d $5
	srun ./tp6 -c $1 $2 $3 $4 -i 256 -n 8192 -d $5

else
	echo "Error ! Usage of the script: $0 [tl_x tl_y br_x br_y chunk size]. Ex: $0 -1 -1 1 1 4" 1>&2
fi
