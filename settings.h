#ifndef SETTINGS_H
#define SETTINGS_H
#include "types.h"
u32 GetDigit(void);
static u32 gettwodigits(u32 min,u32 max);
void SetWaterGoal(void);
void SetNewTime(void);
void SetNewDate(void);
void configurationMenu(void);
void Init_EINT3(void);
#endif
