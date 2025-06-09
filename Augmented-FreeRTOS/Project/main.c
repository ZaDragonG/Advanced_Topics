// main.c

#include <stdio.h>
#include <stdlib.h>
#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"
#include "benchmark.h"

void benchmark_task(void *pvParameters);
void vApplicationIdleHook(void);

int main(void)
{
    // Create the benchmark task
    xTaskCreate(
        benchmark_task,              // Task function
        "Benchmark",                 // Name
        configMINIMAL_STACK_SIZE*2,  // Stack size
        NULL,                        // Parameters
        1,                           // Priority
        NULL                         // Task handle
    );

    // Start the FreeRTOS scheduler
    vTaskStartScheduler(); 
    return 0; // Should never reach here
}

#include <stdio.h>
#include "FreeRTOS.h"
#include "task.h"
#include "benchmark.h"

void benchmark_task(void *pvParameters)
{
    int initial_batch_size = 100;
    int batch_step = 100;
    const int num_runs = 1000;

    FILE *fp = fopen("benchmark_results.csv", "w");
    if (fp == NULL) {
        printf("Failed to open benchmark_results.csv for writing\n");
        vTaskDelete(NULL);
        return;
    }
    fprintf(fp, "run_number,ticks,ms,batch_size\n");

    for (int run = 0; run < num_runs; ++run)
    {
        int batch_size = initial_batch_size + run * batch_step;

        TickType_t start_ticks = xTaskGetTickCount();

        for (int i = 0; i < batch_size; i++) {
            process_data();
        }
        TickType_t end_ticks = xTaskGetTickCount();
        TickType_t duration_ticks = end_ticks - start_ticks;
        fprintf(fp, "%d,%u,%lu,%d\n", run + 1, (unsigned int)duration_ticks,
                (duration_ticks * 1000) / configTICK_RATE_HZ, batch_size);
        fflush(fp);
    }

    fclose(fp);

    printf("Benchmark complete, results saved to benchmark_results.csv\n");

    vTaskDelete(NULL);
}


void vAssertCalled(unsigned long ulLine, const char *const pcFileName)
{
    taskENTER_CRITICAL();
    {
        printf("[ASSERT] %s:%lu\n", pcFileName, ulLine);
        fflush(stdout);
    }
    taskEXIT_CRITICAL();
    exit(-1);
}

void vApplicationIdleHook(void)
{
    // Idle hook; unused in this benchmark
}
