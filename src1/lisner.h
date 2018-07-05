#include "ros/ros.h"
#include "std_msgs/String.h"

class Lisner
{
  public:
//    Lisner(ros::NodeHandle& nh);
//    ~Lisner();
//    void chatterCallback(const std_msgs::String::ConstPtr& msg);
    void startLisner();

  private:
    ros::NodeHandle n;
    ros::Subscriber sub;

//  void chatterCallback(const std_msgs::String::ConstPtr& msg);
};

void chatterCallback(const std_msgs::String::ConstPtr& msg);
