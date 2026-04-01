/*
 * cpu_hog.c
 *
 * CPU-bound infinite loop.
 *
 */

 #include <stdio.h>

int main() {
    long x = 1;
    while (1)
    {
        x = x * 2;
    }
    return 0;  
}
