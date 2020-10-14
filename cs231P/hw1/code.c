// normal_distribution example
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define TOLERANCE 0.001

// TODO: set  to 1000000
#define MAX_CYCLES 1000000

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
double getNormalRandomDistribution(double mean, double standard_deviation) {
    double v1 = rand_gen();
    double v2 = rand_gen();
    double normal_rand = cos(2*3.14*v2)*sqrt(-2.0*log(v1))*standard_deviation + mean;
    return normal_rand;
}

void initArr(int size, int arr[], double value) {
    for (int i = 0; i <= size; i++)
    {
        arr[i] = value;
    }
}

void initMemoryModules(int size, int memory_modules[]) {
    initArr(size, memory_modules, 0);
}

void initProcessors(int size, int processors[]) {
    initArr(size, processors, 0);
}

void setUniformDistributionRequest(int num_processors, int processors[], int num_memory_modules) {
    for (int i = 1; i < num_processors; i++)
    {
        if (processors[i] != 0) continue;
        processors[i] = getUniformRandomDistribution(1, num_memory_modules-1);
    }
}

void setNormalDistributionRequest(int num_processors, int processors[], int num_memory_modules, int memory_modules[], int is_first_cycle, int means[]) {
    if (is_first_cycle) {
        setUniformDistributionRequest(num_processors, means, num_memory_modules);
        for (int i = 1; i < num_processors; i++)
        {
            processors[i] = means[i];
        }
        return;
    }
    num_memory_modules -= 1;
    double x;
    int p_val;
    for (int i = 1; i < num_processors; i++)
    {
        if (processors[i] != 0) continue;
        x = getNormalRandomDistribution(means[i], num_memory_modules/6);
        p_val = (int)round(x)%num_memory_modules;
        processors[i] = p_val+1;
    }
}


void setMemoryRequest(int num_processors, int processors[], int num_memory_modules, int memory_modules[], char distribution_type, int is_first_cycle, int means[]) {
    switch (distribution_type)
    {
    case 'u':
        setUniformDistributionRequest(num_processors, processors, num_memory_modules);
        break;
    case 'n':
        setNormalDistributionRequest(num_processors, processors, num_memory_modules, memory_modules, is_first_cycle, means);
        break;
    default:
        break;
    }
}

void allocateMemoryToProcessors(int num_processors, int processors[], int num_memory_modules, int memory_modules[], int access_times[], int start_i) {
    initArr(num_memory_modules, memory_modules, 0);
    for (int i = start_i; i-start_i < num_processors; i++)
    {
        if (memory_modules[processors[i%num_processors]] == 0) {
            memory_modules[processors[i%num_processors]] = i%num_processors;
            processors[i%num_processors] = 0;
        } else {
            access_times[i%num_processors] += 1;
        }
    }
}

double getSystemAverageAccessTime(int cycle, int num_processors, int access_times[]) {
    double time_cumulative_access_time_sum = 0;
    for (int i = 1; i < num_processors; i++)
    {
        time_cumulative_access_time_sum += (cycle) / (cycle-access_times[i]);
    }
    double arithematic_average_time_cumulative_access_time = time_cumulative_access_time_sum/(num_processors-1);
    return arithematic_average_time_cumulative_access_time;
}

int getNextStart(int num_processors, int processors[]) {
    for (int i = 0; i < num_processors; i++)
    {
        if (processors[i] != 0)
            return i;
    }
    return 1;
}

int skipCycle(int cycle, int num_processors, int access_times[]) {
    for (int i = 0; i < num_processors; i++)
    {
        if (cycle == access_times[i])
            return 1;
    }
    return 0;
}

double getAverageSystemMemoryAccessTime(int num_processors, int num_memory_modules, char distribution_type) {
    num_processors += 1;
    num_memory_modules += 1;

    int processors[num_processors];
    initProcessors(num_processors, processors);

    int means[num_processors];
    initProcessors(num_processors, means);

    int access_times[num_processors];
    initArr(num_processors, access_times, 0);



    int memory_modules[num_memory_modules];
    initMemoryModules(num_memory_modules, memory_modules);

    int is_first_cycle = 1;
    double w = 0;
    double w_prev = -100000;
    int start_i = 1;
    for (int cycle = 1; cycle < MAX_CYCLES + 1; cycle++)
    {
        if (cycle > 1) is_first_cycle = 0;
        // TODO: set the first denied processor as the start of allocation priority at the next cycle
        setMemoryRequest(num_processors, processors, num_memory_modules, memory_modules, distribution_type, is_first_cycle, means);
        allocateMemoryToProcessors(num_processors, processors, num_memory_modules, memory_modules, access_times, start_i);
        if (skipCycle(cycle, num_processors, access_times))
            continue;
        start_i = getNextStart(num_processors, processors);
        w = getSystemAverageAccessTime(cycle, num_processors, access_times);
        if (abs(1 - w_prev/w) < TOLERANCE)
            break;
        w_prev = w;
    }

    return w;
}

void verifyUniformRandomDistribution(int upper_value) {
    int vals[upper_value];
    initArr(upper_value, vals, 0);

    double freq = 1000000;
    for (int i = 0; i < freq; i++)
    {
        vals[getUniformRandomDistribution(1, upper_value)] += 1;
    }
    for (int i = 0; i < upper_value; i++)
    {
        printf("%f\n", (double)vals[i]/freq);
    }
}

void verifyNormalDistribution(int upper_value) {
    int vals[upper_value];
    initArr(upper_value, vals, 0);

    double x;
    int p_val;

    double freq = 1000000;
    for (int i = 0; i < freq; i++)
    {
        x = getNormalRandomDistribution(upper_value/2, upper_value/6);
        vals[(int)round(x)%upper_value] += 1;
    }
    for (int i = 0; i < upper_value; i++)
    {
        printf("%f\n", (double)vals[i]/freq);
    }
}

void printAverageSystemMemoryAccessTime(int num_processors, char distribution_type, int max_no_memory_modules) {
    double val;
    for (int num_memory_modules = 1; num_memory_modules <= max_no_memory_modules; num_memory_modules++)
    {
        val = getAverageSystemMemoryAccessTime(num_processors, num_memory_modules, distribution_type);
        printf("%.4f \n", val);
    }
}

int main(int argc, char const *argv[])
{
    srand(time(0));
    int num_processors = atoi(argv[1]);
    char distribution_type = *argv[2];
    int max_no_memory_modules = 2048;
    printf("p: %d c: %c \n", num_processors, distribution_type);
    printAverageSystemMemoryAccessTime(num_processors, distribution_type, max_no_memory_modules);
    

    // verifyUniformRandomDistribution(10);
    // verifyNormalDistribution(10);


}

