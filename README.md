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

I generated a graph for the cpu implementation as well. It takes way too long to run even with 3000 samples. The plot was generated using the plot below and is named cpu.png

```bash
python hist.py
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

I attempted the 10 points credit. I still want to try attempting the simd version.

-----------------------------------------------------------------------
## Instruction to compile ball_samp-simd.c:

To compile the code I used the following command:

```bash
gcc -o ball_samp-simd ball_samp-simd.c -mavx2 -lm
```

-----------------------------------------------------------------------
## Instruction to run ball_samp-simd.c:

I used this command to run the code:

```bash
./ball_samp-simd
```

I have pasted the output to output_simd.txt for the simd code. It works faster than the regular cpu version and maybe I might get result close to the one posted in piazza if I increase the number of samples. I used 3000 samples and increasing the samples is still taking a lot of time.