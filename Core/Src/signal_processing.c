#include "signal_processing.h"
#include <math.h>
float signal_rms(const float *s,size_t n){if(!s||!n)return 0.0f;double sum=0;for(size_t i=0;i<n;i++)sum+=(double)s[i]*s[i];return (float)sqrt(sum/n);}
float signal_peak_abs(const float *s,size_t n){float p=0;if(!s)return 0;for(size_t i=0;i<n;i++){float a=s[i]<0?-s[i]:s[i];if(a>p)p=a;}return p;}
