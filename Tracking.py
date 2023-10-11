import cv2
import numpy as np
import time
import websockets
import asyncio
import json



global last_send
last_send = 0

async def isSquare(frame, websocket):
    #initilize variable to store the last time a record was sent
    global last_send
    
    #convert frame from camera to HSV color space
    frame = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)
    
    #define threshold for edge detection for multimeter
    lower_color = np.array([0, 74, 55])
    upper_color = np.array([11, 255, 255])
    #Hue: We dont care what value because we are looking for white
    #Saturation: How color color
    #Value: How bright the color is
    
    #define kernel for erosion
    kernel = np.ones((5, 5), np.uint8)

    #define mask for color
    mask = cv2.inRange(frame, lower_color, upper_color)
    mask_eroded = cv2 . erode ( mask , kernel , iterations = 2)
    mask_eroded_dilated = cv2 . dilate ( mask_eroded , None , iterations = 8)

    #create list of contour points 
    contours, _ = cv2.findContours(mask_eroded_dilated, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)
    
    #filter points to only include squares
    squares = []
    for cnt in contours:
        #define epsilon for approximation, determines the accuracy of the approximation, and if it is closed
        epsilon = 0.1*cv2.arcLength(cnt, True)
        
        approx = cv2.approxPolyDP(cnt, epsilon, True)
        minArea = 100
        
        #if the contour is a square, and the area is greater than the minimum area, add it to the list
        if len(approx) == 4 and cv2.contourArea(cnt) > minArea:
            squares.append(cnt)
            area = cv2.contourArea(cnt)
            
            #define a rectangle and get x value
            rect = cv2.boundingRect(cnt)
            x, y, w, h = rect
                  
            #calclate the time elaspsed since last record was sent
            current_time = time.time() - last_send
            
            if current_time >= 1:
                #print send message to Arudino
                print(str(x) + "," + str(area))
                await send_toPort(x, area, websocket)
                
                #update last send time
                last_send = time.time()
        
                  
            
      
    return squares


async def main(websocket):
    global last_send
    # Create a VideoCapture object
    #url = "10.20.1.40:81/stream"
    cap = cv2.VideoCapture(0)

    # Error handling
    if not cap.isOpened():
        print("Error: Could not open camera.")
        exit()

    
    while True:
        
        # Capture a frame from the camera
        ret, frame = cap.read()

        # Can not read frame
        if not ret:
            print("Error: Could not read frame.")
            break

        #display from with squares
        squares = isSquare(frame)
    
        #check if squares array is empty, and if it is send 0,0 to Arduino over serial
        if len(squares) == 0:
            current_time = time.time() - last_send
            if current_time >= 1:
                print("0,0")
                await send_toPort(0,0, websocket)
                last_send = time.time()
    
        cv2.drawContours(frame, squares, -1, (255, 0, 0), 3)  # Change 225 to 255

        cv2.imshow("Frame", frame)

        # Exit program when q is pressed
        if cv2.waitKey(1) & 0xFF == ord('q'):
            exit()

    # Release the camera and close the window
    cap.release()
    cv2.destroyAllWindows()

async def send_toPort(x, area, websocket):
    message = {"x": x, "area": area}
    await websocket.send(json.dumps(message))

if __name__ == "__main__":
    # Run the server
    start_server = websockets.serve(main, "10.20.1.93", 8765)
    asyncio.get_event_loop().run_until_complete(start_server)
    asyncio.get_event_loop().run_forever()
    main()