#ifndef BLUETOOTH_H
#define BLUETOOTH_H
#include "constants.h"

void scan_bluetooth_devices(char devices[MAX_DEVICES][2][256], int *device_count);

void connect_to_device(const char *device_name);

void check_connection_status();

#endif // BLUETOOTH_H
