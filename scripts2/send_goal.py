#!/usr/bin/python

import rospy, actionlib
from move_base_msgs.msg import *

from move_base_msgs.msg import MoveBaseAction, MoveBaseGoal
from std_msgs.msg import String

flag = 0

def callback(data):
    global flag
    flag = 0
    if data.data == str('next'):
        flag = 1
#        rospy.loginfo('B')

if __name__ == '__main__':
  try:
    rospy.init_node('send_goal',anonymous=True)
    client = actionlib.SimpleActionClient('move_base', MoveBaseAction)
    pub = rospy.Publisher('goal_sign', String, queue_size=1)
    while True:
        sub = rospy.Subscriber('chatter' , String, callback)
        rospy.loginfo('A')

        if flag ==1:
            break

#    client.wait_for_server()
    rospy.loginfo('C')
    goal = MoveBaseGoal()
    goal.target_pose.header.stamp = rospy.Time.now()
    goal.target_pose.header.frame_id = "/map"
    goal.target_pose.pose.position.x = -1.35790061951;
    goal.target_pose.pose.position.y = -1.8763718605;
    goal.target_pose.pose.orientation.w = 1
    print goal
    client.send_goal(goal)
#    print client.wait_for_result()

    success = client.wait_for_result(rospy.Duration(60))
    
    if not success:
      client.cancel_goal()
      rospy.loginfo("could not find goal in 60 sec.")
    else:
      state = client.get_state()
#      if state == GoalStatus.SUCCEEDED:
      if state == 3:
        rospy.loginfo("yattaze.")
        pub.publish("next2")
      elif state == 0:
        rospy.loginfo("aaaaaaaa")
        pub.publish("stay")
      else:
        rospy.loginfo("bbbbbbbb")
        pub.publish("else")

  except rospy.ROSInterruptException: pass
