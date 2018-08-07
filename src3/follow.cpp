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

class ImgProc{
private:
    //ROSノードのハンドル
    ros::NodeHandle nh_;
    image_transport::ImageTransport img_t_;
    image_transport::Subscriber img_sub_;
    image_transport::Publisher img_pub_r;
    image_transport::Publisher img_pub_b;
    ros::Subscriber chatter_sub;
    ros::Publisher chatter_pub;
    std_msgs::String current_command;

    const char *cstr = "next2";
    std::string str = std::string(cstr);
    int flag = 0;

    void cb_check(const std_msgs::String::ConstPtr& msg)
    {
        current_command = *msg;
        if(current_command.data == str)
        {
            flag = 1;
        }
    }
/*
    void check_flag()
    {
        while(true){
            if(flag == 1){ 
                break;
            }
        }
    }
*/
public:
   ImgProc():img_t_(nh_){
        img_sub_ = img_t_.subscribe("/usb_cam/image_raw", 1, &ImgProc::subf_img, this);
        printf("A\n");
        img_pub_r = img_t_.advertise("/img_r", 1);
        img_pub_b = img_t_.advertise("/img_b", 1);
        chatter_pub = nh_.advertise<std_msgs::String>("command", 1000);
        printf("A\n");
	chatter_sub = nh_.subscribe("goal_sign", 1, &ImgProc::cb_check, this);
        printf("A\n");
    }

    void subf_img(const sensor_msgs::ImageConstPtr& img){
      if(flag == 1){

        printf("B\n");
        cv::Mat mat_img_r;
        cv::Mat mat_img_b;

        cv_bridge::CvImagePtr cv_img_ptr_r;
        cv_bridge::CvImagePtr cv_img_ptr_b;

        try{
            cv_img_ptr_r = cv_bridge::toCvCopy(img, sensor_msgs::image_encodings::TYPE_8UC3);
            cv_img_ptr_b = cv_bridge::toCvCopy(img, sensor_msgs::image_encodings::TYPE_8UC3);
         }
        catch(cv_bridge::Exception& e){
            ROS_ERROR("cv_bridge exception: %s", e.what());
            return;
          }

        mat_img_r = cv_img_ptr_r->image;
        mat_img_b = cv_img_ptr_b->image;

        cv::cvtColor(mat_img_r, mat_img_r, CV_RGB2HSV);            
        cv::cvtColor(mat_img_b, mat_img_b, CV_RGB2HSV);            

        std_msgs::String msg;
        int red_pixel_l = 0;
        int red_pixel_r = 0;
        
        for(int y = 0; y < 480; y++){
            for(int x = 0; x < 640; x++){
                if(mat_img_r.at<cv::Vec3b>(y, x)[0] < 25 || 105 < mat_img_r.at<cv::Vec3b>(y, x)[0])
                {
                    if(x < 320)
                    { 
                    	red_pixel_l ++;        
                    }                    
                    else
                    { 
                     	red_pixel_r ++;   
                    }
                }
            }
        }
        cv::cvtColor(mat_img_r, mat_img_r, CV_HSV2BGR);
        cv::cvtColor(mat_img_b, mat_img_b, CV_HSV2BGR);

        cv_img_ptr_r->image = mat_img_r;
        cv_img_ptr_b->image = mat_img_b;

        img_pub_r.publish(cv_img_ptr_r->toImageMsg());
        img_pub_b.publish(cv_img_ptr_b->toImageMsg());

        std::stringstream ss;

	printf("red_r=%d",red_pixel_r);
	printf("red_l=%d\n",red_pixel_l);
        if( red_pixel_r < 20000 && red_pixel_l < 20000) ss << "Stop";
	else if(red_pixel_l + red_pixel_r > 250000) ss << "Go";         
	else if(red_pixel_l > 50000) ss << "Left";
        else if(red_pixel_r > 50000) ss << "Right";
	else ss << "Stop";
        msg.data = ss.str();
        chatter_pub.publish(msg);
      }
    }
};

int main (int argc, char** argv){
    ros::init (argc, argv, "follow");

    ImgProc ImgProc;

    while(ros::ok()){
        ros::spinOnce(); 
    }
}
