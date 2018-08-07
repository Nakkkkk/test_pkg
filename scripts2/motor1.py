#!/usr/bin/env python
# -*- coding: utf-8 -*-
import rospy
import time
from geometry_msgs.msg import Twist
from darknet_ros_msgs.msg import BoundingBoxes
###########################################
#変数宣言
###########################################

#variable function
Xmin = 0
Xmax = 0
Ymin = 0
Ymax = 0 
detection = ''

Vd = 0
Vt = 0

#const function
W0 = 640.0 
theta_total = 60
    
a = -0.8816
b = 476.4436
c = 0.002
d = 0.05

Vd = 0
Vt = 0

###########################################
#コールバック
###########################################
def callback(data):
	global detection 
	for cell in data.bounding_boxes :
		detection = ''
		if cell.Class == "person" :		
			global Xmin 
			global Xmax 
			global Ymin 
			global Ymax
			Xmin = 0
			Xmax = 0
			Ymin = 0
			Ymax = 0 
			detection = cell.Class			
			Xmin = cell.xmin
			Xmax = cell.xmax
			Ymin = cell.ymin
			Ymax = cell.ymax
			break
###########################################
#購読，配信
###########################################
def call():
	rospy.init_node('follow_me', anonymous=True)
	pub = rospy.Publisher('cmd_vel', Twist , queue_size=10)
	sub = rospy.Subscriber("darknet_ros/bounding_boxes", BoundingBoxes , callback)
###########################################
#計算,結果
###########################################
def caluculate(): 
	global Vd
	global Vt
	global theta_total
	global Xmax 
	global Ymin 
	global Ymax
	global W0
	global detection
	Vd = Vt = 0
	if  (detection == 'person') :
		hw = Xmax-Xmin
		W2 = (Xmax+Xmin)/2-(W0/2)
		theta = (W2/W0)*theta_total
		distance = (hw-b)/a
		Vd = distance*c
		Vt = theta*d
		print('-------------')
		print('hw=',hw)
		print('Vd=',Vd)
		print('Vt=',Vt)
		print('class=',detection)
###########################################
# main program for follow me
###########################################		
def follow_me():
	global Vd
	global Vt
	global detection 
	rate = rospy.Rate(10) #hz
	print('Vd=',Vd)
	print('Vt=',Vt)
	shake = 0
	while not rospy.is_shutdown():
		shake = shake + 1 
		call()
		caluculate()
		vr = Twist()
		if (detection == 'person') :			
			vr.linear.x = Vd
			vr.angular.z = -Vt
		else :
			print('shaking=',shake)
			vr.linear.x = 0
			if(shake/100 < 1) :
			    vr.angular.z = -0.2
			else :
			    vr.angular.z = 0.2

		if(shake == 300) :
			shake =0
				
		pub.publish(vr) 
		rate.sleep()
	rospy.spin()

if __name__ == '__main__':
	try:
		call()
	except rospy.ROSInterruptException:
		pass

	try:
		caluculate()
	except rospy.ROSInterruptException:
		pass
    
	try:
		follow_me()
	except rospy.ROSInterruptException:
		pass
