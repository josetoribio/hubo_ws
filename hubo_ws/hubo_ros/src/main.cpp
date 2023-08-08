#include <iostream>
#include "PODOClient.h"
#include <QEventLoop>
#include <QCoreApplication>
#include "Reader.h"
#include "JointInformation.h"
#include "ros/ros.h"
#include "Terminator.h"
#include <QThread>
#include "Subscriber.h"

using namespace std;

LAN_PODO2GUI PODO_DATA;


int main(int argc, char *argv[]) {

    QCoreApplication app(argc, argv);
    Terminator *terminator = new Terminator;
    QThread *terminatorThread = new QThread;
    terminator->moveToThread(terminatorThread);
    QObject::connect(terminatorThread, &QThread::started, terminator, &Terminator::startChecking);
    QObject::connect(terminatorThread, &QThread::finished, terminator, &QObject::deleteLater);
    QObject::connect(terminatorThread, &QThread::finished, terminatorThread, &QObject::deleteLater);
    terminatorThread->start();
    QObject::connect(terminator, &Terminator::terminate, &app, &QCoreApplication::quit);
    ros::init(argc, argv, "hubotalker");
    ros::NodeHandle n;
    PODOClient client;
    client.RBConnect();
    Reader *reader = new Reader(&client, &n);
    QThread *readerThread = new QThread;
    reader->moveToThread(readerThread);
    QObject::connect(readerThread, &QThread::started, reader, &Reader::startLoop);
    QObject::connect(readerThread, &QThread::finished, reader, &QObject::deleteLater);
    QObject::connect(readerThread, &QThread::finished, readerThread, &QObject::deleteLater);
    readerThread->start();
    Subscriber subscriber(&client, &n);

    return app.exec();
}
