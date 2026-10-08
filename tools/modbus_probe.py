#!/usr/bin/env python3
import argparse
def crc(data):
    c=0xFFFF
    for x in data:
        c^=x
        for _ in range(8): c=(c>>1)^0xA001 if c&1 else c>>1
    return c
p=argparse.ArgumentParser();p.add_argument("--slave",type=int,default=1);a=p.parse_args()
frame=bytes([a.slave,3,0,0,0,10]);c=crc(frame)
print((frame+bytes([c&255,c>>8])).hex(" "))
