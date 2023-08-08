#include "PODOClient.h"


PODOClient::PODOClient(){
    dataSize = sizeof(LAN_PODO2GUI);
    dataReceived.clear();
    PortName = "PODOClient";
}

void PODOClient::RBReadData(){
    QDataStream in(RBClientSocket);
    in.setVersion(QDataStream::Qt_5_2);

    if(RBClientSocket->bytesAvailable() < dataSize)
        return;

    char *temp = new char[dataSize];
    while(RBClientSocket->bytesAvailable() >= dataSize){
        in.readRawData(temp, dataSize);
        QByteArray data;
        data.clear();
        data.append(temp, dataSize);
        dataReceived.push_back(data);
    }
    delete []temp;
}

