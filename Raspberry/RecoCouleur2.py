#Programme qui se base sur OpenCV et qui a pour but de détecter la position de l'objet

import cv2
import numpy as np
import commandeSerieRobot45
color=100
color_info=(0, 0, 255)
cap=cv2.VideoCapture(0)
robot = commandeSerieRobot45.connexionRobot()
robot.ouvrir_port()


while True:
    radius = 0 
    if cv2.waitKey(33) == ord('a'):
        if color >0:
            color -=1
    if cv2.waitKey(33) == ord('z'):
        color +=1
    lo=np.array([color-5, 100, 50])
    hi=np.array([color+5, 255,255])
    ret, frame=cap.read()
    image=cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)
    mask=cv2.inRange(image, lo, hi)
    mask=cv2.erode(mask, None, iterations=2)
    mask=cv2.dilate(mask, None, iterations=2)
    elements=cv2.findContours(mask, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)[-2]
    cv2.putText(mask, "color =" + str(color),(30,60),cv2.FONT_HERSHEY_DUPLEX, 1, (255,255,255), 1, cv2.LINE_AA)
    if len(elements) > 0:
        c=max(elements, key=cv2.contourArea)
        ((x, y), radius)=cv2.minEnclosingCircle(c)
        if radius>30:
            cv2.putText(mask, "x= "+ str(x), (30,30), cv2.FONT_HERSHEY_DUPLEX, 1, (255,255,255), 1, cv2.LINE_AA)
    cv2.imshow('Mask', mask)
    if cv2.waitKey(1)&0xFF==ord('q'):
        break
    try:
        if 20 < radius < 1000:
            if  x < 235:
                print("tourne à gauche")
                mvt = "L"
              
            elif x > 405:
                print("tourne à droite")
                mvt= "R"
                 
            else:
                print("tout droit")
                mvt = "F"
        else:
            mvt ="S"
            print("Stop")
    except:
        mvt = "S"
    robot.commande(mvt)
    
cap.release()
cv2.destroyAllWindows()
robot.fermer_port()
