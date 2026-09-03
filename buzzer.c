#include<lpc214x.h>
#include"types.h"
#include"buzzer.h"
#define BUZZER 19
void InitBuzzer(void){
IODIR0|=(1<<BUZZER);
IOCLR0=(1<<BUZZER);
}
void Buzzer_ON(void){
IOSET0=(1<<BUZZER);
}
void Buzzer_OFF(void){
IOCLR0=(1<<BUZZER);
}
