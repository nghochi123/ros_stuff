#include <ros/ros.h>
#include <smb_highlevel_controller/SmbHighlevelController.hpp>

namespace smb_highlevel_controller {

SmbHighlevelController::SmbHighlevelController(ros::NodeHandle& nodeHandle) :
  nodeHandle_(nodeHandle)
{
    if(!nodeHandle_.getParam("topic_name", topic)){
        ROS_ERROR("Could not find.");
    }

    if(!nodeHandle_.getParam("queue_size", size)){
        ROS_ERROR("Could not find.");
    }

    ros::Subscriber subscriber = 
        nodeHandle_.subscribe(topic, size, &SmbHighlevelController::scanCallback, this);
    ros::spin();

}

SmbHighlevelController::~SmbHighlevelController()
{
} /* namespace */




void SmbHighlevelController::scanCallback(const sensor_msgs::LaserScan::ConstPtr &msg){
     //scan->ranges[] are laser readings
     //ROS_INFO(msg);
     double min = msg->range_max;
	for (int i = 0; i < msg->ranges.size(); ++i) {
		if (msg->ranges[i] < min)
			min = msg->ranges[i];
	}
	ROS_INFO_STREAM_THROTTLE(2.0,"Minimum Range: " << min);
    
}

    
}
