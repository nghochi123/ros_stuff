#include <ros/ros.h>
#include <smb_localization/SmbLocalization.hpp>

namespace smb_localization {

SmbLocalization::SmbLocalization(ros::NodeHandle& nodeHandle) :
  nodeHandle_(nodeHandle)
{
    if(!nodeHandle_.getParam("odom0", odom)){
        ROS_ERROR("Could not find.");
    }

    if(!nodeHandle_.getParam("imu0", imu)){
        ROS_ERROR("Could not find.");
    }


    ros::Subscriber odom_subscriber = 
        nodeHandle_.subscribe(odom, 10, &SmbLocalization::odomCallback, this);
    
    ros::Subscriber imu_subscriber = 
        nodeHandle_.subscribe(imu, 10, &SmbLocalization::imuCallback, this);
        
    ros::spin();

}

SmbLocalization::~SmbLocalization()
{
} /* namespace */




void SmbLocalization::odomCallback(const nav_msgs::Odometry::ConstPtr &msg){
	ROS_INFO_STREAM_THROTTLE(2.0, "Seq: [%d]" << msg->header.seq);
    ROS_INFO_STREAM_THROTTLE(2.0, "Position-> x: [%f], y: [%f], z: [%f]" << msg->pose.pose.position.x << msg->pose.pose.position.y << msg->pose.pose.position.z);
    ROS_INFO_STREAM_THROTTLE(2.0, "Orientation-> x: [%f], y: [%f], z: [%f], w: [%f]" << msg->pose.pose.orientation.x << msg->pose.pose.orientation.y << msg->pose.pose.orientation.z << msg->pose.pose.orientation.w);
    ROS_INFO_STREAM_THROTTLE(2.0, "Vel-> Linear: [%f], Angular: [%f]" << msg->twist.twist.linear.x << msg->twist.twist.angular.z);
}

void SmbLocalization::imuCallback(const sensor_msgs::Imu::ConstPtr &msg){
	ROS_INFO_STREAM_THROTTLE(2.0,  "Accel: %.3f,%.3f,%.3f [m/s^2] - Ang. vel: %.3f,%.3f,%.3f [deg/sec] - Orient. Quat: %.3f,%.3f,%.3f,%.3f" <<
              msg->linear_acceleration.x << msg->linear_acceleration.y << msg->linear_acceleration.z <<
              msg->angular_velocity.x << msg->angular_velocity.y << msg->angular_velocity.z <<
              msg->orientation.x << msg->orientation.y << msg->orientation.z << msg->orientation.w);
}

    
}
