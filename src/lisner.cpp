#include "lisner.h"
/*
Lisner::Lisner();
{
  
}
*/
void chatterCallback(const std_msgs::String::ConstPtr& msg)
{
  ROS_INFO("I heard: [%s]", msg->data.c_str());
}

void Lisner::startLisner()
{
  sub = n.subscribe("chatter", 1000, chatterCallback);
}
