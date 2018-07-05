#include "ros/ros.h"
#include "std_msgs/String.h"
#include "sensor_msgs/PointCloud2.h"
#include "sensor_msgs/PointField.h"

#include <string.h>

class Listenerpc2
{
  public:
    void startListenerpc2();

  private:
    ros::NodeHandle n;
    ros::Subscriber sub;
};

void listenerpc2Callback(const sensor_msgs::PointCloud2& msg);
