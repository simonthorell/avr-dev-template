#!/bin/bash

# Define the serial device and baud rate
SERIAL_DEVICE="/dev/ttyUSB0" # Default Linux device path; adjust for macOS or provide as input
BAUD_RATE=9600

# Function to configure and read from the serial device
read_serial() {
    if [[ "$OSTYPE" == "linux-gnu"* ]]; then
        stty -F $SERIAL_DEVICE $BAUD_RATE cs8 -cstopb -parenb -ixon -ixoff -crtscts
        cat $SERIAL_DEVICE
    elif [[ "$OSTYPE" == "darwin"* ]]; then
        # macOS specific command
        stty -f $SERIAL_DEVICE $BAUD_RATE cs8 -cstopb -parenb -ixon -ixoff -crtscts
        cat $SERIAL_DEVICE
    elif [[ "$OSTYPE" == "msys"* ]] || [[ "$OSTYPE" == "win32"* ]]; then
        # Windows or Windows Subsystem for Linux (WSL)
        echo "Windows or WSL detected. Adjusting commands accordingly."
        # TODO: Add Windows/WSL specific commands here...
    else
        echo "Unknown OS. Exiting."
        exit 1
    fi
}

# Adjust SERIAL_DEVICE for macOS, as an example
if [[ "$OSTYPE" == "darwin"* ]]; then
    SERIAL_DEVICE="/dev/cu.usbserial-110"
fi

# TODO: Adjust SERIAL_DEVICE for Windows or WSL here...

# Call the function to read from the serial device
read_serial

# TODO! Capture user input and send it to the serial device

# For testing on MAC: screen /dev/cu.usbserial-110 9600
# Close with 'CTRL + a' then ':' then type 'quit' and press 'Enter

# Capture user input and send it to the serial device (not working properly!)
while IFS= read -r line; do
    echo "$line" > $SERIAL_DEVICE
done