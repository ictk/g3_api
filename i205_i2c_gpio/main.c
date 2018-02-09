#include "il005define.h"
#include "il005test.h"
#include "il005communication.h"
#include "i2c_sw.h"

PI_THREAD(il005)
{
  (void)piHiPri(10);	// Set this thread to be high priority
  il005_menu();
}

int main(void)
{
  if(wiringPiSetup() == -1)
  	return 1;	

  i2c_init();  
  piThreadCreate(il005);
  for(;;);
  
  return 0;
}
