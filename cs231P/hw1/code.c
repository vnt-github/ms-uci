// normal_distribution example
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define TOLERANCE 0.001
#define MAX_CYCLES 1000000

/**
 * generate a uniformly distributed random value between 0 and 1
 * @return a random double value between 0 and 1
 * */
double rand_gen() {
   return ( (double)(rand()) + 1.0 )/( (double)(RAND_MAX) + 1.0 );
}

// Returns a scaled random value with a floor of @param range_low and a ceiling of @param range_high

/**
 * Returns a scaled random value with a floor of range_low and a ceiling of range_high
 * @param range_low is the lower range
 * @param range_high is the upper range
 * @return a scaled random value
 * */
int getUniformRandomDistribution(int range_low, int range_high) {
    int range = range_high - range_low + 1;
    int rand_scaled = (rand_gen()*range) + range_low;
    return rand_scaled;
}


/**  
 * using Box–Muller_transform Generates normal distribution of two random variables between 0 and 1
 * Multiplied with standard_deviation and added to mean to generate the desired distribution.
 * @param mean is the mean of the random normal distribution
 * @param standard_deviation is the standard deviation for the random normal distribution
 * @return double random value by normal random distribution
 */
double getNormalRandomDistribution(double mean, double standard_deviation) {
    double v1 = rand_gen();
    double v2 = rand_gen();
    double normal_rand = cos(2*3.14*v2)*sqrt(-2.0*log(v1))*standard_deviation + mean;
    return normal_rand;
}

/**
 * Initializes an int array with desired value
 * @param size is the number of values in the array
 * @param arr is the array to be initialized
 * @param value is the default value to be initialized with
 * */
void initArr(int size, int arr[], double value) {
    for (int i = 0; i <= size; i++)
    {
        arr[i] = value;
    }
}

/**
 * Initializes Memory Modules of specific count
 * @param size is the number of memory_modules
 * @param memory_modules is the array to be initialized
 * */
void initMemoryModules(int size, int memory_modules[]) {
    initArr(size, memory_modules, 0);
}

/**
 * Initializes processors of specific count
 * @param size is the number processors
 * @param processors is the array to be initialized
 * */
void initProcessors(int size, int processors[]) {
    initArr(size, processors, 0);
}

/**
 * Creates a uniform distribution for processors where any processor can request any available memory module.
 * @param num_processors is the count of processors
 * @param processors is the array representing processors
 * @param num_memory_modules is the number of memory modules 
 * */
void setUniformDistributionRequest(int num_processors, int processors[], int num_memory_modules) {
    for (int i = 1; i < num_processors; i++)
    {
        if (processors[i] != 0) continue;
        processors[i] = getUniformRandomDistribution(1, num_memory_modules-1);
    }
}

/**
 * In the first cycle, generates a uniform distribution for processors where any processor can request any available memory module.
 * In the following cycles, creates a normal distribution with the constrains defined in the problem description.
 * @param num_processors is the count of processors
 * @param processors is the array representing processors
 * @param num_memory_modules is the count of memory modules
 * @param memory_modules is the array representing memory modules
 * @param is_first_cycle tells if it's the first cycle
 * @param means is the array representing the means set for each processors.
 * 
 * */
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


/**
 * Creates the workload distribution for the simulation depending upon the input from distribution_type.
 * @param num_processors is the count of processors
 * @param processors is the array representing processors
 * @param num_memory_modules is the count of memory modules
 * @param memory_modules is the array representing memory modules
 * @param distribution_type is the distribution type to be followed for locality of reference for memory access
 * @param is_first_cycle tells if it's the first cycle
 * @param means is the array representing the means set for each processors.
 * */
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

/**
 * Allocates a memory module to a particular processor in cyclic priority order starting from start_i if possible or else increments the access_time[] of that particular processor. 
 * @param num_processors is the count of processors
 * @param processors is the array representing processors
 * @param num_memory_modules is the count of memory modules
 * @param memory_modules is the array representing memory modules
 * @param access_time is array storing the access time for each processor
 * @param start_i the processor index in cyclic order from which the allocation should start
 * */
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

/**
 * Calculates and returns the arithematic average of the time cumulative access-time for the entire system after a specific number of cycle.
 * @param cycle is the number of cyles occured till now
 * @param num_processors is the count of processors
 * @param access_times is the array containing the access times for each processors
 * @return a double value that is the arithematic average of the time cumulative access time.
 * */
double getSystemAverageAccessTime(int cycle, int num_processors, int access_times[]) {
  
    double time_cumulative_access_time_sum = 0;
    for (int i = 1; i < num_processors; i++)
    {
        time_cumulative_access_time_sum += (cycle) / (cycle-access_times[i]);
    }
    double arithematic_average_time_cumulative_access_time = time_cumulative_access_time_sum/(num_processors-1);
    return arithematic_average_time_cumulative_access_time;
}

/**
 * Determines the next processor to be given access first in the next cycle.
 * @param num_processors is the count of processors
 * @param processors is the array representing the processors
 * @return the index of the processors to be given priority while allocating memory modules.
 * */
int getNextStart(int num_processors, int processors[]) {
  
    for (int i = 0; i < num_processors; i++)
    {
        if (processors[i] != 0)
            return i;
    }
    return 1;
}

/**
 * Determines whether a particular cycleshould be skipped due to insufficient allocated memory modules
 * @param cycle is the number of cyles occured till now
 * @param num_processors is the count of processors
 * @param access_times is the array containing the access times for each processors
 * */
int skipCycle(int cycle, int num_processors, int access_times[]) {
    for (int i = 0; i < num_processors; i++)
    {
        if (cycle == access_times[i])
            return 1;
    }
    return 0;
}

/**
 * the main loop which runs from 1 to MAX_CYCLES cycles and request and allocates the memory request for processors based on distribution type
 * and returns average system memory access time
 * @param num_processors is the count of processors
 * @param num_memory_modules is the count of the memory modules
 * @param distribution_type is the char representing the distribution type to be followed
 * @return double value representing the average system memory access time for a provided configuration
 * */
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
    double w = INFINITY;
    double w_prev = -100000;
    int start_i = 1;
    for (int cycle = 1; cycle < MAX_CYCLES + 1; cycle++)
    {
        if (cycle > 1) is_first_cycle = 0;
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

/**
 * helper function to verify the validity of the Uniform random distribution function
 * @param upper_value is the upper limit for the uniform random distribution
 * */
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

/**
 * helper function to verify the validity of the normal random distribution function
 * @param upper_value is the upper limit for the normal random distribution
 * */
void verifyNormalDistribution(int upper_value) {
    int vals[upper_value];
    initArr(upper_value, vals, 0);

    double x;

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

/**
 * runs the simulation from 1 to max_no_memory_modules number of memory modules and logs the average system memory access time for given number of processors
 * @param num_processors is the nubmer of processors
 * @param distribution_type is the char representing the distribution type to be followed
 * @param max_no_memory_modules is the max number of memory modules to be simulated
 * */
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

