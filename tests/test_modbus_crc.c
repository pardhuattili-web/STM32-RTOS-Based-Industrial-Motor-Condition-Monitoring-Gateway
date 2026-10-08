#include "modbus_crc.h"
#include <assert.h>
#include <stdio.h>
int main(void){const unsigned char f[]={1,3,0,0,0,10};assert(modbus_crc16(f,6)==0xCDC5);puts("modbus CRC: PASS");}
