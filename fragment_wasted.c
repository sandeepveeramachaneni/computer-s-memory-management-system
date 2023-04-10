#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

// Define the memory structure
#define MEMORY_SIZE 1024
#define BLOCK_SIZE 16

// Initialize the memory block with empty flags
int memory[MEMORY_SIZE / BLOCK_SIZE] = {0};

// Memory Allocation Algorithm: First-Fit
int allocate_memory(int size) {

    int blocks = size / BLOCK_SIZE;

    int start = -1;

    int count = 0;

    for (int i = 0; i < MEMORY_SIZE / BLOCK_SIZE; i++) {
        if (memory[i] == 0) {
            if (start == -1) {
                start = i;
            }
            count++;
        } else {
            start = -1;
            count = 0;
        }
        if (count == blocks) {
            for (int j = start; j < start + blocks; j++) {
                memory[j] = 1;
            }
            return start * BLOCK_SIZE;
        }
    }
    return -1;
}

// Deallocation of memory
void deallocate_memory(int start, int size) {
    int blocks = size / BLOCK_SIZE;
    for (int i = start / BLOCK_SIZE; i < (start + size) / BLOCK_SIZE; i++) {
        memory[i] = 0;
    }
}

// Simulation loop
#define SIMULATION_TIME 10 // in time units
#define TIME_UNIT 0.01 // in seconds
int fragmentation[SIMULATION_TIME] = {0};

int wasted_blocks[SIMULATION_TIME] = {0};

int wasted_count = 0;

int main() {
    // Seed the random number generator
    srand(time(NULL));

    for (int t = 0; t < SIMULATION_TIME; t++) {
        // Generate a random process
        int process_size = rand() % 241 + 16;

        // Allocate memory for the process
        int start = allocate_memory(process_size);
        if (start == -1) {
            printf("Memory allocation failed for process size %d\n", process_size);
            wasted_blocks[wasted_count] = process_size / BLOCK_SIZE;
            wasted_count++;
        }
        else {
            // Simulate the process running for some time
            printf("Process allocated at start %d with size %d\n", start, process_size);
            usleep(100000);
            // Deallocate memory when the process completes
            deallocate_memory(start, process_size);
        }

        // Calculate fragmentation and wasted blocks at the end of each time unit

        int fragments = 0;

        int wasted = 0;

        int count = 0;

        for (int i = 0; i < MEMORY_SIZE / BLOCK_SIZE; i++) {
            if (memory[i] == 0) {
                count++;
            } else {
                if (count > 0) {
                    fragments++;
                    wasted += count;
                    count = 0;
                }
            }
        }
        if (count > 0) {
            fragments++;
            wasted += count;
        }

        fragmentation[t] = fragments;

        wasted_blocks[wasted_count] = wasted;

        wasted_count++;

        // Wait for the next time unit
        usleep(TIME_UNIT * 1000000);
    }
// Calculate the average fragmentation and wasted blocks per time unit

int total_fragmentation = 0;

int total_wasted_blocks = 0;

for (int i = 0; i < SIMULATION_TIME; i++) {

total_fragmentation += fragmentation[i];
total_wasted_blocks += wasted_blocks[i];

}

float avg_fragmentation = (float) total_fragmentation / SIMULATION_TIME;

float avg_wasted_blocks = (float) total_wasted_blocks / (SIMULATION_TIME * MEMORY_SIZE / BLOCK_SIZE);

// Print the results

printf("Average fragmentation: %f\n", avg_fragmentation);

printf("Average wasted blocks per unit time: %f\n", avg_wasted_blocks);

return 0;

}

