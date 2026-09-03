#include"types.h"
#include"defines.h"
#include "kpm_defines.h"
#include "keypad_defines.h"
#include<lpc21xx.h>

u32 kpmLUT[4][4]= {{'1','2','3','A'},
                  {'4','5','6','B'},
                                  {'7','8','9','C'},
                                  {'*','0','#','E'}};
void Init_kpm(void){
WRITENIBBLE(IODIR1,row0,15);
}
u32 colscan(void)
{
if((READNIBBLE(IOPIN1,col0))<15)
return 0;
else
return 1;
}
u32 rowcheck(void){
u32 rno;
for(rno=0;rno<4;rno++){
WRITENIBBLE(IOPIN1,row0,(~(1<<rno)));
if(colscan()==0)
break;
}
IOCLR1=15<<row0;
return rno;
}
u32 colcheck(void){
u32 cno;
for(cno=0;cno<4;cno++){
if(READBIT(IOPIN1,(cno+col0))==0)
break;
}
return cno;
}
u32 Keyscan(void){
u32 rno,cno;
u32 key;
while(colscan()==1);
rno=rowcheck();
cno=colcheck();
key=kpmLUT[rno][cno];
while(colscan()==0);
return key;
}

