#pragma once

#include <ros/ros.h>
#include <sensor_msgs/LaserScan.h>
#include <string.h>
#include <sensor_msgs/PointCloud2.h>

namespace smb_highlevel_controller {

/**
 * Class containing the SMB Highlevel Controller
 */
class SmbHighlevelController {
 public:
  /** Constructor */
  SmbHighlevelController(ros::NodeHandle& nodeHandle);

  /** Destructor */
  virtual ~SmbHighlevelController();

 private:
  bool readParameters();
  void scanCallback(const sensor_msgs::LaserScan::ConstPtr& msg);

  ros::NodeHandle nodeHandle_;
  ros::Subscriber subscriber;
  std::string topic;
  int size;

  /*bonus task solution */
  ros::Subscriber pclSubscriber_;
};

}  // namespace smb_highlevel_controller
