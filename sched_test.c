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

    int num_hogs = atoi(argv[1]); // number of cpu hogs
    int runtime_seconds = atoi(argv[2]); // how long to run before killing the hogs

    if(num_hogs < 0 || runtime_seconds <= 0) {
        fprintf(stderr, "Invalid arguments: the parameters num_hogs and runtime_seconds must be non-negative integers.\n");
        return 1;
    }

    pid_t hog_pids[num_hogs];
    
    //cpu hog processes
    for(int i = 0; i < num_hogs; i++) {
        pid_t pid = fork(); // fork for each cpu hog
        if (pid < 0) {
            perror("fork failed");
            return 1;
        } else if (pid == 0) {
            execl("./cpu_hog", "./cpu_hog", NULL); // cpu hog
            perror("exec failed");
            return 1;
        } else {
            hog_pids[i] = pid;
        }
    }

    //interactive process
    pid_t interactive_pid = fork(); // fork for interactive process
    if (interactive_pid < 0) {
        perror("fork failed");
        return 1;
    } else if (interactive_pid == 0) {
        char runtime_str[10];
        snprintf(runtime_str, sizeof(runtime_str), "%d", runtime_seconds);
        execl("./interactive", "./interactive", runtime_str, NULL); // interactive process
        perror("exec failed");
        return 1;
    }

    //wait for interactive process to finish
    waitpid(interactive_pid, NULL, 0);

    // kill all of the hogs
    for(int i = 0; i < num_hogs; i++) {
        kill(hog_pids[i], SIGKILL);
    }

    // reap all remaining hogs
    while (wait(NULL) > 0); // wait for all child processes to finish

    return 0;
}

