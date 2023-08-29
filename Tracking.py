import cv2
import numpy as np
import serial.tools.list_ports
import time

#Get list of ports to interact with arduino
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



def isSquare(frame):
    #convert frame from camera to HSV color space
    frame = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)
    
    #define threshold for edge detection green
    lower_green = np.array([80, 140, 128])
    upper_green = np.array([90, 255, 211])
    
    #define mask for pink
    maskPink = cv2.inRange(frame, lower_green, upper_green)
    
    #create list of contour points 
    contours, _ = cv2.findContours(maskPink, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)
    
    #filter points to only include squares
    greenSquares = []
    for cnt in contours:
        #define epsilon for approximation, determines the accuracy of the approximation, and if it is closed
        epsilon = 0.1*cv2.arcLength(cnt, True)
        
        approx = cv2.approxPolyDP(cnt, epsilon, True)
        minArea = 100
        
        #if the contour is a square, and the area is greater than the minimum area, add it to the list
        if len(approx) == 4 and cv2.contourArea(cnt) > minArea:
            greenSquares.append(cnt)
            area = cv2.contourArea(cnt)
            
            
            # Check if it's been 1 second since the last send
            current_time = time.time()
            if current_time - last_send_time >= 1.0:
                print("The area of the square is: " + str(area))
                # Write area to the serial port as a float
                ser.write(str(area).encode('utf-8'))
                last_send_time = current_time  # Update the last send time
            
            
    return greenSquares
    
# Create a VideoCapture object
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
    cv2.drawContours(frame, squares, -1, (0, 255, 0), 3)
    cv2.imshow("Frame", frame)
    
    
    
    
    # Exit program when q is pressed
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

# Release the camera and close the window
cap.release()
cv2.destroyAllWindows()

