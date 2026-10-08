#include "signal_processing.h"
#include "motor_health.h"
#include <assert.h>
#include <math.h>
#include <stdio.h>
int main(void){const float x[]={1,-1,1,-1};assert(fabsf(signal_rms(x,4)-1)<0.001f);assert(fabsf(signal_peak_abs(x,4)-1)<0.001f);motor_health_t h;health_config_t c={0};health_init(&h,&c);health_update(&h,40,2,0.5f,1,0);assert(h.state==MOTOR_NORMAL);health_update(&h,90,2,0.5f,1,0);assert(h.state==MOTOR_FAULT);puts("signal/health: PASS");}
