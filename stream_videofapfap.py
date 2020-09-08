import time
import cv2 
from flask import Flask, render_template, Response
faceCascade = cv2.CascadeClassifier('D:\Code\Flask-streaming-Pedestrians-detection-using-python-opencv--master\opencv\data\haarcascades\haarcascade_frontalface_default.xml')

app = Flask(__name__)
sub = cv2.createBackgroundSubtractorMOG2()

@app.route('/')
def index():
	return render_template('index.html')


def gen():
	cap = cv2.VideoCapture(0)
	cap.set(4,480) #SET_WIDTH
	cap.set(3,320) #SET_HEIGHT
	counter = 0
	while True:
		ret, img = cap.read()
		gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
		faces = faceCascade.detectMultiScale(
			gray,
			scaleFactor = 1.2,
			minNeighbors = 5,
			minSize = (20, 20)
			)
		if counter > 10:
			img_name = "screen_cap.jpg"
			cv2.imwrite(img_name, img)
			print("Face Detection OFF")
			number = "1"
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
				frame = cv2.imencode('.jpg', img)[1].tobytes()
				yield(b'--frame\r\n'b'Content-Type: img/jpeg\r\n\r\n' + frame + b'\r\n')
				k = cv2.waitKey(30)
				if k == 27: #PRESS ESC TO QUIT
					break

@app.route('/video_feed')
def video_feed():
    return Response(gen(),
                    mimetype='multipart/x-mixed-replace; boundary=frame')

    

