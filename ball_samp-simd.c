#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <immintrin.h>

#define NUM_INTERVALS 100
#define NUM_DIMENSIONS 16
#define NUM_SAMPLES 3000

// Function to generate a random number between 0 and 1
double rand_double(void)
{
    return (double)rand() / RAND_MAX;
}

// Function to compute the squared Euclidean norm of a vector using AVX2 intrinsics
double squared_norm_simd(double *v, int dim)
{
    __m256d sum = _mm256_setzero_pd();
    int i;

    for (i = 0; i + 7 < dim; i += 8)
    {
        __m256d x = _mm256_loadu_pd(v + i);
        __m256d y = _mm256_loadu_pd(v + i + 4);
        x = _mm256_mul_pd(x, x);
        y = _mm256_mul_pd(y, y);
        sum = _mm256_add_pd(sum, x);
        sum = _mm256_add_pd(sum, y);
    }

    double sum_scalar = 0.0;
    double temp[4] __attribute__((aligned(32)));
    _mm256_store_pd(temp, sum);
    sum_scalar = temp[0] + temp[1] + temp[2] + temp[3];

    for (; i < dim; i++)
    {
        sum_scalar += v[i] * v[i];
    }

    return sum_scalar;
}

// SIMD-accelerated implementation
void ball_samp_simd(void)
{
    for (int dim = 2; dim <= NUM_DIMENSIONS; dim++)
    {
        printf("Dimension: %d\n", dim);
        double histogram[NUM_INTERVALS] = {0.0};
        int num_inside = 0;
        for (int i = 0; i < NUM_SAMPLES; i++)
        {
            double point[dim];
            double norm_squared;
            do
            {
                for (int j = 0; j < dim; j++)
                {
                    point[j] = 2.0 * rand_double() - 1.0;
                }
                norm_squared = squared_norm_simd(point, dim);
            } while (norm_squared > 1.0);

            double distance = sqrt(1.0 - norm_squared);
            int bin = (int)(distance * NUM_INTERVALS);
            histogram[bin]++;
            num_inside++;
        }

        for (int i = 0; i < NUM_INTERVALS; i++)
        {
            double fraction = histogram[i] / (double)num_inside;
            printf("%lf ", fraction);
        }
        printf("\n");
    }
}

int main(void)
{
    srand(time(NULL));
    ball_samp_simd();
    return 0;
}