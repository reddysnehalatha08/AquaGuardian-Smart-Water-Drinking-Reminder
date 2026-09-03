#include<lpc214x.h>
#include"lcd.h"
#include"lcd_defines.h"
#include"delay.h"
#include"rtc.h"
#include"switch.h"
#include"led.h"
#include"buzzer.h"
#include"config.h"
#include"kpm.h"
u32 hour,min,sec,year,month,date,day,MON;
u8 glass[16]={0x0a,0x11,0x11,0x11,0x1f,0x1f,0x1f,0x00,0x0a,0x11,0x11,0x11,0x11,0x11,0x1f,0x00};
extern u32 newGoal;
u8 daydone=0;
u32 glasscount=8;
u32 i;
u8 remindFlag=0;
u32 nextRemindMin;
u32 startMin;
u32 drankcount=0;
u32 missedcount=0;
u32 remindercount=0;
u8 midnightflag=0;
u8 goalchanged=0;

volatile u8 configFlag=0;

void EINT3_ISR(void) __irq
{
     configFlag=1;
     EXTINT=(1<<3);
     VICVectAddr=0;
}
void Init_EINT3(void){
     PINSEL1&=~(3<<8);
     PINSEL1|=(3<<8);
     EXTMODE|=(1<<3);
     EXTPOLAR&=~(1<<3);
     EXTINT=(1<<3);
     VICIntSelect&=~(1<<17);
     VICVectAddr10=(unsigned long)EINT3_ISR;
     VICVectCntl10 =0x20|17;
     VICIntEnable|=(1<<17);
}

void configurationMenu(void){
     u32 key;
     GreenLED_OFF();
     YellowLED_OFF();
     Red_OFF();
     cmdLCD(CLEAR_LCD);
     cmdLCD(GOTO_LINE1_POS0);
     strLCD("1.Goal 2.Time");
     cmdLCD(GOTO_LINE2_POS0);
     strLCD("3.Date E.Exit");
while(1){
     key=Keyscan();
if(key=='1'){
     GreenLED_OFF();
     YellowLED_OFF();
     Red_OFF();
     goalchanged=1;
     SetWaterGoal();
     return;
}
if(key=='2'){
     GreenLED_OFF();
     YellowLED_OFF();
     Red_OFF();
     SetNewTime();
     return;
}
if(key=='3'){
     GreenLED_OFF();
     YellowLED_OFF();
     Red_OFF();
     SetNewDate();
     return;
}
if(key=='E'){
     break;
}
}
     GreenLED_OFF();
     YellowLED_OFF();
     Red_OFF();
     cmdLCD(CLEAR_LCD);
}


