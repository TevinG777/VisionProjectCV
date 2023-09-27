import asyncio
import websockets
import random
import time
import json

async def send_custom_data(websocket, path):
    while True:
        # Generate two random integer values (you can replace this with your own data)
        data1 = random.randint(0, 500)
        data2 = random.randint(0, 11000)
        
        # Send the data to the client as a JSON object
        message = {"data1": data1, "data2": data2}
        await websocket.send(json.dumps(message))

        # Wait for a second before sending the next update
        await asyncio.sleep(3)

# Start the WebSocket server on a specific host and port
start_server = websockets.serve(send_custom_data, "10.20.1.93", 8765)

# Run the server
asyncio.get_event_loop().run_until_complete(start_server)
asyncio.get_event_loop().run_forever()

print("HIIIII")
