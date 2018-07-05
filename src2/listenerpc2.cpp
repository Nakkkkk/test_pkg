#include "listenerpc2.h"

void listenerpc2Callback(const sensor_msgs::PointCloud2& msg)
{
  // get width and height of 2D point cloud data
  int width = msg.width;
  int height = msg.height;

  // Convert from u (column / width), v (row/height) to position in array
  // where X,Y,Z data starts

//  int arrayPosition = v*msg.row_step + u*msg.point_step;
  int arrayPosition = msg.row_step + msg.point_step;

  // compute position in array where x,y,z data start
  int arrayPosX = arrayPosition + msg.fields[0].offset; // X has an offset of 0
  int arrayPosY = arrayPosition + msg.fields[1].offset; // Y has an offset of 4
  int arrayPosZ = arrayPosition + msg.fields[2].offset; // Z has an offset of 8
/*
  float X = 0.0;
  float Y = 0.0;
  float Z = 0.0;

  memcpy(&X, &msg.data[arrayPosX], sizeof(float));
  memcpy(&Y, &msg.data[arrayPosY], sizeof(float));
  memcpy(&Z, &msg.data[arrayPosZ], sizeof(float));

  p.x = X;
  p.y = Y;
  p.z = Z;
*/
  ROS_INFO("============================================");
  ROS_INFO("X: [%u]", msg.data[arrayPosX]);
  ROS_INFO("Y: [%u]", msg.data[arrayPosY]);
  ROS_INFO("Z: [%u]", msg.data[arrayPosZ]);

}

void Listenerpc2::startListenerpc2()
{
  sub = n.subscribe("/camera/depth/points", 1000, listenerpc2Callback);
}
