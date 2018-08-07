//C++
#include <stdio.h>
#include <vector>

//ROS
#include <ros/ros.h>

#include <sensor_msgs/image_encodings.h>
#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>
#include <std_msgs/String.h>

//OpenCV
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace std;

class ImgProc
{
private:
    //ROSノードのハンドル
    ros::NodeHandle nh_;

    image_transport::ImageTransport img_t_;
    image_transport::Subscriber img_sub_;

    ros::Publisher chatter_pub;

    std_msgs::String msg;

    int redPixelFast = 0;
public:
    ImgProc():img_t_(nh_)
    {
        img_sub_ = img_t_.subscribe("/usb_cam/image_raw", 1, &ImgProc::subf_img, this);
        chatter_pub = nh_.advertise<std_msgs::String>("chatter", 1000);
    }
    void subf_img(const sensor_msgs::ImageConstPtr& img){
        cv::Mat mat_img_r;
        cv_bridge::CvImagePtr cv_img_ptr_r;
        try{ cv_img_ptr_r = cv_bridge::toCvCopy(img, sensor_msgs::image_encodings::TYPE_8UC3); }
        catch(cv_bridge::Exception& e){ ROS_ERROR("cv_bridge exception: %s", e.what()); return; }
        mat_img_r = cv_img_ptr_r->image;
        cv::cvtColor(mat_img_r, mat_img_r, CV_RGB2HSV);       
        int red_pixel = 0;
        for(int y = 0; y < 480; y++)
        {
            for(int x = 0; x < 640; x++)
            {                
                if(mat_img_r.at<cv::Vec3b>(y, x)[0] < 25 || 102< mat_img_r.at<cv::Vec3b>(y, x)[0]) red_pixel++;
            }
        }
        if(redPixelFast == 0) redPixelFast = red_pixel; 
        if(red_pixel < redPixelFast / 2)
        {
            std::stringstream ss;
            ss << "next";
            msg.data = ss.str();
            chatter_pub.publish(msg);
        }
    }
};

int main (int argc, char** argv){
    ros::init (argc, argv, "img_proc");

    ImgProc ImgProc;

    while(ros::ok()){
        ros::spinOnce(); 
    }
}
