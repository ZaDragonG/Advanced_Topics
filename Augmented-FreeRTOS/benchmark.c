#include "benchmark.h"

int data[DATA_SIZE];

void generate_data() {
    for (int i = 0; i < DATA_SIZE; ++i)
        data[i] = i;
}

void process_data() {
    volatile int result = 0;
    for (int i = 0; i < DATA_SIZE; ++i)
        result += data[i] * data[i];
}


