#include"types.h"
#include"lcd.h"
# define GREEN_LED 20
# define YELLOW_LED 21
# define RED_LED 22
void InitLED(void){
IODIR1|=(1<<GREEN_LED)|(1<<YELLOW_LED)|(1<<RED_LED);
IOSET1=(1<<GREEN_LED)|(1<<YELLOW_LED)|(1<<RED_LED);
}
void GreenLED_ON(void){
IOCLR1=(1<< GREEN_LED);
}
void GreenLED_OFF(void){
IOSET1=(1<<GREEN_LED);
}
void YellowLED_ON(void){
IOCLR1=(1<<YELLOW_LED);
}
void YellowLED_OFF(void){
IOSET1=(1<<YELLOW_LED);
}
void Red_ON(void){
IOCLR1=(1<<RED_LED);
}
void Red_OFF(void){
IOSET1=(1<<RED_LED);
}
