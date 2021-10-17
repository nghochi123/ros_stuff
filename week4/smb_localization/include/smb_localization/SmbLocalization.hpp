#pragma once

#include <ros/ros.h>
#include <sensor_msgs/Imu.h>
#include <string.h>
#include "nav_msgs/Odometry.h"

namespace smb_localization {

/**
 * Class containing the SMB Highlevel Controller
 */
class SmbLocalization {
 public:
  /** Constructor */
  SmbLocalization(ros::NodeHandle& nodeHandle);

  /** Destructor */
  virtual ~SmbLocalization();

 private:
  bool readParameters();
  void odomCallback(const nav_msgs::Odometry::ConstPtr &msg);
  void imuCallback(const sensor_msgs::Imu::ConstPtr &msg);

  ros::NodeHandle nodeHandle_;
  ros::Subscriber subscriber;
  std::string odom;
  std::string imu;

};

}  // namespace smb_highlevel_controller
