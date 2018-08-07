#!/usr/bin/env python

import rospy
from geometry_msgs.msg import Twist
from std_msgs.msg import String

import sys, select, termios, tty
command = "Stop"
pub = rospy.Publisher('cmd_vel', Twist, queue_size=100);
def callback(data):
    global command
    global pub
    rospy.loginfo(rospy.get_caller_id() + "I heard %s", data.data)
    command = data.data
    cmd = Twist()
    cmd.linear.x = move[command]()[0]
    cmd.linear.y = move[command]()[1]
    cmd.angular.z = move[command]()[2]
    pub.publish(cmd)
     
def listener():
    rospy.Subscriber("command", String, callback)
    rospy.spin()

move = {
  'Stop' : lambda : (0,0,0),
  'Go' : lambda : (1,0,0),
  'Left' : lambda : (0,0,1),
  'Right' : lambda : (0,0,-1),
  }

if __name__== '__main__':

    rospy.init_node('send_velocity', anonymous=True)
    settings = termios.tcgetattr(sys.stdin)

    try:
        listener()
    except :
        print "ERROR"
