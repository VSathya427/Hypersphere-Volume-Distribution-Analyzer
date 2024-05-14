# CS547: Final
## Name: Sathya Vemulapalli

-----------------------------------------------------------------------
## Instruction to compile ball_samp-cpu.c:

```bash
make
```

Description: Compiles code and generates required file inside the folder.

-----------------------------------------------------------------------
## Instruction to run  ball_samp-cpu.c:

**The code submitted runs using the following command as per the required specification**

```bash
./ball_samp-cpu
```


-----------------------------------------------------------------------
## Instruction to compile ball_samp-cpu.cu:

First we will need to load module cuda into hpc:

```bash
module load cuda
```

Also need to load python probably

```bash
module load python
```

Then to compile we can run:

```bash
nvcc -o ball_samp-cuda ball_samp-cuda.cu 
```

Description: Compiles code and generates required file inside the folder.


-----------------------------------------------------------------------
## Instruction to setup cuda

I generated a graph for the cpu implementation as well. It takes way too long to run even with 3000 samples.

```bash
python hist.py
```

For the cuda program to generate plot I used a conda environment.


```bash
module load conda 
```

Created a environment:

```bash
conda create -n cs547 
```

Then to activate 

```bash
conda activate cs547
```

After that I installed the required libraries:

```bash
conda install matplotlib numpy
```

-----------------------------------------------------------------------
## Instruction to run  ball_samp-cpu.cu:

**The code can be run using the sbatch command:**
The code was run using 30k samples

```bash
sbatch run.sh
```

The plots I generated are cpu.png(generated using cpu version) and  surface_plot.png(generated using cuda version).

