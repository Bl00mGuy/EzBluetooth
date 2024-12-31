#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include "bluetooth.h"
#include "constants.h"

void print_ascii_banner() {
    printf("--------------------------------------------------------\n");
    printf("▗▄▄▄▖▗▄▄▄▄▖▗▄▄▖ ▗▖   ▗▖ ▗▖▗▄▄▄▖▗▄▄▄▖ ▗▄▖  ▗▄▖ ▗▄▄▄▖▗▖ ▗▖\n");
    printf("▐▌      ▗▞▘▐▌ ▐▌▐▌   ▐▌ ▐▌▐▌     █  ▐▌ ▐▌▐▌ ▐▌  █  ▐▌ ▐▌\n");
    printf("▐▛▀▀▘ ▗▞▘  ▐▛▀▚▖▐▌   ▐▌ ▐▌▐▛▀▀▘  █  ▐▌ ▐▌▐▌ ▐▌  █  ▐▛▀▜▌\n");
    printf("▐▙▄▄▖▐▙▄▄▄▖▐▙▄▞▘▐▙▄▄▖▝▚▄▞▘▐▙▄▄▖  █  ▝▚▄▞▘▝▚▄▞▘  █  ▐▌ ▐▌\n");
    printf("                 EzBluetooth Utility                    \n");
    printf("--------------------------------------------------------\n");
}

void print_help() {
    printf("EzBluetooth Utility - Help\n");
    printf("Commands:\n");
    printf("  help            - Display this help message\n");
    printf("  scan            - Scan for available Bluetooth devices\n");
    printf("  connect NAME    - Connect to a Bluetooth device by its name\n");
    printf("  status          - Check the connection status\n");
    printf("  exit            - Exit the utility\n");
}

void print_version() {
    printf(VERSION_FILE, VERSION);
}

int main(int argc, char *argv[]) {
    if (argc > 1 && (strcmp(argv[1], "--help") == 0 || strcmp(argv[1], "-h") == 0)) {
        print_help();
        return 0;
    }

    if (argc > 1 && (strcmp(argv[1], "--version") == 0 || strcmp(argv[1], "-v") == 0)) {
        print_version();
        return 0;
    }

    print_ascii_banner();

    while (true) {
        printf("\n#EzBluetooth: ");
        char command[256];
        fgets(command, sizeof(command), stdin);
        command[strcspn(command, "\n")] = '\0';

        if (strcmp(command, "scan") == 0) {
            char devices[MAX_DEVICES][2][256] = {0};
            int device_count = 0;
            scan_bluetooth_devices(devices, &device_count);
            if (device_count == 0) {
                printf("No Bluetooth devices found.\n");
            } else {
                printf("Discovered devices:\n");
                for (int i = 0; i < device_count; i++) {
                    printf("%d. Name: %s, MAC: %s\n", i + 1, devices[i][1], devices[i][0]);
                }
            }
        } else if (strncmp(command, "connect ", 8) == 0) {
            connect_to_device(command + 8);
        } else if (strcmp(command, "status") == 0) {
            check_connection_status();
        } else if (strcmp(command, "exit") == 0) {
            printf("Exiting EzBluetooth. Goodbye!\n");
            break;
        } else if (strcmp(command, "help") == 0) {
            print_help();
        } else {
            printf("Invalid command. Type 'exit' to quit or 'help' for assistance.\n");
        }
    }

    return 0;
}
