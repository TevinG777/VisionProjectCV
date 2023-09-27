import cv2
import numpy as np
import asyncio
import websockets
import json
import time

# Define WebSocket server details
websocket_server_address = "ws://10.20.1.93:8765"  # Replace with your WebSocket server address

async def send_data_to_websocket(data):
    async with websockets.connect(websocket_server_address) as websocket:
        await websocket.send(json.dumps(data))

async def process_camera_data():
    last_send = 0  # Initialize the last_send variable
    # Create a VideoCapture object
    url = "10.20.1.40:81/stream"
    cap = cv2.VideoCapture(url)

    # Error handling
    if not cap.isOpened():
        print("Error: Could not open camera.")
        return

    while True:
        ret, frame = cap.read()

        if not ret:
            print("Error: Could not read frame.")
            break

        squares = isSquare(frame)

        if len(squares) == 0:
            current_time = time.time() - last_send
            if current_time >= 1:
                print("0,0")
                await send_data_to_websocket({"x": 0, "area": 0})
                last_send = time.time()

        cv2.drawContours(frame, squares, -1, (225, 0, 0), 3)
        cv2.imshow("Frame", frame)

        if cv2.waitKey(1) & 0xFF == ord('q'):
            break

    cap.release()
    cv2.destroyAllWindows()

def isSquare(frame):
    global last_send

    frame = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)
    
    lower_color = np.array([0, 74, 55])
    upper_color = np.array([11, 255, 255])

    kernel = np.ones((5, 5), np.uint8)

    mask = cv2.inRange(frame, lower_color, upper_color)
    mask_eroded = cv2.erode(mask, kernel, iterations=2)
    mask_eroded_dilated = cv2.dilate(mask_eroded, None, iterations=8)

    contours, _ = cv2.findContours(mask_eroded_dilated, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)

    squares = []
    for cnt in contours:
        epsilon = 0.1 * cv2.arcLength(cnt, True)
        approx = cv2.approxPolyDP(cnt, epsilon, True)
        minArea = 100

        if len(approx) == 4 and cv2.contourArea(cnt) > minArea:
            squares.append(cnt)
            area = cv2.contourArea(cnt)
            rect = cv2.boundingRect(cnt)
            x, y, w, h = rect

            current_time = time.time() - last_send

            if current_time >= 1:
                print(str(x) + "," + str(area))
                asyncio.run(send_data_to_websocket({x, area}))
                last_send = time.time()

    return squares

if __name__ == "__main__":
    # Initialize the asyncio event loop
    loop = asyncio.get_event_loop()

    # Start the camera data processing as a task
    camera_data_task = loop.create_task(process_camera_data())

    # Run the event loop
    try:
        loop.run_until_complete(camera_data_task)
    except KeyboardInterrupt:
        pass
