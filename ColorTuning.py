import cv2
import numpy as np

def nothing(x):
    pass

# Create a VideoCapture object for the camera
url = "http://10.20.1.40:81/stream"
cap = cv2.VideoCapture(url)

# Error handling
if not cap.isOpened():
    print("Error: Could not open camera.")
    exit()

# Create a window
cv2.namedWindow('image')

# Create trackbars for color change
# Hue is from 0-179 for OpenCV
cv2.createTrackbar('HMin', 'image', 0, 179, nothing)
cv2.createTrackbar('SMin', 'image', 0, 255, nothing)
cv2.createTrackbar('VMin', 'image', 0, 255, nothing)
cv2.createTrackbar('HMax', 'image', 0, 179, nothing)
cv2.createTrackbar('SMax', 'image', 0, 255, nothing)
cv2.createTrackbar('VMax', 'image', 0, 255, nothing)

# Set default value for Max HSV trackbars
cv2.setTrackbarPos('HMax', 'image', 179)
cv2.setTrackbarPos('SMax', 'image', 255)
cv2.setTrackbarPos('VMax', 'image', 255)

# Initialize HSV min/max values
hMin = sMin = vMin = hMax = sMax = vMax = 0
phMin = psMin = pvMin = phMax = psMax = pvMax = 0

while True:
    # Capture a frame from the camera
    ret, frame = cap.read()

    # Error handling
    if not ret:
        print("Error: Could not read frame.")
        break

    # Get current positions of all trackbars
    hMin = cv2.getTrackbarPos('HMin', 'image')
    sMin = cv2.getTrackbarPos('SMin', 'image')
    vMin = cv2.getTrackbarPos('VMin', 'image')
    hMax = cv2.getTrackbarPos('HMax', 'image')
    sMax = cv2.getTrackbarPos('SMax', 'image')
    vMax = cv2.getTrackbarPos('VMax', 'image')

    # Set minimum and maximum HSV values to create the mask
    lower = np.array([hMin, sMin, vMin])
    upper = np.array([hMax, sMax, vMax])

    # Convert to HSV format
    hsv = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)

    # Create a mask based on the HSV range
    mask = cv2.inRange(hsv, lower, upper)

    # Apply the mask to the original frame to keep it in color
    result = cv2.bitwise_and(frame, frame, mask=mask)

    # Print if there is a change in HSV value
    if((phMin != hMin) or (psMin != sMin) or (pvMin != vMin) or (phMax != hMax) or (psMax != sMax) or (pvMax != vMax)):
        print("(hMin = %d, sMin = %d, vMin = %d), (hMax = %d, sMax = %d, vMax = %d)" % (hMin, sMin, vMin, hMax, sMax, vMax))
        phMin = hMin
        psMin = sMin
        pvMin = vMin
        phMax = hMax
        psMax = sMax
        pvMax = vMax

    # Display the result image with color
    cv2.imshow('image', result)

    # Exit program when 'q' is pressed
    if cv2.waitKey(10) & 0xFF == ord('q'):
        break

# Release the camera and close the window
cap.release()
cv2.destroyAllWindows()
