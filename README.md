# AVR Development Container

## List USB-devices in container

Inside the vs-code terminal run:
```bash
lsusb
```

## Configuring the USB Port

In case you would like to flash to or monitor your microcontroller direc

To ensure proper communication with the AVR microcontroller, you need to specify the correct USB port in both the development container configuration and the CMake project settings. Follow the steps below to configure the USB port on your system.

## Step 1: Update the `.devcontainer.json` File

1. Open the `.devcontainer.json` file located in your project root.
2. Find and uncomment the `runArgs` section.
3. Replace the existing USB port reference with the correct port. For example, if your device is connected to `/dev/ttyUSB1`, change it to:

    ```json
    "runArgs": [
        "--device=/dev/ttyUSB1:/dev/ttyUSB1"
    ],
    ```

*Note: When you add the runArgs command, the container will not start if specified device is not connected.*

## Step 2: Update the `CMakeLists.txt` File

1. Open the `CMakeLists.txt` file also located in your project root.
2. On the line that sets the `USB_PORT` variable, change `/dev/ttyUSB0` to the correct port, e.g., `/dev/ttyUSB1`, to match your system configuration:

    ```cmake
    set(USB_PORT /dev/ttyUSB1) # Serial port for programming
    ```

## Finding Your USB Device [optional]

If unsure of your device's port, use these terminal/command prompt commands:

- **Windows**: Run `mode` and look for `COM#`.
- **macOS**: Run `ls /dev/tty.*` or `ls /dev/cu.*` and look for `/dev/tty.usbserial#`.
- **Linux**: Use `dmesg | grep tty` or `ls /dev/ttyUSB*` / `ls /dev/ttyACM*`.
