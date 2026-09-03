#include"types.h"
#include"lcd.h"
#include"kpm.h"
#include"rtc.h"
#include"delay.h"
#include"config.h"
#include"lcd_defines.h"
         extern u32 glasscount;
         u32 newGoal=0;
         void SetWaterGoal(void){
         while(colscan()==0);
         delay_s(1);
         cmdLCD(CLEAR_LCD);
         cmdLCD(GOTO_LINE1_POS0);
         strLCD("Set Goal:");
         cmdLCD(GOTO_LINE2_POS0);
         newGoal=gettwodigits(1,99);
         glasscount=newGoal;
         cmdLCD(GOTO_LINE1_POS0);
         strLCD("Goal Updated");
         delay_s(2);
 }

static u32 gettwodigits(u32 min,u32 max){
         u8 value[2];
         u32 pos=0;
         u32 key;
         u32 result;
         u8 valid=0;
while(!valid){
         pos=0;
         cmdLCD(GOTO_LINE2_POS0);
         strLCD("   ");
         cmdLCD(GOTO_LINE2_POS0);
while(1){
         key=Keyscan();
         if(key>='0'&&key<='9'){
if(pos<2){
         value[pos]=key;
         pos++;
}
}
else if(key=='B'){
     if(pos>0)
        pos--;
}
else if(key=='E' && pos>0){
        break;
}
        cmdLCD(GOTO_LINE2_POS0);
        strLCD("              ");
        cmdLCD(GOTO_LINE2_POS0);
      if(pos>0)
        charLCD(value[0]);
      if(pos>1)
        charLCD(value[1]);
}

      if(pos==1)
         return (value[0]-'0');
      else
         return (value[0]-'0')*10+(value[1]-'0');
if(result>=min&&result<=max){
         valid=1;
}
else{
         cmdLCD(GOTO_LINE1_POS0);
         strLCD("Invalid retry");
         delay_s(2);
         cmdLCD(GOTO_LINE1_POS0);
         strLCD("   ");
}
}
         return result;
}


