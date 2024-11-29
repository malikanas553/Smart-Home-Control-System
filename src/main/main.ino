#include "DC_Motor.h"
#include <util/delay.h>

//Code For testing DC Motor Speed

void init(){

  DC_Init();

}

int main()
{

	  init();
    while(1)
	  {
      DC_Start(0, DIRECTION_CW, 300);
      _delay_ms(1000);
      DC_Stop(0);
      _delay_ms(1000);
      DC_Start(0, DIRECTION_CCW, 1023);
      _delay_ms(1000);
      DC_Stop(0);
      _delay_ms(1000);
	  }

	  return 0;

}
