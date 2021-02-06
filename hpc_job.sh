#!/bin/sh
#BSUB -q hpc
#BSUB -J Pepper_Planner
#BSUB -n 1
#BSUB -R "span[hosts=1]"
#BSUB -R "rusage[mem=64]"
#BSUB -M 128GB
#BSUB -W 01:00
#BSUB -u s164438@student.dtu.dk
#BSUB -B
#BSUB -N
#BSUB -o Output_%J.out

module load cmake/3.18.2
module load gcc/9.2.0
build_and_run.sh > print.out