static void getcompletedate(u32 *date,u32 *month,u32 *year)
 {
         u8 value[6];
         u32 pos=0;
         u32 key;
         u32 d,m,y;
 while(1){
  pos=0;
         cmdLCD(CLEAR_LCD);
         cmdLCD(GOTO_LINE1_POS0);
         strLCD("ENTER DATE");
 while(1){
         key=Keyscan();
 if(key>='0'&&key<='9'){
 if(pos<6){
         value[pos]=key;
         pos++;
}
}
else if(key=='B')
{
   if(pos>0)
         pos--;
}
else if(key=='E' && pos>0) {
         d=(value[0]-'0')*10+(value[1]-'0');
         m= (value[2]-'0')*10+(value[3]-'0');
         y=(value[4]-'0')*10+(value[5]-'0');
if(d<1||d>31||m<1||m>12){
         cmdLCD(CLEAR_LCD);
         cmdLCD(GOTO_LINE1_POS0);
         strLCD("invalid date");
         delay_s(2);
         break;
}
         *date=d;
         *month=m;
         *year=y;
         return;
}
         cmdLCD(GOTO_LINE2_POS0);
         strLCD("           ");
         cmdLCD(GOTO_LINE2_POS0);
  if(pos>0)
         charLCD(value[0]);
  if(pos>1)
         charLCD(value[1]);
 if(pos>2){
         charLCD('/');
         charLCD(value[2]);
}
  if(pos>3)
         charLCD(value[3]);
  if(pos>4){
         charLCD('/');
         charLCD(value[4]);
}
if(pos>5)
         charLCD(value[5]);
}
}
}

 static void getcompletetime(u32 *hour,u32 *min,u32 *sec)
 {
 u8 value[6];
 u32 pos=0;
 u32 key;
 u32 h,m,s;

 while(1){
 pos=0;
 cmdLCD(CLEAR_LCD);
 cmdLCD(GOTO_LINE1_POS0);
 strLCD("Enter Time");
 while(1){
 key=Keyscan();
 if(key>='0'&&key<='9'){
 if(pos<6){
value[pos]=key;
pos++;
}
}
else if(key=='B')
{
if(pos>0)
pos--;
}
else if(key=='E' && pos>0){

h=(value[0]-'0')*10+(value[1]-'0');
m= (value[2]-'0')*10+(value[3]-'0');
s=(value[4]-'0')*10+(value[5]-'0');
if(h>23||m>59||s>59){
cmdLCD(CLEAR_LCD);
cmdLCD(GOTO_LINE1_POS0);
strLCD("invalid time");
delay_s(2);
break;

}
*hour=h;
*min=m;
*sec=s;
return;
}
cmdLCD(GOTO_LINE2_POS0);
strLCD("           ");
cmdLCD(GOTO_LINE2_POS0);
if(pos>0)
charLCD(value[0]);
if(pos>1)
charLCD(value[1]);
if(pos>2){
charLCD(':');
charLCD(value[2]);
}
if(pos>3)
charLCD(value[3]);
if(pos>4){
charLCD(':');
charLCD(value[4]);
}
if(pos>5)
charLCD(value[5]);
}

}
}




 void SetNewDate(void){
 u32 date,month,year;
 u32 choice;
 GetRTCDateInfo(&date,&month,&year);
 cmdLCD(CLEAR_LCD);
 cmdLCD(GOTO_LINE1_POS0);
 strLCD("1D 2M 3Y 4ALL");
choice=Keyscan();
 while(choice!='1'&&choice!='2'&&choice!='3'&&choice!='4'){
 choice=Keyscan();
 }
 cmdLCD(CLEAR_LCD);
 if(choice=='1'){
 cmdLCD(GOTO_LINE1_POS0);
 strLCD("set date");
 cmdLCD(GOTO_LINE2_POS0);
 date=gettwodigits(1,31);
 }
 else if(choice=='2'){
 cmdLCD(GOTO_LINE1_POS0);
  strLCD("set month");
 cmdLCD(GOTO_LINE2_POS0);
 month=gettwodigits(1,12);
 }
 else if(choice=='3'){
 cmdLCD(GOTO_LINE1_POS0);
 strLCD("set year");
 cmdLCD(GOTO_LINE2_POS0);
 year=gettwodigits(0,99);

 }
 else if(choice=='4'){
 cmdLCD(GOTO_LINE1_POS0);
 strLCD("DD/MM/YY");
cmdLCD(GOTO_LINE2_POS0);
getcompletedate(&date,&month,&year);
}


SetRTCDateInfo(date,month,year);
cmdLCD(CLEAR_LCD);
cmdLCD(GOTO_LINE1_POS0);
strLCD("Date Updated");
delay_s(2);
}






   void SetNewTime(void){
 u32 hour,min,sec;
 u32 choice;
 GetRTCDateInfo(&hour,&min,&sec);
 cmdLCD(CLEAR_LCD);
 cmdLCD(GOTO_LINE1_POS0);
 strLCD("1H 2M 3S 4ALL");
 choice=Keyscan();
 while(choice!='1'&&choice!='2'&&choice!='3'&&choice!='4'){
 choice=Keyscan();
 }
 cmdLCD(CLEAR_LCD);
 if(choice=='1'){
 cmdLCD(GOTO_LINE1_POS0);
 strLCD("set hour");
 cmdLCD(GOTO_LINE2_POS0);
 hour=gettwodigits(0,23);

 }
 else if(choice=='2'){
 cmdLCD(GOTO_LINE1_POS0);
 strLCD("set minute");
 cmdLCD(GOTO_LINE2_POS0);
 min=gettwodigits(0,59);
 }
 else if(choice=='3'){
 cmdLCD(GOTO_LINE1_POS0);
 strLCD("set second");
 cmdLCD(GOTO_LINE2_POS0);
 sec=gettwodigits(0,59);

 }
 else if(choice=='4'){
 cmdLCD(GOTO_LINE1_POS0);
 strLCD("HH:MM:SS");
cmdLCD(GOTO_LINE2_POS0);
getcompletetime(&hour,&min,&sec);
}

SetRTCTimeInfo(hour,min,sec);
cmdLCD(CLEAR_LCD);
cmdLCD(GOTO_LINE1_POS0);
strLCD("Time Updated");
delay_s(2);
}

