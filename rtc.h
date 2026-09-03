#ifndef _RTC_H_
#define _RTC_H_
#include <lpc214x.h>
#include "types.h"
void RTC_Init(void);

void SetRTCTimeInfo(u32 hour,u32 minute,u32 second);
void GetRTCTimeInfo(u32*hour,u32*minute,u32*sec);
void DisplayRTCTime(u32 hour,u32 minute,u32 second);
void SetRTCDateInfo(u32 date,u32 month,u32 year);
void GetRTCDateInfo(u32*date,u32*month,u32*year);
void DisplayRTCDate(u32 date,u32 month,u32 year);
void SetRTCDay(u32 day);
void GetRTCDayInfo(u32*day);
void DisplayRTCDay(u32 day);
u32 DaysInMonth(u32 month,u32 year);
void IncrementDate(u32 *date,u32 *month,u32 *year,u32 *day);

#endif
