#include "motor_health.h"
void health_init(motor_health_t *h,const health_config_t *c){*h=(motor_health_t){0};(void)c;h->state=MOTOR_NORMAL;}
void health_update(motor_health_t *h,float t,float c,float rms,float peak,int sensor_error){
h->temperature=t;h->current=c;h->vib_rms=rms;h->vib_peak=peak;h->warning_flags=0;h->fault_flags=0;
if(t>70)h->warning_flags|=1u;if(c>10)h->warning_flags|=2u;if(rms>1.5f)h->warning_flags|=4u;
if(t>85)h->fault_flags|=1u;if(c>15)h->fault_flags|=2u;if(peak>3.0f)h->fault_flags|=4u;if(sensor_error)h->fault_flags|=8u;
h->state=h->fault_flags?MOTOR_FAULT:(h->warning_flags?MOTOR_WARNING:MOTOR_NORMAL);
}
