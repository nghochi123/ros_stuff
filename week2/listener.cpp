#include <ros/ros.h>
#include <std_msgs/String.h>

void chatterCallback(const std_msgs::String& msg) {
    ROS_INFO_STREAM("I heard: [" << msg.data << "]");
}

int main(int argc, char* argv[]){
    ros::init(argc, argv, "listener");
    ros::NodeHandle nodeHandle;

    ros::Subscriber subscriber = 
        nodeHandle.subscribe("chatter", 10, chatterCallback);
    ros::spin();
    return 0;
}