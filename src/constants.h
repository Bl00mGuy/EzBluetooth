#ifndef CONSTANTS_H
#define CONSTANTS_H

#define MAX_DEVICES 256
#define BUFFER_SIZE 1024
#define SCAN_SLEEP_DURATION 30
#define DEVICE_NAME_UNKNOWN_PREFIX "Unknown"

#define BLUETOOTH_CTL "bluetoothctl"
#define SCAN_COMMAND "scan on"
#define STOP_SCAN_COMMAND "scan off"
#define CONNECT_COMMAND "connect"

#define DEVICE_REGEX_PATTERN "\\[NEW\\] Device ([[:xdigit:]:]+) (.+)"

#define VERSION "1.0.0"
#define VERSION_FILE "EzBluetooth Utility version %s\n"

#endif // CONSTANTS_H
