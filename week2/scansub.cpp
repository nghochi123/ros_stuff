#include <ros/ros.h>

void scanCallback(const std_msgs::String& msg){
    ROS_INFO_STREAM("SCAN INFO" << msg.data << "!!!")
}

int main(int argc, char* argv[]){
    ros::init(argc, argv, "listener")
    ros::NodeHandle nodeHandle;

    std::string topic;
    std::string size;
    if(!nodeHandle.getParam("topic_name", topic)){
        ROS_ERROR("Could not find.");
    }

    if(!nodeHandle.getParam("queue_size", size)){
        ROS_ERROR("Could not find.");
    }

    ros::Subscriber subscriber = 
        nodeHandle.subscribe("scan", 100, scanCallback);
    ros::spin();

    return 0;
}