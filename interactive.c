/*
 * interactive.c
 *
 * Sleeps for CLICK_INTERVAL_MS between "clicks" and reports:
 *   - elapsed time since click (ms, 3 decimals)
 *   - instantaneous jitter for THIS click (ms, 3 decimals)
 *
 * jitter_ms = actual_interval_ms - CLICK_INTERVAL_MS
 *
 * Usage:
 *   ./interactive <runtime_seconds>
 */

#define _POSIX_C_SOURCE 199309L

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define CLICK_INTERVAL_MS 300.0

double convert_to_milliseconds(struct timespec *start, struct timespec *end) {
    return (end->tv_sec - start->tv_sec) * 1000.0 + (end->tv_nsec - start->tv_nsec) / 1e6;
}

int main(int argc, char *argv[]) {
    if(argc != 2) {
        fprintf(stderr, "Usage: %s <runtime_seconds>\n", argv[0]);
        return 1;
    }

    int run_seconds = atoi(argv[1]);

    struct timespec start_time, prev_time, curr_time;
    clock_gettime(CLOCK_MONOTONIC, &start_time);
    prev_time = start_time;

    double total_time_elapsed = 0.0;

    while(total_time_elapsed < run_seconds) {
        usleep((int)(CLICK_INTERVAL_MS * 1000));

        clock_gettime(CLOCK_MONOTONIC, &curr_time);

        // time since last cliock
        double elapsed_milliseconds = convert_to_milliseconds(&prev_time, &curr_time);

        double jitter_ms = elapsed_milliseconds - CLICK_INTERVAL_MS;

        printf("[click] elapsed=%.3f ms  jitter=%.3f ms\n",
               elapsed_milliseconds, jitter_ms);

        // update previous click
        prev_time = curr_time;

        // total runtime 
        total_time_elapsed = convert_to_milliseconds(&start_time, &curr_time) / 1000.0;
    }

    return 0;
}

