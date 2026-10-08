#pragma once
#include <stdint.h>
typedef struct {uint16_t state,temp_x10,current_x100,vib_rms_x100,vib_peak_x100,warnings,faults;} modbus_snapshot_t;
int modbus_read_register(const modbus_snapshot_t *s,uint16_t address,uint16_t *value);
