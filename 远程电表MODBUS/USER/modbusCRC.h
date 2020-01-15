#ifndef _MODBUS_CRC_H_
#define _MODBUS_CRC_H_
#include "stm32f10x_conf.h"
#define uint u16
#define uchar u8
uint crc16( uchar *puchMsg, uint usDataLen );
#endif
