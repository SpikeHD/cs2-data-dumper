import numpy as np
import cv2
import pyautogui
import sys
import time

# The first argument (after the script name) is the file to save the label data to
timestamp = time.time()
label_file = './dump/labels/' + str(timestamp) + '.txt'
image_file = './dump/images/' + str(timestamp) + '.png'

# Each argument after is data to push to the label file, so gather all args and make them into one var
data = " ".join(sys.argv[1:]).replace('\\n ', '\n').replace('\\n', '\n')

# take screenshot using pyautogui
image = pyautogui.screenshot()

# since the pyautogui takes as a 
# PIL(pillow) and in RGB we need to 
# convert it to numpy array and BGR 
# so we can write it to the disk
image = cv2.cvtColor(np.array(image),
                     cv2.COLOR_RGB2BGR)

# writing it to the disk using opencv
cv2.imwrite(image_file, image)

# Create the label file
with open(label_file, 'w') as f:
    f.write(data)