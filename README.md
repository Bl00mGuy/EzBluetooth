# EzBluetooth Utility

***EzBluetooth*** is a CLI utility for scanning and managing Bluetooth devices on Linux using `bluetoothctl`. It offers
a simple interface for discovering devices, connecting to them, and checking the connection status.

## Features

- **Scan for Bluetooth devices**: Discover available Bluetooth devices in the vicinity.
- **Connect to a device**: Connect to a Bluetooth device by its name.
- **Check connection status**: Check the current Bluetooth connection status.
- **Cross-platform**: Designed to work on Linux systems with Bluetooth support.

## Prerequisites

Before using EzBluetooth, ensure that:

- Your system has Bluetooth hardware and drivers installed.
- `bluetoothctl` is available on your system (it’s part of the `bluez` package).
- You have root or sudo privileges to manage Bluetooth services.

## Installation

### Clone the Repository

```
git clone https://github.com/Bl00mGuy/ezbluetooth.git
cd ezbluetooth
```

### Build the Project

Run the following gcc command to compile the project:

```
gcc -o EzBluetooth src/main.c src/bluetooth.c src/utils.c -lbluetooth -Wall -Wextra -std=c17
```

### Running the Program

After compilation, run the program using:

```
./EzBluetooth
```

## Usage

### Running the Utility

Run the utility by executing the following command in your terminal:

```
./ezbluetooth
```

Once the program starts, you can enter the following commands:

### Commands

- **`scan`**: Scan for available Bluetooth devices in the vicinity.

  Example:
  ```
  scan
  ```

- **`connect DEVICE_NAME`**: Connect to a Bluetooth device by its name. Replace `DEVICE_NAME` with the name of the
  device.

  Example:
  ```
  connect MyBluetoothSpeaker
  ```

- **`status`**: Check the current connection status of your Bluetooth devices.

  Example:
  ```
  status
  ```

- **`exit`**: Exit the EzBluetooth utility.

  Example:
  ```
  exit
  ```

### Help & Version

- `-h, --help` : Show a list of available commands and options.
- `-v, --version` : Show the version of the EzBluetooth utility.

### Example Output

```
$ ./ezbluetooth
--------------------------------------------------------
▗▄▄▄▖▗▄▄▄▄▖▗▄▄▖ ▗▖   ▗▖ ▗▖▗▄▄▄▖▗▄▄▄▖ ▗▄▖  ▗▄▖ ▗▄▄▄▖▗▖ ▗▖
▐▌      ▗▞▘▐▌ ▐▌▐▌   ▐▌ ▐▌▐▌     █  ▐▌ ▐▌▐▌ ▐▌  █  ▐▌ ▐▌
▐▛▀▀▘ ▗▞▘  ▐▛▀▚▖▐▌   ▐▌ ▐▌▐▛▀▀▘  █  ▐▌ ▐▌▐▌ ▐▌  █  ▐▛▀▜▌
▐▙▄▄▖▐▙▄▄▄▖▐▙▄▞▘▐▙▄▄▖▝▚▄▞▘▐▙▄▄▖  █  ▝▚▄▞▘▝▚▄▞▘  █  ▐▌ ▐▌
                 EzBluetooth Utility                    
--------------------------------------------------------

#EzBluetooth: scan

Scanning for devices...
Discovered devices:
1. Name: MyDevice, MAC: 00:11:22:33:44:55
2. Name: BluetoothSpeaker, MAC: 66:77:88:99:00:11
```

## Troubleshooting

- If you encounter errors like "Failed to stop discovery", make sure you have appropriate permissions to manage
  Bluetooth services, or try running the program with `sudo`.
- If no devices are found, ensure that your Bluetooth adapter is enabled and in range of discoverable devices.

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.
