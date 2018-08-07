#!/usr/bin/python

import rospy, actionlib
from move_base_msgs.msg import *

from move_base_msgs.msg import MoveBaseAction, MoveBaseGoal
from std_msgs.msg import String

class send_goal():
  def __init__(self):
    self.client = actionlib.SimpleActionClient('move_base', MoveBaseAction)
    self.pub = rospy.Publisher('goal_sign', String, queue_size=1)
    self.sub = rospy.Subscriber('chatter' , String, self.callback)

    self.goal = MoveBaseGoal()
    self.goal.target_pose.header.stamp = rospy.Time.now()
    self.goal.target_pose.header.frame_id = "/map"
    self.goal.target_pose.pose.position.x = 1.69677269459;
    self.goal.target_pose.pose.position.y = -0.640728414059;
    self.goal.target_pose.pose.orientation.w = 1
    print self.goal

    self.flag = 0

  def callback(self,data):
    if data.data == str('next'):
      self.flag = 1

  def check_flag(self):
    while True:
      if self.flag == 1:
        break

  def do_action(self):
    self.client.send_goal(self.goal)
    self.success = self.client.wait_for_result(rospy.Duration(30))

  def check_result(self):
    if not self.success:
      self.client.cancel_goal()
      rospy.loginfo("could not find goal in 60 sec.")
    else:
      state = self.client.get_state()
#      if state == GoalStatus.SUCCEEDED:
      if state == 3:
        rospy.loginfo("yattaze.")
        self.pub.publish("next2")
      elif state == 0:
        rospy.loginfo("stay")
        self.pub.publish("stay")
      else:
        rospy.loginfo("else")
        self.pub.publish("else")

if __name__ == '__main__':

  rospy.init_node('send_goal',anonymous=True)

  try:
    sd = send_goal()
    rospy.loginfo('A')
    sd.check_flag()
    rospy.loginfo('A')
    sd.do_action()
    rospy.loginfo('A')
    sd.check_result()
    rospy.loginfo('A')
  except rospy.ROSInterruptException: pass
