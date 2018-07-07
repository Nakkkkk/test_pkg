#include "listenerpc2.h"
#include <vector>

//typedef pcl::PointCloud<pcl::PointXYZ> PointCloud;

void listenerpc2Callback(const sensor_msgs::PointCloud2ConstPtr& msg)
{
  pcl::PointCloud<pcl::PointXYZ> cloud;
  pcl::fromROSMsg (*msg, cloud);

  printf ("Cloud: width = %d, height = %d\n", cloud.width, cloud.height);
  BOOST_FOREACH (const pcl::PointXYZ& pt, cloud.points)
  printf ("\t(%f, %f, %f)\n", pt.x, pt.y, pt.z);

/*
  // get width and height of 2D point cloud data
  int width = msg.width;
  int height = msg.height;

  // Convert from u (column / width), v (row / height) to position in array
  // where X,Y,Z data starts

//  int arrayPosition = v*msg.row_step + u*msg.point_step;
  int arrayPosition = (height-240)*msg.row_step + (width-320)*msg.point_step;

  // compute position in array where x,y,z data start
  int arrayPosX = arrayPosition + msg.fields[0].offset; // X has an offset of 0
  int arrayPosY = arrayPosition + msg.fields[1].offset; // Y has an offset of 4
  int arrayPosZ = arrayPosition + msg.fields[2].offset; // Z has an offset of 8

  float X = 0.0;
  float Y = 0.0;
  float Z = 0.0;

  memcpy(&X, &msg.data[arrayPosX], sizeof(float));
  memcpy(&Y, &msg.data[arrayPosY], sizeof(float));
  memcpy(&Z, &msg.data[arrayPosZ], sizeof(float));

  p.x = X;
  p.y = Y;
  p.z = Z;

  ROS_INFO("============================================");
  ROS_INFO("height: %d", msg.height);
  ROS_INFO("width: %d", msg.width);
  ROS_INFO("row_step: [%d]", msg.row_step);
  ROS_INFO("point_step: [%d]", msg.point_step);
  ROS_INFO("X: [%d]", msg.data[arrayPosX]);
  ROS_INFO("Y: [%u]", msg.data[arrayPosY]);
  ROS_INFO("Z: [%u]", msg.data[arrayPosZ]);
  ROS_INFO("x:OFFSET = %d", msg.fields[0].offset);
  ROS_INFO("y:OFFSET = %d", msg.fields[1].offset);
  ROS_INFO("z:OFFSET = %d", msg.fields[2].offset);
*/
/*
  std::vector<float> cloud_points_z;
  float p[3] = read_points(msg, field_names = ("x", "y", "z"), skip_nans=false);
  cloud_point_z.push_back()
*/
}

void Listenerpc2::startListenerpc2()
{
  sub = n.subscribe<sensor_msgs::PointCloud2>("/camera/depth/points", 1000, listenerpc2Callback);
}
