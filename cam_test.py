import numpy as np
import cv2
import time
import serial
faceCascade = cv2.CascadeClassifier('/home/pi/opencv/data/lbpcascades/lbpcascade_frontalface.xml')
cap = cv2.VideoCapture(0)
cap.set(4,480) #SET_WIDTH
cap.set(3,320) #SET_HEIGHT
ser = serial.Serial('/dev/ttyUSB0', 115200, timeout=1)
ser.flush()
counter = 0
while True:
	ret, img = cap.read()
	gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
	faces = faceCascade.detectMultiScale(
		gray,
		scaleFactor=1.2,
		minNeighbors=5,
		minSize=(300, 300)
	)
	if counter > 10:
		img_name = "screen_cap.jpg"
		cv2.imwrite(img_name, img)
		print("Face Detection OFF")
		number = "1"
		ser.write(number.encode())
		time.sleep(3)
		counter = 0
	else:
		for (x,y,w,h) in faces:
			cv2.rectangle(img,(x,y),(x+w,y+h),(255,0,0),2)
			print(x)
			print(y)
			print(w)
			print(h)
			print("EOF_________________")
			x = 0
			y = 0
			w = 0
			h = 0
			counter = counter + 1
	cv2.imshow('video',img)
	k = cv2.waitKey(30) & 0xff
	if k == 27: #PRESS ESC TO QUIT
		break
cap.release()
cv2.destroyAllWindows()