main(){
     RTC_Init();
     InitLCD();
     Init_kpm();
     InitSwitch();
     InitLED();
     InitBuzzer();
     Init_EINT3(); 
     BuildCGRAM(glass,16);
     SetRTCTimeInfo(15,02,00);
     GetRTCTimeInfo(&hour,&min,&sec);
     nextRemindMin=(min+2)%60;
     SetRTCDateInfo(11,4,26);
     SetRTCDay(MON);
     newGoal=8;
while(1){
if(configFlag==1){
     configFlag=0;
     GreenLED_OFF();
     YellowLED_OFF();
     Red_OFF();
     Buzzer_OFF();
     cmdLCD(CLEAR_LCD);
     cmdLCD(GOTO_LINE1_POS0);
     strLCD("INTERRUPT OK");
     delay_s(2);
     configurationMenu();
     configFlag=0;
  if(goalchanged){
     glasscount=newGoal;
     goalchanged=0;
}
      GreenLED_OFF();
      YellowLED_OFF();
      Red_OFF();
      GetRTCTimeInfo(&hour,&min,&sec);
      GetRTCDateInfo(&date,&month,&year); 
      GetRTCDayInfo(&day);
      nextRemindMin=(min+2)%60;
      remindFlag=0;
      cmdLCD(CLEAR_LCD);
      continue;
}
      GetRTCTimeInfo(&hour,&min,&sec);
      if(hour==0&&min==0&&sec==0){
      if( midnightflag==0){
      midnightflag=1;
      IncrementDate(&date,&month,&year,&day);
      SetRTCDateInfo(date,month,year);
      SetRTCDay(day);
      glasscount=newGoal;
      drankcount=0;
      missedcount=0;
      remindercount=0;
      remindFlag=0;
      daydone=0;
      GetRTCTimeInfo(&hour,&min,&sec);
      nextRemindMin=(min+2)%60;
      Buzzer_OFF();
      YellowLED_OFF();
      GreenLED_OFF();
      Red_OFF();
      cmdLCD(CLEAR_LCD);
   }
      continue;
   }
   else{
         midnightflag=0;
   }
         GetRTCTimeInfo(&hour,&min,&sec);
         DisplayRTCTime(hour,min,sec);
         GetRTCDateInfo(&date,&month,&year);
         DisplayRTCDate(date,month,year);
         GetRTCDayInfo(&day);
          DisplayRTCDay(day);
          cmdLCD(GOTO_LINE2_POS0+10);
          charLCD(0);
          charLCD(':');
          u32LCD(glasscount);
  if(glasscount>0&&daydone==0&&min==nextRemindMin&&sec==0&&remindFlag==0){
          remindFlag=1;
          startMin=min;
          cmdLCD(CLEAR_LCD);
          cmdLCD(GOTO_LINE1_POS0);
          strLCD("Time To Drink");
          YellowLED_ON();
          Buzzer_ON();
          cmdLCD(GOTO_LINE2_POS0);
for(i=0;i<glasscount;i++)
          charLCD(0);
          delay_s(3);
          GreenLED_OFF();
          Red_OFF();
          startMin=min;
while(1)
{
         GetRTCTimeInfo(&hour,&min,&sec);
if(ReadSwitch())
{
        Buzzer_OFF();
        YellowLED_OFF();
        GreenLED_ON();
if(glasscount>0)
        glasscount--;
        drankcount++;
        remindercount++;
        cmdLCD(CLEAR_LCD);
        cmdLCD(GOTO_LINE1_POS0);
        strLCD("drank water");
        cmdLCD(GOTO_LINE2_POS0);
for(i=0;i<drankcount;i++)
        charLCD(1);
for(i=0;i<glasscount;i++)
        charLCD(0);
        delay_s(5);
        cmdLCD(CLEAR_LCD);
        GreenLED_OFF();
        break;
}
if(min!=startMin){
        Buzzer_OFF();
        YellowLED_OFF(); 
        Red_ON();
        missedcount++;
        remindercount++; 
        cmdLCD(GOTO_LINE1_POS0);
        strLCD("MISSED WATER");
        delay_s(3);
        Red_OFF(); 
        cmdLCD(CLEAR_LCD);
        break;
}
}
if(remindercount==newGoal){
        cmdLCD(CLEAR_LCD);
        cmdLCD(GOTO_LINE1_POS0);
        strLCD("Todays status");
        cmdLCD(GOTO_LINE2_POS0);
        charLCD(1);
        u32LCD(drankcount);
        cmdLCD(GOTO_LINE2_POS0+10);
        charLCD(0);
        u32LCD(missedcount);
        delay_s(5); 
        drankcount=0;
        missedcount=0;
        remindercount=0;
        remindFlag=0;
        daydone=1;
        GetRTCTimeInfo(&hour,&min,&sec);
        nextRemindMin=(min+2)%60;
        Buzzer_OFF();
        YellowLED_OFF();
        GreenLED_OFF();
        Red_OFF();
        cmdLCD(CLEAR_LCD);
        continue;
}
         nextRemindMin+=2;
         if(nextRemindMin>=60) 
         nextRemindMin-=60;
if(min!=nextRemindMin||sec!=0){
         remindFlag=0;
}
}
}
}










