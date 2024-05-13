#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define NUM_INTERVALS 100
#define NUM_DIMENSIONS 15
#define NUM_SAMPLES 3000

// Function to generate a random number between 0 and 1
double rand_double(void)
{
    return (double)rand() / RAND_MAX;
}

// Function to compute the squared Euclidean norm of a vector
double squared_norm(double *v, int dim)
{
    double sum = 0.0;
    for (int i = 0; i < dim; i++)
    {
        sum += v[i] * v[i];
    }
    return sum;
}


int main(void)
{
    printf("Started!");
    return 0;
}

