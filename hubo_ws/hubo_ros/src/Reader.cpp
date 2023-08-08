//
// Created by Luca Fonstad on 4/22/23.
//

#include "Reader.h"
#include "JointInformation.h"
#include <iostream>


#include <sstream>
extern LAN_PODO2GUI PODO_DATA;

// Constructor

Reader::Reader(PODOClient* _client, ros::NodeHandle* _n) : client(_client), n(_n) {
    jointPub = n->advertise<sensor_msgs::JointState>("joint_states", 1);
    jointState.name.resize(NO_OF_JOINTS);
    for (int i = 0; i < NO_OF_JOINTS; i++) {
        jointState.name[i] = JointNameList[i];
    }
    jointState.position.resize(NO_OF_JOINTS);
}

// Slots

/**
 * Initialize readTimer to ensure Reader reads every 1 second. 
*/
void Reader::startLoop() {
    readTimer = new QTimer(this);
    connect(readTimer, SIGNAL(timeout()),
            this, SLOT(ReadData()));
    readTimer->start(1000);
}

/**
 * Index into data sent from HUBO, get joint positions from the encoder,
 * and publish the readings to the /joint_states topic.
*/
void Reader::ReadData() {
    if(client->dataReceived.size() > 0){
        //ROS_INFO("Publishing joint states");
        QByteArray tempPODOData = client->dataReceived[0];
        client->dataReceived.pop_front();
        memcpy(&PODO_DATA, tempPODOData, sizeof(LAN_PODO2GUI));

        RBCORE_SHM_SENSOR sensors = PODO_DATA.CoreSEN;
        for (int i = 0; i < NO_OF_JOINTS; i++) {
            double pos = (double) sensors.ENCODER[MC_GetID(i)][MC_GetCH(i)].
                CurrentPosition;
            jointState.position[i] = pos;
        }
        jointPub.publish(jointState);
    } else {
        //ROS_INFO("Did not receive any information");
    }
}
