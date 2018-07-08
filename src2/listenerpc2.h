#include "ros/ros.h"
#include "std_msgs/String.h"
#include "sensor_msgs/PointCloud2.h"
#include "sensor_msgs/PointField.h"

#include <string.h>

#include <pcl_conversions/pcl_conversions.h>
#include <pcl/point_cloud.h>
#include <pcl/point_types.h>
#include <pcl/sample_consensus/model_types.h>
#include <pcl/sample_consensus/method_types.h>
#include <pcl/segmentation/sac_segmentation.h>
#include <pcl_ros/point_cloud.h>

#include <iostream>
#include <pcl/io/pcd_io.h>

//ros::NodeHandle n;

class Listenerpc2
{
  public:
    void startListenerpc2();

    void listenerpc2Callback(const sensor_msgs::PointCloud2ConstPtr& msg);

  private:
    ros::NodeHandle n;
    ros::Subscriber sub;
    ros::Publisher pub = n.advertise<sensor_msgs::PointCloud2>("laser_pc_cloud", 1);
};

//void listenerpc2Callback(const sensor_msgs::PointCloud2& msg);
