import asyncio
import websockets
import json

async def client():
    async with websockets.connect("ws://10.20.1.93:8765") as websocket:
        while True:
            message = await websocket.recv()
            data = json.loads(message)
            data1 = data.get("data1")
            data2 = data.get("data2")
            print(f"Received data1: {data1}, data2: {data2}")

asyncio.get_event_loop().run_until_complete(client())
