#include "ros/ros.h"
#include <sensor_msgs/JointState.h>
#include "JointInformation.h"

void jointCallback(const sensor_msgs::JointState& msg) {
    for (int i = 0; i < 25; i++) {
        ROS_INFO("Received sensor state of %f from %s", msg.position[i], JointNameList[i].c_str());
    }
}

int main(int argc, char **argv) {
    ros::init(argc, argv, "listener");
    ros::NodeHandle n;
    ros::Subscriber sub = n.subscribe("joint_states", 1, jointCallback);
    ros::spin();
}
