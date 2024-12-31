#include <unistd.h>
#include <stdio.h>
#include "constants.h"
#include "utils.h"

void display_scanning_animation(int total_steps) {
    const char *animation[] = {"/", "-", "\\", "|"};
    int i = 0;
    for (int step = 0; step < total_steps; step++) {
        printf("\rScanning for devices %s", animation[i]);
        fflush(stdout);
        sleep(SCAN_SLEEP_DURATION);
        i = (i + 1) % 4;
    }
    printf("\rScanning for devices...\n");
}
