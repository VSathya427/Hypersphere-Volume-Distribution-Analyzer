#!/bin/bash

#SBATCH --job-name=ball_samp
#SBATCH --partition=gpu
#SBATCH --gres=gpu:1
#SBATCH --nodes=1
#SBATCH --ntasks-per-node=1
#SBATCH --cpus-per-task=1
#SBATCH --time=00:10:00

# Load necessary modules
module load cuda

# Run the CUDA program and capture the output
./ball_samp-cuda > output.txt

# Run the Python script
python3 hist_cuda.py