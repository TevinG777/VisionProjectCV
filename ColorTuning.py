import cv2
import numpy as np

def nothing(x):
    pass

# Create a VideoCapture object for the camera
cap = cv2.VideoCapture(0)

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

    # Set minimum and maximum HSV values to display
    lower = np.array([hMin, sMin, vMin])
    upper = np.array([hMax, sMax, vMax])

    kernel = np.ones((5, 5), np.uint8)

    # Convert to HSV format and apply color threshold
    hsv = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)
    mask = cv2.inRange(hsv, lower, upper)
    mask_eroded = cv2 . erode ( mask , kernel , iterations = 2)
    mask_eroded_dilated = cv2 . dilate ( mask_eroded , None , iterations = 8)

    # Print if there is a change in HSV value
    if((phMin != hMin) or (psMin != sMin) or (pvMin != vMin) or (phMax != hMax) or (psMax != sMax) or (pvMax != vMax)):
        print("(hMin = %d, sMin = %d, vMin = %d), (hMax = %d, sMax = %d, vMax = %d)" % (hMin, sMin, vMin, hMax, sMax, vMax))
        phMin = hMin
        psMin = sMin
        pvMin = vMin
        phMax = hMax
        psMax = sMax
        pvMax = vMax

    # Display result image
    cv2.imshow('image', mask_eroded_dilated)

    # Exit program when 'q' is pressed
    if cv2.waitKey(10) & 0xFF == ord('q'):
        break

# Release the camera and close the window
cap.release()
cv2.destroyAllWindows()
