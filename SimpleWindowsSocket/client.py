import asyncio
import websockets
import json
import serial.tools.list_ports

async def client():
    # Define the serial port and baud rate (make sure it matches the Arduino settings)
    ser = serial.Serial('/dev/ttyAMA0', 9600)  # Use '/dev/ttyAMA0' for the Raspberry Pi's GPIO pins
    message_counter = 0  # Counter to keep track of messages received
    try:
        # Connect to the WebSocket server
        async with websockets.connect("ws://10.20.1.93:8765") as websocket:
            while True:
                # Receive data from the WebSocket server
                message = await websocket.recv()
                message_counter +=1

                # Only print every 50th message
                if message_counter % 10 == 0:
                    try:
                        # Parse the JSON data
                        data = json.loads(message)
                        data1 = data.get("data1")
                        data2 = data.get("data2")
                        

                        # Validate and send data to the Arduino
                        if isinstance(data1, int) and isinstance(data2, int):
                            print(f"Sending.... Received data1: {data1}, data2: {data2}")
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
