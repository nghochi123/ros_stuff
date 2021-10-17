#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <visualization_msgs/Marker.h>
#include <smb_highlevel_controller/SmbHighlevelController.hpp>

namespace smb_highlevel_controller {


float linx, angz;

geometry_msgs::Twist twm;

SmbHighlevelController::SmbHighlevelController(ros::NodeHandle& nodeHandle) :
  nodeHandle_(nodeHandle)
{
    if(!nodeHandle_.getParam("topic_name", topic)){
        ROS_ERROR("Could not find.");
    }

    if(!nodeHandle_.getParam("queue_size", size)){
        ROS_ERROR("Could not find.");
    }

    ros::Subscriber scan_subscriber = 
        nodeHandle_.subscribe(topic, size, &SmbHighlevelController::scanCallback, this);
    
    ros::Publisher twist_publisher = 
        nodeHandle_.advertise<geometry_msgs::Twist>("/cmd_vel", 10);

    ros::Publisher vis_pub = 
        nodeHandle_.advertise<visualization_msgs::Marker>( "visualization_marker", 0 );

    ros::Rate loop_rate(10);

    while(ros::ok()){

        twist_publisher.publish(twm);
        ros::spinOnce();
        loop_rate.sleep();

        visualization_msgs::Marker marker;
        marker.header.frame_id = "base_link";
        marker.header.stamp = ros::Time();
        marker.ns = "my_namespace";
        marker.id = 0;
        marker.type = visualization_msgs::Marker::SPHERE;
        marker.action = visualization_msgs::Marker::ADD;
        marker.pose.position.x = 1;
        marker.pose.position.y = 1;
        marker.pose.position.z = 1;
        marker.pose.orientation.x = 0.0;
        marker.pose.orientation.y = 0.0;
        marker.pose.orientation.z = 0.0;
        marker.pose.orientation.w = 1.0;
        marker.scale.x = 1;
        marker.scale.y = 0.1;
        marker.scale.z = 0.1;
        marker.color.a = 1.0; // Don't forget to set the alpha!
        marker.color.r = 0.0;
        marker.color.g = 1.0;
        marker.color.b = 0.0;
        vis_pub.publish( marker );

    }
    
    ros::spin();

}

SmbHighlevelController::~SmbHighlevelController()
{
} /* namespace */




void SmbHighlevelController::scanCallback(const sensor_msgs::LaserScan::ConstPtr &msg){
     //scan->ranges[] are laser readings
     //ROS_INFO(msg);
    double min = msg->range_max;
	for (int i = msg->ranges.size()/2 - 10; i < msg->ranges.size()/2 + 10; ++i) {
		if (msg->ranges[i] < min)
			min = msg->ranges[i];
	}
    if(min < 20){
        twm.linear.x = 0.5;
        twm.angular.z = 0;
    } else{
        twm.linear.x = 0;
        twm.angular.z = 0.5;
    }
    
	ROS_INFO_STREAM_THROTTLE(2.0,"Minimum Range: " << min);
    
}

    
}
