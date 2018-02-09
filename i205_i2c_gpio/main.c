#include "il005define.h"
#include "il005communication.h"
#include "i2c_sw.h"



int main(void)
{
  if(wiringPiSetup() == -1)
  	return 1;	

  i2c_init();  
 
  
  return 0;
}
