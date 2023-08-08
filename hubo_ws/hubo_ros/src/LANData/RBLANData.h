#ifndef RBLANDATA_H
#define RBLANDATA_H

#include "../RBSharedMemory.h"
#include "../UserSharedMemory.h"

typedef struct __LAN_STRUCT_GUI2PODO__
{
    USER_COMMAND            UserCMD;
    GUI2MOTION              UserG2M;
} LAN_GUI2PODO,*pLAN_GUI2PODO;

typedef struct __LAN_STRUCT_PODO2GUI__
{
    RBCORE_SHM_REFERENCE    CoreREF;
    RBCORE_SHM_SENSOR       CoreSEN;
    RBCORE_SHM_COMMAND      CoreCMD;

    MOTION2GUI              UserM2G;
} LAN_PODO2GUI, *pLAN_PODO2GUI;

typedef struct __LAN_STRUCT_VISION2PODO__
{
    int    data_type;
    float  data_x;
    float  data_y;
    float  data_z;
}LAN_VISION2PODO;

#endif // RBLANDATA_H
