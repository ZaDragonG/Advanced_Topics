#include <stdio.h>
#include <time.h>
#include "Augmented-FreeRTOS/benchmark.h"  // Make sure this path is correct relative to your build

#define BATCH_SIZE 10000
#define NUM_RUNS   100

int main(void) {
    FILE *fp = fopen("benchmark_results_gpos.csv", "w");
    if (!fp) {
        perror("Failed to open file");
        return 1;
    }

    fprintf(fp, "run_number,ticks,ms\n");

    for (int run = 1; run <= NUM_RUNS; ++run) {
        clock_t start = clock();

        for (int i = 0; i < BATCH_SIZE; ++i) {
            process_data();
        }

        clock_t end = clock();
        double elapsed_ms = ((double)(end - start)) / CLOCKS_PER_SEC * 1000.0;

        // Convert milliseconds to a tick-like value for easier comparison
        // Assuming RTOS tick is 10 ms (configTICK_RATE_HZ = 100)
        unsigned int ticks = (unsigned int)(elapsed_ms / 10);

        fprintf(fp, "%d,%u,%.0f\n", run, ticks, elapsed_ms);
        fflush(fp);
    }

    fclose(fp);

    printf("GPOS benchmark complete. Results saved to benchmark_results_gpos.csv\n");

    return 0;
}
