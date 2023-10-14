import asyncio
import websockets
import json
import serial.tools.list_ports

async def client():
    # Get list of ports to interact with Arduino
    ports = list(serial.tools.list_ports.comports())
    arduino_port = None

    # Find the port that matches the specified HWID
    for p in ports:
        if "USB VID:PID=2341:0043 SER=7503330333535130D091 LOCATION=1-1:1.0" in p.hwid:
            arduino_port = p.device
            break
    
    # Error if the Arduino is not found
    if not arduino_port:
        print("Arduino not found in the available ports.")
        return

    # Initialize and open the serial port with arduino baudrate
    ser = serial.Serial(arduino_port, baudrate=115200)
    message_counter = 0  # Counter to keep track of messages received
    try:
        # Connect to the WebSocket server
        async with websockets.connect("ws://10.20.1.93:8765") as websocket:
            while True:
                # Receive data from the WebSocket server
                message = await websocket.recv()
                message_counter +=1

                # Only print every 50th message
                if message_counter % 50 == 0:
                    try:
                        # Parse the JSON data
                        data = json.loads(message)
                        data1 = data.get("data1")
                        data2 = data.get("data2")
                        print(f"Received data1: {data1}, data2: {data2}")

                        # Validate and send data to the Arduino
                        if isinstance(data1, int) and isinstance(data2, int):
                            ser.write(f"{data1},{data2}\n".encode('utf-8'))
                        else:
                            print("Invalid data received from WebSocket.")
                        #error handling
                    except json.JSONDecodeError as e:
                        print(f"Error decoding JSON: {e}")
                    except Exception as e:
                        print(f"Error processing data: {e}")
                    
    # Print if websocket connection is closed
    except websockets.exceptions.ConnectionClosedError as e:
        print(f"WebSocket connection closed: {e}")
    except serial.SerialException as e:
        print(f"Serial port error: {e}")
    finally:
        # Close the serial port
        ser.close()

# Run the client
if __name__ == "__main__":
    asyncio.get_event_loop().run_until_complete(client())
