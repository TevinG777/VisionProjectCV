import serial
import time

# Define the serial port and baud rate (make sure it matches the Arduino settings)
ser = serial.Serial('/dev/ttyAMA0', 9600)  # Use '/dev/ttyAMA0' for the Raspberry Pi's GPIO pins

try:
    while True:
        command = input("Enter a command ('1' to turn on LED, '0' to turn it off, or 'exit' to quit): ")

        if command == '1' or command == '0':
            ser.write(command.encode())  # Send the command to the Arduino
        elif command == 'exit':
            break
        else:
            print("Invalid input. Enter '1' or '0' to control the LED.")

finally:
    ser.close()