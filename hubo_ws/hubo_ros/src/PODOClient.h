#ifndef LANDIALOG_H
#define LANDIALOG_H

#include <QDialog>
#include <QTimer>
#include <QSettings>
#include "LAN/RBTCPClient.h"


#include "LANData/RBLANData.h"


class PODOClient : public RBTCPClient
{
Q_OBJECT
public:
    PODOClient();

    QByteArrays     dataReceived;

protected slots:
    virtual void    RBReadData();

private:
    int     dataSize;
};

#endif // LANDIALOG_H
