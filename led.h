#ifndef _LED_H_
#define _LED_H_

#include<lpc214x.h>
#include "types.h"
void InitLED(void);

void GreenLED_ON(void);
void GreenLED_OFF(void);

void YellowLED_ON(void);
void YellowLED_OFF(void);

void Red_ON(void);
void Red_OFF(void);

#endif
