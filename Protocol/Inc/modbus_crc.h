#pragma once
#include <stddef.h>
#include <stdint.h>
uint16_t modbus_crc16(const uint8_t *data,size_t len);
