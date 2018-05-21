

#include <unistd.h>				//Needed for I2C port
//#include <fcntl.h>				//Needed for I2C port
//#include <sys/ioctl.h>			//Needed for I2C port
//#include <linux/i2c-dev.h>		//Needed for I2C port
#include <stdio.h>
#include <wiringPi.h>
#include <wiringPiI2C.h>
#include <stdlib.h>
#include <memory.h>
#include "g3_api.h"
#include "sample_def.h"
#include "neoDebug.h"
#include "util.h"

#include <errno.h>
#define GPIO_WAKE_UP_PIN 4

int _file_i2c = 0;
extern "C" int init_sample_i2c(void *param);
extern "C" int wake_up_and_convert_mode_i2c();
extern "C" void end_sample_i2c();
extern "C" void get_functions_i2c(LPSAMPLE_FUNCTIONS lpsamplefunction);

SAMPLE_FUNCTIONS  _samplefunction_i2c = {
	init_sample_i2c,
	wake_up_and_convert_mode_i2c,
	end_sample_i2c

};

void wake_up(int pin_num,int f_sleep_time,int s_sleep_time){
	NEO_TITLE(wake_up);
	
	pinMode(pin_num, OUTPUT);
	printf("%d %d \n",f_sleep_time,s_sleep_time);
	int st = millis();
	delay(s_sleep_time);
	printf("tktime: %d %d \n",millis()-st,st);
	

	digitalWrite(pin_num, HIGH);
	digitalWrite(pin_num, LOW);
	delay(f_sleep_time);
	digitalWrite(pin_num, HIGH);
	delay(s_sleep_time);
	//digitalWrite(pin_num, LOW);
	pinMode(pin_num, INPUT);
}

int send(int file_i2c, const char * title,unsigned char *snd_buff,int length){
	//print_bytes(title,snd_buff,length);
	int ret = write(file_i2c, snd_buff, length);
	if (ret != length)		
	{
		/* ERROR HANDLING: i2c transaction failed */
		printf("Failed to write to the i2c bus. %d \n",ret);
		return -1;
	}
	return ret;
}
int ictk_convert_to_inst_mode(int file_i2c){
	NEO_TITLE(ictk_convert_to_inst_mode);
	int i = 0;
	unsigned char list_convert_invoke[3][11] = {
			{0x0E,0xFF,0x05,0x00,0x00,0x1C,0x55,0x11,0xEA,0xCC,0x00},
			{0x0E,0xFF,0x05,0x00,0x00,0x14,0x00,0x00,0x00,0xFF,0x00},
			{0x0E,0xFF,0x01,0x00,0x17,0x78,0x00,0x04,0x10,0x00,0x00}
	};
	
	for(i =0 ; i <3;i++){
		int length = 11;
		
		int ret = write(file_i2c, list_convert_invoke[i], length);
		if (ret != length)		
		{
			/* ERROR HANDLING: i2c transaction failed */
			printf("Failed to write to the i2c bus. %d \n",ret);
			return -1;
		}

		
	}
	return 0;
}

extern "C" int send_n_recv_4_i2c(const unsigned char*snd, int snd_size, unsigned char*recv, int* recv_size, void*etcparam)
{
	NEO_TITLE(send_n_recv_4_i2c);
	
	int file_i2c;
	memcpy(&file_i2c,etcparam,4);
	NEO_DWORD(file_i2c);
	if(file_i2c <0){
		
		return -1;
	}

	
	
	print_value("SND",snd, snd_size);
	
	//unsigned char buffer[256];
	int ret = write(file_i2c, (void*)snd, snd_size);
	if (ret != snd_size)		
	{
		/* ERROR HANDLING: i2c transaction failed */
		printf("Failed to write to the i2c bus. %d \n",ret);
		return -1;
	}
	delay(100);
	int length = * recv_size;			//<<< Number of bytes to read
	ret = read(file_i2c, recv, length);
	
	
	if (ret != length)		//read() returns the number of bytes actually read, if it doesn't match then an error occurred (e.g. no response from the device)
	{
		//ERROR HANDLING: i2c transaction failed
		printf("Failed to read from the i2c bus ret:0x%x. err:0x%x\n",ret,errno);
		return -1;
	}
	print_value("RECV",recv, length);
	*recv_size = ret;
	return 0;
	
	
}


void get_functions_i2c(LPSAMPLE_FUNCTIONS lpsamplefunction)
{
	*lpsamplefunction = _samplefunction_i2c;

}


int init_sample_i2c(void *param)
{
	NEO_TITLE(init_sample_i2c);
	wiringPiSetup(); // Initializes wiringPi using wiringPi's simlified number system.
	wiringPiSetupGpio(); // Initializes wiringPi using the Broadcom GPIO pin numbers
	wake_up_and_convert_mode_i2c();
	
	_file_i2c = wiringPiI2CSetup (100);
	printf("wiringPiI2CSetup %d\n",_file_i2c);
	NEO_DWORD(_file_i2c);
	g3api_set_user_send_recv_pf(send_n_recv_4_i2c, &_file_i2c);
	
	


	return 0;


}
void end_sample_i2c()
{
	NEO_TITLE(end_sample_i2c);
}

int wake_up_and_convert_mode_i2c()
{
	unsigned char snd_buff[] = {0x00};
	unsigned char recv_buff[4] = {0x00,};
	unsigned char cmp_recv_buff[4] = {0x04,0x11,0x33,0x43};
	int size_recv = 4;
	
	
	NEO_TITLE(wake_up_and_convert_mode_i2c);
	printf("wake_up_and_convert_mode_i2c\n");
	
  
  
	int i2c = wiringPiI2CSetup (0);
  write(i2c,snd_buff,1);
  delay(20);
  
  int ret = read(i2c, recv_buff, size_recv);
	printf("read result: %d", ret);
	print_value("Wake-up Response",recv_buff, size_recv);

  
  return 0;
	wake_up(GPIO_WAKE_UP_PIN,1,10);	
	
	return ictk_convert_to_inst_mode(_file_i2c);
	
	

}