import serial.tools.list_ports

#Get list of ports
ports = list(serial.tools.list_ports.comports())

#initialize serial port
ser = serial.Serial()

#select port that has Arduino in description
for p in ports:
    if "Arduino" in p.description:
        ser.port = p.device
        
#define baud rate   
ser.baudrate = 9600

#open serial port
ser.open()

while True:
    command = input("Enter command(on/off): ")
    ser.write(command.encode('utf-8'))
    if command == "exit":
        break
