#include "listenerpc2.h"
#include <vector>

//typedef pcl::PointCloud<pcl::PointXYZ> PointCloud;

//void listenerpc2Callback(const sensor_msgs::PointCloud2& msg)
void Listenerpc2::listenerpc2Callback(const sensor_msgs::PointCloud2ConstPtr& msg)
{
  sensor_msgs::PointCloud2 pc2;
  pcl::PointCloud<pcl::PointXYZ> cloud;
  pc2 = *msg;
  pcl::fromROSMsg (*msg, cloud);

  printf ("Cloud: width = %d, height = %d\n", cloud.width, cloud.height);
//  BOOST_FOREACH (const pcl::PointXYZ& pt, cloud.points)
//  printf ("\t(%f, %f, %f)\n", pt.x, pt.y, pt.z);

  cloud.is_dense = false;
  cloud.points.resize (cloud.width * cloud.height);

//  pcl::io::savePCDFileASCII ("test_pcd.pcd", cloud);
  std::cerr << " size: " << cloud.points.size() << " cloud points" << std::endl;
  std::cerr << " size: " << pc2.data.size() << " data points " << std::endl;

//  printf ("size is %d\n",cloud.points.size());
//  for (size_t i = 0; i < cloud.points.size (); ++i)
//    std::cerr << "    " << cloud.points[i].x << " " << cloud.points[i].y << " " << cloud.points[i].z << std::endl;
  std::cerr << "    " << cloud.points[(cloud.height/2)*cloud.width + cloud.width/2].x << " " << cloud.points[(cloud.height/2)*cloud.width + cloud.width/2].y << " " << cloud.points[(cloud.height/2)*cloud.width + cloud.width/2].z << std::endl;

//std::cout << typeid(cloud.points[(cloud.height/2)*cloud.width + cloud.width/2].z).name() << std::endl;

//  printf("yea1\n");
//  pc2.height = 480;
//  pc2.width = 640;
//  pc2.fields[0].offset = 0;
//  pc2.fields[1].offset = 4;
//  pc2.fields[2].offset = 8;
//  pc2.is_bigendian = false;
//  pc2.point_step = 16;
//  pc2.row_step = 10240;
//  pc2.is_dense = false;
//  printf("yea2\n");
//  std::vector<pcl::uint8_t> data;
/*
  for (size_t i = 0; i < cloud.points.size()*16; i=i+16){

    if((cloud.height/2)*16*cloud.width <= i && i <= (cloud.height/2)*16*cloud.width + 16*cloud.width - 1){
//      pc2.data.push_back(cloud.points[i].x);
//      pc2.data.push_back(cloud.points[i].y);
//      pc2.data.push_back(cloud.points[i].z);
        pc2.data[i] =  cloud.points[i].x;
        pc2.data[i + 4] =  cloud.points[i].y;
        pc2.data[i + 8] =  cloud.points[i].z;
    }

//    else{
//      pc2.data.push_back(0);
//    }
  }
*/
/*
  for (size_t i = 0 ; i < cloud.width*cloud.height; i=i+1){
    if((cloud.height/2)*cloud.width > i && i >= (cloud.height/2)*cloud.width + cloud.width){
      pc2.data[i*16] =  0;
      pc2.data[i*16 + 4] =  0;
      pc2.data[i*16 + 8] =  0;
    }
  }
*/
/*
  for (size_t i = 0 ; i < cloud.width; i=i+1){
    pc2.data[(cloud.height/2)*16*cloud.width + i*16] =  cloud.points[i].x;
    pc2.data[(cloud.height/2)*16*cloud.width + i*16 + 4] =  cloud.points[i].y;
    pc2.data[(cloud.height/2)*16*cloud.width + i*16 + 8] =  cloud.points[i].z;
  }
*/
/*
  for (size_t i = (cloud.height/2)*16*cloud.width; i < (cloud.height/2)*16*cloud.width + 16*cloud.width ; i=i+16){
    pc2.data[i] =  cloud.points[i].x;
    pc2.data[i + 4] =  cloud.points[i].y;
    pc2.data[i + 8] =  cloud.points[i].z;
  }
*/
//  pub = n.advertise<sensor_msgs::PointCloud2>("laser_pc_cloud", 1);

  ROS_INFO("============================================");
  ROS_INFO("height: %d", pc2.height);
  ROS_INFO("width: %d", pc2.width);
  ROS_INFO("row_step: [%d]", pc2.row_step);
  ROS_INFO("point_step: [%d]", pc2.point_step);
  ROS_INFO("x:OFFSET = %d", pc2.fields[0].offset);
  ROS_INFO("y:OFFSET = %d", pc2.fields[1].offset);
  ROS_INFO("z:OFFSET = %d", pc2.fields[2].offset);

//  pub.publish(pc2);

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

//  float X = 0.0;
//  float Y = 0.0;
//  float Z = 0.0;

//  memcpy(&X, &msg.data[arrayPosX], sizeof(float));
//  memcpy(&Y, &msg.data[arrayPosY], sizeof(float));
//  memcpy(&Z, &msg.data[arrayPosZ], sizeof(float));

//  p.x = X;
//  p.y = Y;
//  p.z = Z;

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
  sub = n.subscribe<sensor_msgs::PointCloud2>("/camera/depth/points", 1000, &Listenerpc2::listenerpc2Callback, this);
//  sub = n.subscribe("/camera/depth/points", 1000, listenerpc2Callback);
}
