
#ifndef     __CONFIG_H
#define     __CONFIG_H

#include <stdio.h>
#include <string.h>
#include "stc12c5a60s2.h"


#define         FSOC        11059200
#define         uint8       unsigned char
#define         int8        char
#define         uint16      unsigned int
#define         int16       int


#define         VERTION     0x13

sbit beep = P3 ^ 2;
sbit RS = P2 ^ 5;
sbit RW = P2 ^ 6;
sbit E = P2 ^ 7;
sbit TRIG =P1 ^ 3;
sbit ECHO =P1 ^ 4;
sbit P0_0=  P0 ^ 0;
sbit P0_1=  P0 ^ 1;
sbit P0_2=  P0 ^ 2;
sbit P0_3=  P0 ^ 3;
sbit P0_4=  P0 ^ 4;
sbit P0_5=  P0 ^ 5;
sbit P0_6=  P0 ^ 6;
sbit P0_7=  P0 ^ 7;

#define LongToBin(n) \
(\
((n >> 21) & 0x80) | \
((n >> 18) & 0x40) | \
((n >> 15) & 0x20) | \
((n >> 12) & 0x10) | \
((n >> 9) & 0x08) | \
((n >> 6) & 0x04) | \
((n >> 3) & 0x02) | \
((n ) & 0x01) \
)

#define Bin(n) LongToBin(0x##n##l)


#endif



