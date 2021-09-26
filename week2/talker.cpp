#include <ros/ros.h>
#include <std_msgs/String.h>

int main(int argc, char* argv[]){
    ros::init(argc, argv, "talker");
    ros::NodeHandle nh;
    ros::Publisher chatterPublisher = 
        nh.advertise<std_msgs::String>("chatter", 1);
    ros::Rate loopRate(10);

    unsigned int count = 0;
    while (ros::ok()){
        std_msgs::String message;
        message.data = "hello world " + std::to_string(count);
        ROS_INFO_STREAM(message.data);
        chatterPublisher.publish(message);
        ros::spinOnce();
        loopRate.sleep();
        count++;
    }
    return 0;
}