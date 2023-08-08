//
// Created by Luca Fonstad on 4/22/23.
//

#ifndef HUBO_READER_H
#define HUBO_READER_H
#include <QTimer>
#include "PODOClient.h"
#include "ros/ros.h"
#include <sensor_msgs/JointState.h>

/**
 * Reader node - reads joint positions from HUBO, advertises the /joint_states
 * topic, and publishes the data as a message of type sensor_msgs/JointState.
 * 
 *  * client  - TCP Client for HUBO server.
 *  * n - ROS node.
 *  * readTimer - Qtimer.
 *  * jointPub - ROS publisher for joint states.
 *  * jointState - ROS sensor message with joint position data.
*/
class Reader : public QObject {

Q_OBJECT

public:
    Reader(PODOClient* _client, ros::NodeHandle* _n);
    PODOClient* client;
    ros::NodeHandle* n;
    QTimer *readTimer;

public slots:
    void startLoop();
    void ReadData();
    
private:
    ros::Publisher jointPub;
    sensor_msgs::JointState jointState;

};


#endif //HUBO_READER_H
