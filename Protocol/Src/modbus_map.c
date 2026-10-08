#include "modbus_map.h"
int modbus_read_register(const modbus_snapshot_t *s,uint16_t a,uint16_t *v){if(!s||!v||a<40001||a>40007)return -1;const uint16_t *m=&s->state;*v=m[a-40001];return 0;}
