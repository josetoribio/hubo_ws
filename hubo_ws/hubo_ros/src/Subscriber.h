#include "ros/ros.h"
#include <sensor_msgs/JointState.h>
#include <QTimer>
#include "PODOClient.h"
#include "std_msgs/String.h"

class Subscriber : public QObject {
    Q_OBJECT
public:
    Subscriber(PODOClient* _client, ros::NodeHandle* n);
    PODOClient* client;
    ros::NodeHandle* n;
    QTimer *timer;
    void receiverCallback(const sensor_msgs::JointState& msg);
    ros::Subscriber sub;
    ros::Subscriber modeSub;
    void modeCallback(const std_msgs::String::ConstPtr& msg);
public slots:
    void shouldSpin();
};