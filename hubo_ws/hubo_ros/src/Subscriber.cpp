#include "Subscriber.h"
#include <unordered_map>
#include <string>


enum MELKCOMMAND
{
    MELK_NO_ACT = 100,
    MELK_GO_WALKREADYPOS,
    MELK_GO_HOMEPOS,
    MELK_WHEELCMD,
    MELK_GOTODES,
    MELK_INFINITY,
    MELK_MOVEHAND,
    MELK_SHOW_INFO,
    MELK_SHOW_JOINT_VALUES,
    MELK_MOVE_JOINTS,
    MELK_DEMO_MOVEHAND,
    MELK_DEMO_INITIALPOSITION,
    MELK_DRAW_RECTANGLE,
};

Subscriber::Subscriber(PODOClient* _client, ros::NodeHandle* _n) : client(_client), n(_n) {
    sub = n->subscribe("joint_refs", 1, &Subscriber::receiverCallback, this);
    modeSub = n->subscribe("robot_mode", 1, &Subscriber::modeCallback, this);
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()),
            this, SLOT(shouldSpin()));
    timer->start(100);
}

void Subscriber::shouldSpin() {
    ros::spinOnce();
}

void Subscriber::modeCallback(const std_msgs::String::ConstPtr& msg) {
    if (msg->data == std::string("home_position")) {
        ROS_INFO("Setting robot to home position");
        USER_COMMAND cmd;
        cmd.COMMAND_TARGET = 10;
        cmd.COMMAND_DATA.USER_COMMAND = MELK_GO_HOMEPOS;
        LAN_GUI2PODO tempDATA;
        memcpy(&(tempDATA.UserCMD), &cmd, sizeof(USER_COMMAND));
        QByteArray tempSendData = QByteArray::fromRawData((char *)&tempDATA, sizeof(LAN_GUI2PODO));
        client->RBSendData(tempSendData);
    } else if (msg->data == "wheel_position") {
        ROS_INFO("Setting robot to wheel position");
        USER_COMMAND cmd;
        cmd.COMMAND_TARGET = 10;
        cmd.COMMAND_DATA.USER_PARA_CHAR[0]=0;
        cmd.COMMAND_DATA.USER_COMMAND = MELK_WHEELCMD;
        LAN_GUI2PODO tempDATA;
        memcpy(&(tempDATA.UserCMD), &cmd, sizeof(USER_COMMAND));
        QByteArray tempSendData = QByteArray::fromRawData((char *)&tempDATA, sizeof(LAN_GUI2PODO));
        client->RBSendData(tempSendData);
    } else if (msg->data == "walking_position") {
        ROS_INFO("Setting robot to walking position");
        USER_COMMAND cmd;
        cmd.COMMAND_TARGET = 10;
        cmd.COMMAND_DATA.USER_PARA_INT[0] = 0;
        cmd.COMMAND_DATA.USER_COMMAND = MELK_GO_WALKREADYPOS;
        
        LAN_GUI2PODO tempDATA;
        memcpy(&(tempDATA.UserCMD), &cmd, sizeof(USER_COMMAND));
        QByteArray tempSendData = QByteArray::fromRawData((char *)&tempDATA, sizeof(LAN_GUI2PODO));
        client->RBSendData(tempSendData);
    }
}

void Subscriber::receiverCallback(const sensor_msgs::JointState& msg) {
    std::unordered_map<std::string,int> nameMap;
    nameMap["RSP"] = 0;
    nameMap["LSP"] = 1;
    nameMap["RSR"] = 2;
    nameMap["LSR"] = 3;
    nameMap["RSY"] = 4;
    nameMap["LSY"] = 5;
    nameMap["REB"] = 6;
    nameMap["LEB"] = 7;
    nameMap["RWY"] = 8;
    nameMap["LWY"] = 9;
    nameMap["RWP"] = 10;
    nameMap["LWP"] = 11;
    nameMap["RWY2"] = 12;
    nameMap["LWY2"] = 13;
    nameMap["RHAND"] = 14;
    nameMap["LHAND"] = 15;
    nameMap["RHY"] = 16;
    nameMap["LHY"] = 17;
    nameMap["RHR"] = 18;
    nameMap["LHR"] = 19;
    nameMap["RHP"] = 20;
    nameMap["LHP"] = 21;
    nameMap["RKN"] = 22;
    nameMap["LKN"] = 23;
    nameMap["RAP"] = 24;
    nameMap["LAP"] = 25;
    nameMap["RAR"] = 26;
    nameMap["LAR"] = 27;
    nameMap["RWH"] = 28;
    nameMap["LWH"] = 29;
    nameMap["WST"] = 30;
    USER_COMMAND cmd;
    for (int i = 0; i < 31; i++) {
        cmd.COMMAND_DATA.USER_PARA_DOUBLE[i] = 0.0;
    }
    for (int i = 0; i < msg.name.size(); i++) {
        ROS_INFO("Sending command to move joint %s to position %f",msg.name[i].c_str(), msg.position[i]);
        cmd.COMMAND_DATA.USER_PARA_DOUBLE[nameMap[msg.name[i]]]=msg.position[i];
    }
    if (msg.velocity.empty()) {
        cmd.COMMAND_DATA.USER_PARA_DOUBLE[31]=5;
    } else {
        cmd.COMMAND_DATA.USER_PARA_DOUBLE[31]=msg.velocity[0];
    }
    ROS_INFO("Velocity set to %f",cmd.COMMAND_DATA.USER_PARA_DOUBLE[31]);
    cmd.COMMAND_DATA.USER_COMMAND = MELK_MOVE_JOINTS;
    cmd.COMMAND_TARGET = 10;
    

    LAN_GUI2PODO tempDATA;
    memcpy(&(tempDATA.UserCMD), &cmd, sizeof(USER_COMMAND));
    QByteArray tempSendData = QByteArray::fromRawData((char *)&tempDATA, sizeof(LAN_GUI2PODO));
    client->RBSendData(tempSendData);
}