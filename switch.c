#include <lpc214x.h>
#include "types.h"
#define SW 5
void InitSwitch(void){
IODIR0&=~(1<<SW);
}
u8 ReadSwitch(void){
if(((IOPIN0>>SW)&1)==0)
return 1;
else
return 0;
}
