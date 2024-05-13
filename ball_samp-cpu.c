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

// Sequential implementation
void ball_samp_cpu()
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

            // Generate a random point within the hypercube
            do
            {
                for (int j = 0; j < dim; j++)
                {
                    point[j] = 2.0 * rand_double() - 1.0;
                }
                norm_squared = squared_norm(point, dim);
            } while (norm_squared > 1.0); // Reject points outside the hypersphere

            // Compute the distance from the surface
            double distance = sqrt(1.0 - norm_squared);

            // Update the histogram
            int bin = (int)(distance * NUM_INTERVALS);
            histogram[bin]++;
            num_inside++;
        }

        // Print the histogram
        for (int i = 0; i < NUM_INTERVALS; i++)
        {
            double fraction = histogram[i] / (double)num_inside;
            printf("%lf ", fraction);
        }
        printf("\n");
    }
}

int main(int argc, char *argv[])
{
    srand(time(NULL));
    ball_samp_cpu();
    return 0;
}

