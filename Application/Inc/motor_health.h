#pragma once
#include <stdint.h>
typedef enum { MOTOR_NORMAL, MOTOR_WARNING, MOTOR_FAULT } motor_state_t;
typedef struct {float temp_warn,temp_fault,current_warn,current_fault,vib_warn,vib_fault;} health_config_t;
typedef struct {float temperature,current,vib_rms,vib_peak;motor_state_t state;uint32_t warning_flags,fault_flags;} motor_health_t;
void health_init(motor_health_t *h,const health_config_t *cfg);
void health_update(motor_health_t *h,float temp,float current,float rms,float peak,int sensor_error);
