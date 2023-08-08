#include <QObject>
#include "ros/ros.h"
#include <QTimer>

class Terminator : public QObject {
Q_OBJECT
public:
    Terminator();
    QTimer *timer;
public slots:
    void startChecking();
    void checkTime();
signals:
    void terminate();
};