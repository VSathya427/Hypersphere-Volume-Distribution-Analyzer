#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <cuda_runtime.h>

#define NUM_INTERVALS 100
#define NUM_DIMENSIONS 16
#define NUM_SAMPLES 30000
#define BLOCK_SIZE 256

// Function to generate a random number between 0 and 1
__host__ __device__ double rand_double(unsigned int &seed)
{
    seed = (seed * 1103515245 + 12345) & 0x7fffffff;
    return (double)seed / (double)0x7fffffff;
}

// Function to compute the squared Euclidean norm of a vector
__device__ double squared_norm(double *v, int dim)
{
    double sum = 0.0;
    for (int i = 0; i < dim; i++)
    {
        sum += v[i] * v[i];
    }
    return sum;
}

// Kernel function to generate random points and compute histogram
__global__ void ball_samp_kernel(int *histogram, int dim, int num_samples, unsigned int *seeds)
{
    int idx = blockIdx.x * blockDim.x + threadIdx.x;
    if (idx >= num_samples)
        return;

    double point[NUM_DIMENSIONS];
    double norm_squared;
    unsigned int seed = seeds[idx];

    do
    {
        for (int j = 0; j < dim; j++)
        {
            point[j] = 2.0 * rand_double(seed) - 1.0;
        }
        norm_squared = squared_norm(point, dim);
    } while (norm_squared > 1.0);

    double distance = sqrt(1.0 - norm_squared);
    int bin = (int)(distance * NUM_INTERVALS);
    atomicAdd(&histogram[bin], 1);
}

// Sequential implementation
void ball_samp_cpu()
{
    for (int dim = 2; dim <= NUM_DIMENSIONS; dim++)
    {
        printf("Dimension: %d\n", dim);
        int histogram[NUM_INTERVALS] = {0};

        unsigned int *seeds;
        cudaMallocManaged(&seeds, NUM_SAMPLES * sizeof(unsigned int));
        for (int i = 0; i < NUM_SAMPLES; i++)
        {
            seeds[i] = rand();
        }

        int *d_histogram;
        cudaMalloc(&d_histogram, NUM_INTERVALS * sizeof(int));
        cudaMemset(d_histogram, 0, NUM_INTERVALS * sizeof(int));

        int grid_size = (NUM_SAMPLES + BLOCK_SIZE - 1) / BLOCK_SIZE;
        ball_samp_kernel<<<grid_size, BLOCK_SIZE>>>(d_histogram, dim, NUM_SAMPLES, seeds);
        cudaDeviceSynchronize();

        cudaMemcpy(histogram, d_histogram, NUM_INTERVALS * sizeof(int), cudaMemcpyDeviceToHost);

        for (int i = 0; i < NUM_INTERVALS; i++)
        {
            double fraction = (double)histogram[i] / (double)NUM_SAMPLES;
            printf("%lf ", fraction);
        }
        printf("\n");

        cudaFree(d_histogram);
        cudaFree(seeds);
    }
}

int main(int argc, char *argv[])
{
    srand(time(NULL));
    ball_samp_cpu();
    return 0;
}