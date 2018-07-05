#!/usr/bin/env python
# -*- coding: utf-8 -*-
# license removed for brevity
import rospy
from std_msgs.msg import String
#import std_msgs.msg
from test_pkg.msg import Num
import roslib
import subprocess

def talker():
    pub2 = rospy.Publisher('chatter', String, queue_size=10)
    pub = rospy.Publisher('test_msg', Num, queue_size=10)
    rospy.init_node('talker_py', anonymous=True)
    r = rospy.Rate(1) # 10hz

    subprocess.Popen(["rosrun", "test_pkg", "talker"])
    rospy.sleep(10)
    subprocess.call(["rosnode", "kill", "talker"])
    print("test")

    node_name = rospy.get_namespace()
    rospy.loginfo(node_name)
    pkg_dir = roslib.packages.get_pkg_dir("test_pkg")
    rospy.loginfo(pkg_dir)

    #pkg_file = roslib.packages.find_path("test_pkg")
    #rospy.loginfo(pkg_file)

    #number = test_pkg.msg.Num()
    #number.num = 10

    while not rospy.is_shutdown():
        str = "hello world %s"%rospy.get_time()
        int = 1
        start = rospy.get_time()
#        rospy.loginfo(str)
        rospy.logwarn("start : %s"%(start))

        pub.publish(10)
        pub2.publish(str)

        r.sleep()
        #rospy.sleep(3)
        rospy.logfatal("end : %s"%rospy.get_time())
        rospy.logerr("time : %s"%(rospy.get_time() - start))
        rospy.logdebug("====================================")

if __name__ == '__main__':
    try:
        talker()
    except rospy.ROSInterruptException: pass
