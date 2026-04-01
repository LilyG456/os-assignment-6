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

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define CLICK_INTERVAL_MS 300.0


int main(int argc, char *argv[]) {
    // TODO
}
