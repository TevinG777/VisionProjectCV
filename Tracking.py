import cv2
import numpy as np
import imutils


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
        
        if len(approx) == 4 and cv2.contourArea(cnt) > minArea:
            greenSquares.append(cnt)
            print("The area of the square is: " + cv2.contourArea(cnt))
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

