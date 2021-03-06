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
//    image_transport::ImageTransport img_t_;
    image_transport::Subscriber img_sub_;
    image_transport::Publisher img_pub_r;
    image_transport::Publisher img_pub_b;
//    ros::Publisher left_pub;
 //   ros::Publisher right_pub;
 //   ros::Publisher center_pub;
    ros::Publisher chatter_pub;

public:
    //コンストラクタ
   ImgProc():img_t_(nh_){
        img_sub_ = img_t_.subscribe("/usb_cam/image_raw", 1, &ImgProc::subf_img, this);
        img_pub_r = img_t_.advertise("/img_r", 1);
        img_pub_b = img_t_.advertise("/img_b", 1);
//        left_pub = nh_.advertise<std_msgs::String>("/left",1);
//        right_pub = nh_.advertise<std_msgs::String>("/right",1);
//        center_pub = nh_.advertise<std_msgs::String>("/center",1);
        chatter_pub = nh_.advertise<std_msgs::String>("command", 1000);
    }

    //デストラクタ
    ~ImgProc(){
    }


    void subf_img(const sensor_msgs::ImageConstPtr& img){
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
//        cv::cvtColor(mat_img, mat_img, CV_BGR2RGB);

        cv::cvtColor(mat_img_r, mat_img_r, CV_RGB2HSV);            
        cv::cvtColor(mat_img_b, mat_img_b, CV_RGB2HSV);            

        std_msgs::String msg;
        int red_pixel_l = 0;
        int red_pixel_r = 0;
        int red_pixel_c = 0;
        int blue_pixel = 0;

        for(int y = 0; y < 480; y++){
            for(int x = 0; x < 640; x++){
                
                if(mat_img_r.at<cv::Vec3b>(y, x)[0] < 25 ||
                  102< mat_img_r.at<cv::Vec3b>(y, x)[0]){

                  if(x<213){
                    red_pixel_l ++;
                  }else if(x<426){
                    red_pixel_c ++;
                  }else{
                    red_pixel_r ++;
                  }

//                }else{                 
//                  mat_img_r.at<cv::Vec3b>(y, x)[0] = 0;
//                  mat_img_r.at<cv::Vec3b>(y, x)[1] = 0;
//                  mat_img_r.at<cv::Vec3b>(y, x)[2] = 0;
                }

//                if(50 < mat_img_b.at<cv::Vec3b>(y, x)[0] && 
//                  mat_img_b.at<cv::Vec3b>(y, x)[0] < 150){
//                  blue_pixel ++;
//                }else{
//                  mat_img_b.at<cv::Vec3b>(y, x)[0] = 0;
//                  mat_img_b.at<cv::Vec3b>(y, x)[1] = 0;
//                  mat_img_b.at<cv::Vec3b>(y, x)[2] = 0;
//                }


//                mat_img.at<cv::Vec3b>(y, x)[0] -= 0;
//                if(mat_img.at<cv::Vec3b>(y, x)[0] < 0){
//                    mat_img.at<cv::Vec3b>(y, x)[0]  = 0;
//                    }
                }
          }
//        ROS_INFO("red = %d, blue = %d\n", red_pixel, blue_pixel);
        cv::cvtColor(mat_img_r, mat_img_r, CV_HSV2BGR);
        cv::cvtColor(mat_img_b, mat_img_b, CV_HSV2BGR);

//        cv::cvtColor(mat_img_r, mat_img_r, CV_BGR2RGB);
//        cv::cvtColor(mat_img_b, mat_img_b, CV_BGR2RGB);

        cv_img_ptr_r->image = mat_img_r;
        cv_img_ptr_b->image = mat_img_b;

        img_pub_r.publish(cv_img_ptr_r->toImageMsg());
        img_pub_b.publish(cv_img_ptr_b->toImageMsg());

        std::stringstream ss;

        printf("r = %d, c = %d, l = %d\n",red_pixel_r,red_pixel_c,red_pixel_l);
        if(red_pixel_l < red_pixel_r && red_pixel_c < red_pixel_r){
          ss << "right";
        }else if(red_pixel_l < red_pixel_c && red_pixel_r < red_pixel_c){
          ss << "center";
        }else{
          ss << "left";
        }

        msg.data = ss.str();
        chatter_pub.publish(msg);
//        left_pub.publish(red_pixel_l);    
//        right_pub.publish(red_pixel_r);
//        center_pub.publish(red_pixel_c);
    }
};

int main (int argc, char** argv){
    ros::init (argc, argv, "img_proc");

    ImgProc ImgProc;

    while(ros::ok()){
        ros::spinOnce(); 
    }
}
