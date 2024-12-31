#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <regex.h>
#include "bluetooth.h"
#include "constants.h"
#include "utils.h"

void execute_command(const char *command, char *output, size_t size) {
    FILE *pipe = popen(command, "r");
    if (!pipe) {
        fprintf(stderr, "Error executing command: %s\n", command);
        return;
    }

    char buffer[BUFFER_SIZE];
    while (fgets(buffer, sizeof(buffer), pipe) != NULL) {
        strncat(output, buffer, size - strlen(output) - 1);
    }

    pclose(pipe);
}

void scan_bluetooth_devices(char devices[MAX_DEVICES][2][256], int *device_count) {
    char output[BUFFER_SIZE * 10] = {0};

    execute_command(BLUETOOTH_CTL " " SCAN_COMMAND, output, sizeof(output));
    display_scanning_animation(30);

    execute_command(BLUETOOTH_CTL " " STOP_SCAN_COMMAND, output, sizeof(output));

    regex_t regex;
    regmatch_t matches[3];

    if (regcomp(&regex, DEVICE_REGEX_PATTERN, REG_EXTENDED) != 0) {
        fprintf(stderr, "Error compiling regex.\n");
        return;
    }

    const char *pos = output;
    *device_count = 0;
    int unknown_counter = 1;

    while (regexec(&regex, pos, 3, matches, 0) == 0) {
        if (*device_count >= MAX_DEVICES) break;

        int len = matches[1].rm_eo - matches[1].rm_so;
        strncpy(devices[*device_count][0], pos + matches[1].rm_so, len);
        devices[*device_count][0][len] = '\0';

        len = matches[2].rm_eo - matches[2].rm_so;
        if (len > 0) {
            strncpy(devices[*device_count][1], pos + matches[2].rm_so, len);
            devices[*device_count][1][len] = '\0';
        } else {
            snprintf(devices[*device_count][1], sizeof(devices[*device_count][1]), "%s%d", DEVICE_NAME_UNKNOWN_PREFIX,
                     unknown_counter++);
        }

        (*device_count)++;
        pos += matches[0].rm_eo;
    }

    regfree(&regex);
}

void connect_to_device(const char *device_name) {
    char devices[MAX_DEVICES][2][256] = {0};
    int device_count = 0;

    scan_bluetooth_devices(devices, &device_count);

    if (device_count == 0) {
        printf("No Bluetooth devices found.\n");
        return;
    }

    char mac_address[256] = {0};
    for (int i = 0; i < device_count; i++) {
        if (strcmp(devices[i][1], device_name) == 0) {
            strncpy(mac_address, devices[i][0], sizeof(mac_address) - 1);
            break;
        }
    }

    if (strlen(mac_address) == 0) {
        printf("Device with name \"%s\" not found.\n", device_name);
        return;
    }

    char command[512];
    snprintf(command, sizeof(command), BLUETOOTH_CTL " " CONNECT_COMMAND " %s", mac_address);
    printf("Attempting to connect to \"%s\" (%s)...\n", device_name, mac_address);

    char output[BUFFER_SIZE] = {0};
    execute_command(command, output, sizeof(output));
    if (strstr(output, "Connection successful")) {
        printf("Successfully connected to \"%s\".\n", device_name);
    } else {
        printf("Failed to connect to \"%s\".\n", device_name);
    }
}

void check_connection_status() {
    char output[BUFFER_SIZE] = {0};
    execute_command(BLUETOOTH_CTL " info", output, sizeof(output));
    if (strlen(output) == 0) {
        printf("No active Bluetooth connection.\n");
    } else {
        printf("Connection status:\n%s\n", output);
    }
}
