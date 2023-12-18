#!/bin/sh
#SBATCH --job-name Michel_TP7			# Permit us to find easily our job
#SBATCH --output ./out/Michel_TP7-out.o%j	# Outputs will be written here
#SBATCH --error ./err/Michel_TP7-err.e%j	# Errors will be written here
#SBATCH --gpus 1
#SBATCH --partition shared-gpu			# Partition to use
#SBATCH --time 15:00				# Maximum time execution

# Load modules for compiling and run program
# module load foss/2018b
# module load NVHPC/21.9
module load foss/2018b
# module load CUDA
module load NVHPC/21.9

echo $CUDA_VISIBLE_DEVICES

make gpu

./tp7 -i 256 -s 512
