#include <ros/ros.h>
#include "smb_localization/SmbLocalization.hpp"

int main(int argc, char** argv) {
  ros::init(argc, argv, "smb_localization");
  ros::NodeHandle nodeHandle("~");

  smb_localization::SmbLocalization smbLocalization(nodeHandle);

  ros::spin();
  return 0;
}
