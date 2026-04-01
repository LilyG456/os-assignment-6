/*
 * sched_test.c
 *
 * Run:
 *   ./sched_test <num-hogs> <runtime-seconds>
 *
 * Required behavior:
 *   1) fork+exec CPU hogs first
 *   2) fork+exec interactive last (passing runtime-seconds)
 *   3) waitpid() for interactive process
 *   4) kill hogs
 *   5) reap remaining children
 */

#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <num_hogs> <runtime_seconds>\n", argv[0]);
        return 1;
    }

    // TODO

    return 0;
}