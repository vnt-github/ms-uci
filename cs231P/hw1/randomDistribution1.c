// normal_distribution example
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

double rand_gen() {
   // return a uniformly distributed random value between 0 and 1
   return ( (double)(rand()) + 1.0 )/( (double)(RAND_MAX) + 1.0 );
}

int getUniformRandomDistribution(int range_low, int range_high) {
    int range = range_high - range_low + 1;
    int rand_scaled = (rand_gen()*range) + range_low;
    return rand_scaled;
}

// Box–Muller_transform
double getNormalRandomDistribution(int no_memory_modules, double mean, double standard_deviation) {
    double v1 = rand_gen();
    double v2 = rand_gen();
    return cos(2*3.14*v2)*sqrt(-2.*log(v1))*standard_deviation + mean;
}

int main()
{
    int freq[11] = {0};
    int rand_value;
    srand(time(0));
    for (int i = 0; i < 200; i++)
    {
        rand_value = getUniformRandomDistribution(1, 10);
        printf("%d ", rand_value);
        freq[rand_value] += 1;
    }

    printf("\n");

    for (int i = 0; i < 11; i++)
    {
        printf("%d %d\n", i, freq[i]);
    }
    
    for (int i = 0; i < 10; i++)
    {
        printf("%f\n", getNormalRandomDistribution(7, 1, 1));
    }

}

