#ifndef RBTCPCLIENT_H
#define RBTCPCLIENT_H

#include <QTcpSocket>
#include "RBLANCommon.h"



class RBTCPClient : public QTcpSocket
{
Q_OBJECT
public:
    RBTCPClient(QObject *parent = 0);
    virtual ~RBTCPClient();

    void RBConnect(QString _ip = "192.168.1.100", quint16 _port = 4000);
    void RBDisconnect();
    void RBSendData(QByteArray &data);

    quint8          RBConnectionState;

private slots:
    void            RBClientConnected();
    void            RBClientDisconnected();

protected slots:
    virtual void    RBReadData() = 0;

signals:
    void            SIG_Connected();
    void            SIG_Disconnected();

protected:
    QTcpSocket			*RBClientSocket;
    QString             PortName;

private:
    QString				RBIpAdress;
    quint16				RBPortNumber;
};

#endif // RBTCPCLIENT_H
