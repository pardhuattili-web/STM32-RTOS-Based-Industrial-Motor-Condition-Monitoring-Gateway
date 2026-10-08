#include "modbus_crc.h"
uint16_t modbus_crc16(const uint8_t *d,size_t n){uint16_t crc=0xFFFF;for(size_t i=0;i<n;i++){crc^=d[i];for(int b=0;b<8;b++)crc=(crc&1)?(uint16_t)((crc>>1)^0xA001):(uint16_t)(crc>>1);}return crc;}
