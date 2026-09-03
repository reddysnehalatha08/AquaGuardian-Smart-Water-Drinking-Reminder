#include<lpc214x.h>
#include"types.h"
#include"lcd.h"
#include"lcd_defines.h"
#include "rtc.h"


#define FOSC 12000000
#define CCLK (5*FOSC)
#define PCLK  (CCLK/4)

#define PREINT_VAL ((int)(PCLK/32768)-1)
#define PREFRAC_VAL (PCLK-((PREINT_VAL+1)*32768))

#define RTC_ENABLE (1<<0)
#define RTC_RESET (1<<1)                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                        


char week[][4]={"SUN","MON","TUES","WED","THUS","FRI","SAT"};

void RTC_Init(void){
  
CCR=RTC_RESET;
PREINT=PREINT_VAL;
PREFRAC=PREFRAC_VAL;
CCR=RTC_ENABLE;

}

void SetRTCTimeInfo(u32 hour,u32 minute,u32 second){
HOUR=hour;
MIN=minute;
SEC=second;
}

void GetRTCTimeInfo(u32*hour,u32*minute,u32*second){
*hour=HOUR;
*minute=MIN;
*second=SEC;
}


void DisplayRTCTime(u32 hour,u32 minute,u32 second){
cmdLCD(GOTO_LINE1_POS0);
charLCD(hour/10+'0');
charLCD(hour%10+'0');
charLCD(':');
charLCD(minute/10+'0');
charLCD(minute%10+'0');
charLCD(':');
charLCD(second/10+'0');
charLCD(second%10+'0');
}

void SetRTCDateInfo(u32 date,u32 month,u32 year){
DOM=date;
MONTH=month;
YEAR=year;
}

void GetRTCDateInfo(u32*date,u32*month,u32*year){
*date=DOM;
*month=MONTH;
*year=YEAR;
}


void DisplayRTCDate(u32 date,u32 month,u32 year){
cmdLCD(GOTO_LINE2_POS0);
charLCD(date/10+'0');
charLCD(date%10+'0');
charLCD('/');
charLCD(month/10+'0');
charLCD(month%10+'0');
charLCD('/');
charLCD(year/10+'0');
charLCD(year%10+'0');
}


void SetRTCDay(u32 day){
DOW=day;
}

void GetRTCDayInfo(u32*day){
*day=DOW;
}

void DisplayRTCDay(u32 day){
cmdLCD(GOTO_LINE1_POS0+10);
strLCD(week[day]);
}


u32 DaysInMonth(u32 month,u32 year){
if(month==2){
if((year%4)==0)
return 29;
else
  return 28;
}
if(month==4||month==6||month==9||month==11)
return 30;
return 31;
}


void IncrementDate(u32 *date,u32 *month,u32 *year,u32 *day){
(*date)++;
if(*date>DaysInMonth(*month,*year))
{
*date=1;
(*month)++;
if(*month>12)
{
*month=1;
(*year)++;
}
}
(*day)++;
if(*day>6)
*day=0;
}
  



