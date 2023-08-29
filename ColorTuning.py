import cv2
import numpy as np

# Create a callback function for mouse events
def get_color(event, x, y, flags, param):
    if event == cv2.EVENT_LBUTTONDOWN:
        # Get the color at the clicked point in HSV
        hsv_color = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)
        color = hsv_color[y, x]
        print("HSV Color:", color)

# Create a VideoCapture object
cap = cv2.VideoCapture(0)

# Error handling
if not cap.isOpened():
    print("Error: Could not open camera.")
    exit()

# Create a window to display the camera feed
cv2.namedWindow("Camera Feed")

# Set up a mouse callback function to get color values
cv2.setMouseCallback("Camera Feed", get_color)

while True:
    # Capture a frame from the camera
    ret, frame = cap.read()

    # Can not read frame
    if not ret:
        print("Error: Could not read frame.")
        break

    # Display the camera feed
    cv2.imshow("Camera Feed", frame)

    # Exit program when q is pressed
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

# Release the camera and close the window
cap.release()
cv2.destroyAllWindows()
