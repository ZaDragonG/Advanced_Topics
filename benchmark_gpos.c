#include <stdio.h>
#include <time.h>
#include "Augmented-FreeRTOS/benchmark.h" 

#define INITIAL_BATCH_SIZE 100
#define BATCH_STEP         100
#define NUM_RUNS           1000  

int main(void) {
    FILE *fp = fopen("benchmark_results_gpos.csv", "w");
    if (!fp) {
        perror("Failed to open file");
        return 1;
    }

    fprintf(fp, "run_number,ticks,ms,batch_size\n");

    for (int run = 1; run <= NUM_RUNS; ++run) {
        int batch_size = INITIAL_BATCH_SIZE + (run - 1) * BATCH_STEP;

        clock_t start = clock();

        for (int i = 0; i < batch_size; ++i) {
            process_data();
        }

        clock_t end = clock();
        double elapsed_ms = ((double)(end - start)) / CLOCKS_PER_SEC * 1000.0;
        unsigned int ticks = (unsigned int)(elapsed_ms / 10);
        fprintf(fp, "%d,%u,%.0f,%d\n", run, ticks, elapsed_ms, batch_size);
        fflush(fp);
    }

    fclose(fp);

    printf("GPOS benchmark complete. Results saved to benchmark_results_gpos.csv\n");

    return 0;
}
