#!/bin/bash

# Define the serial port to which the microcontroller is connected.
SERIAL_PORT=/dev/cu.usbserial-110

# Define the microcontroller type (e.g., ATmega328P).
MCU=atmega328p

# Define the programmer type (e.g., Arduino as ISP).
PROGRAMMER=arduino

# Define the path to the hex file you want to flash.
HEX_FILE=../build/avr-firmware.hex

# Flash the microcontroller using avrdude.
avrdude -p $MCU -c $PROGRAMMER -P $SERIAL_PORT -U flash:w:$HEX_FILE:i

# Check if avrdude succeeded.
if [ $? -eq 0 ]; then
    echo "Flashing successful!"
else
    echo "Flashing failed."
fi