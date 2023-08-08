#include "Terminator.h"

Terminator::Terminator() {
    
}

void Terminator::startChecking() {
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()),
            this, SLOT(checkTime()));
    timer->start(100);
}

void Terminator::checkTime() {
    if (!ros::ok()) {
        emit terminate();
    }
}