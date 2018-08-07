


//#include <fcntl.h>				//Needed for I2C port
//#include <sys/ioctl.h>			//Needed for I2C port
//#include <linux/i2c-dev.h>		//Needed for I2C port
#include <stdio.h>

#include <stdlib.h>
#include <memory.h>
#include "g3_api.h"
#include "g3_io_lib.h"
//#include "neoCoLib.h"

#include "util.h"
#include "LibFT4222.h"
#include "neoDebug.h"

#include <errno.h>
#define GPIO_WAKE_UP_PIN 4


extern "C" int init_sample_ft4222(void *param);
extern "C" int wake_up_and_convert_mode_ft4222();
extern "C" void end_sample_ft4222();
extern "C" void get_functions_ft4222(LPST_G3_IO_LIB_FUNCTIONS lpsamplefunction);

ST_G3_IO_LIB_FUNCTIONS  _samplefunction_ft4222 = {
	init_sample_ft4222,
	wake_up_and_convert_mode_ft4222,
	end_sample_ft4222

};
typedef struct _tagDEVINO{
	int numdev;
	FT_DEVICE_LIST_INFO_NODE * a_devInfo;
	FT_DEVICE_LIST_INFO_NODE * b_devInfo;
	FT_DEVICE_LIST_INFO_NODE * orgalloc;

}DEVINO, *LPDEVINO;

DEVINO _devinfo;



void Disconnect(LPDEVINO lpdevinfo)
{

	if (lpdevinfo->a_devInfo->ftHandle){
		FT4222_UnInitialize(lpdevinfo->a_devInfo->ftHandle);
		FT_Close(lpdevinfo->a_devInfo->ftHandle);
	}

	if (lpdevinfo->b_devInfo->ftHandle){
		FT4222_UnInitialize(lpdevinfo->b_devInfo->ftHandle);
		FT_Close(lpdevinfo->b_devInfo->ftHandle);
	}
		

	//FT_Close(lpdevinfo->b_devInfo->ftHandle);

	//if (pdevInfo->ftHandle != (FT_HANDLE)NULL)
	//{
	//	(void)FT4222_UnInitialize(pdevInfo->ftHandle);
	//	(void)FT_Close(pdevInfo->ftHandle);
	//}

}

int Connect(LPDEVINO lpdevinfo)
{
	FT_STATUS            ftStatus;
	FT_DEVICE_LIST_INFO_NODE * a_devInfo = lpdevinfo->a_devInfo;
	FT_DEVICE_LIST_INFO_NODE * b_devInfo = lpdevinfo->b_devInfo;

	int ret = 0;
	if (lpdevinfo->numdev == 0)
		return -1;
	
	
	if (ftStatus= FT_Open(a_devInfo->LocId, &a_devInfo->ftHandle) != FT_OK){
		printf("FT_OpenEx failed (error %d)\n",
			(int)ftStatus);
		return  -1;
	}
		

	if (ftStatus = FT_Open(b_devInfo->LocId, &b_devInfo->ftHandle) != FT_OK){

		printf("FT_OpenEx failed (error %d)\n",
			(int)ftStatus);
		return  -1;

	}



	// enable gpio 2
	if (FT4222_SetSuspendOut(b_devInfo->ftHandle, false) != FT_OK)
	{
		ret = -1;
		goto end;

	}

	// enable gpio 3
	if (FT4222_SetWakeUpInterrupt(b_devInfo->ftHandle, false) != FT_OK)
	{
		ret = -1;
		goto end;

	}

	//FT4222_GPIO_SetInputTrigger(ftHandle, GPIO_PORT2, (GPIO_Trigger)(GPIO_TRIGGER_LEVEL_HIGH | GPIO_TRIGGER_LEVEL_LOW | GPIO_TRIGGER_RISING | GPIO_TRIGGER_FALLING));
	//FT4222_GPIO_SetInputTrigger(ftHandle, GPIO_PORT3, (GPIO_Trigger)(GPIO_TRIGGER_LEVEL_HIGH | GPIO_TRIGGER_LEVEL_LOW | GPIO_TRIGGER_RISING | GPIO_TRIGGER_FALLING));

	if (ret = FT4222_I2CMaster_Init(a_devInfo->ftHandle, 400) != FT_OK)
	{
	
		ret = -1;
		goto end;

	}

	GPIO_Dir gpioDir[4];
	gpioDir[0] = GPIO_INPUT;
	gpioDir[1] = GPIO_INPUT;
	gpioDir[2] = GPIO_OUTPUT;
	gpioDir[3] = GPIO_OUTPUT;

	if (FT4222_GPIO_Init(b_devInfo->ftHandle, gpioDir) != FT_OK)
	{
		ret = -1;
		goto end;
	}

end:
	return ret;
}

void Wakeup(FT_DEVICE_LIST_INFO_NODE * b_devInfo,int wakeupTime)
{
	FT4222_GPIO_Write(b_devInfo->ftHandle, GPIO_PORT2, 1);
	cur_sleep(wakeupTime);
	FT4222_GPIO_Write(b_devInfo->ftHandle, GPIO_PORT2, 0);
}

void Reset(FT_DEVICE_LIST_INFO_NODE * b_devInfo)
{
	FT4222_GPIO_Write(b_devInfo->ftHandle, GPIO_PORT3, 1);
	cur_sleep(100);
	FT4222_GPIO_Write(b_devInfo->ftHandle, GPIO_PORT3, 0);
}
#if 0
int exercise4222(LPDEVINO lpdevinfo)
{
	int                  success = 0;
	FT_STATUS            ftStatus;
	//FT_HANDLE            ftHandle = (FT_HANDLE)NULL;
	FT4222_STATUS        ft4222Status;
	FT4222_Version       ft4222Version;
	const uint16         slaveAddr = 0x64;
	uint16               bytesToRead;
	uint16               bytesRead = 0;
	uint16               bytesToWrite;
	uint16               bytesWritten = 0;
	char                *writeBuffer;
	uint8              pageBuffer[255];
	uint8              newContent[255];
	
	int                  page;



	ft4222Status = FT4222_GetVersion(lpdevinfo->a_devInfo->ftHandle,
		&ft4222Version);

	if (FT4222_OK != ft4222Status)
	{
		printf("FT4222_GetVersion failed (error %d)\n",
			(int)ft4222Status);
		goto exit;
	}

	printf("Chip version: %08X, LibFT4222 version: %08X\n",
		(unsigned int)ft4222Version.chipVersion,
		(unsigned int)ft4222Version.dllVersion);


	ft4222Status = FT4222_GetVersion(lpdevinfo->b_devInfo->ftHandle,
		&ft4222Version);

	if (FT4222_OK != ft4222Status)
	{
		printf("FT4222_GetVersion failed (error %d)\n",
			(int)ft4222Status);
		goto exit;
	}

	printf("Chip version: %08X, LibFT4222 version: %08X\n",
		(unsigned int)ft4222Version.chipVersion,
		(unsigned int)ft4222Version.dllVersion);
	

	unsigned char snd_buff[] = { 0x03, 0x07, 0x84, 0x20, 0x00, 0x00, 0x5F, 0x39, };
	ft4222Status = FT4222_I2CMaster_Write(lpdevinfo->a_devInfo->ftHandle,
		slaveAddr,
		snd_buff,
		sizeof(snd_buff),
		&bytesWritten);
	if (FT4222_OK != ft4222Status)
	{
		printf("FT4222_I2CMaster_Write 2 failed (error %d)\n",
			(int)ft4222Status);
		goto exit;
	}
	bytesToRead = 255;
	//Sleep(10);
	cur_sleep(100);

	ft4222Status = FT4222_I2CMaster_Read(lpdevinfo->a_devInfo->ftHandle,
		slaveAddr,
		newContent,
		bytesToRead,
		&bytesRead);
	if (FT4222_OK != ft4222Status)
	{
		printf("FT4222_I2CMaster_Read failed (error %d)\n",
			(int)ft4222Status);
		goto exit;
	}
	print_value("newContent",newContent,255);

#if 0

	// Reset the I2CM registers to a known state.
	ft4222Status = FT4222_I2CMaster_Reset(ftHandle);
	if (FT4222_OK != ft4222Status)
	{
		printf("FT4222_I2CMaster_Reset failed (error %d)!\n",
			ft4222Status);
		goto exit;
	}

	// Before reading EEPROM, set buffer to known content
	memset(originalContent, '!', EEPROM_BYTES);

	// Reset slave EEPROM's current word address counter.
	ft4222Status = setWordAddress(ftHandle,
		slaveAddr,
		0);
	if (FT4222_OK != ft4222Status)
	{
		goto exit;
	}

	// Sequential read from slave EEPROM's current word address.
	bytesToRead = _countof(originalContent);
	ft4222Status = FT4222_I2CMaster_Read(ftHandle,
		slaveAddr,
		originalContent,
		bytesToRead,
		&bytesRead);
	if (FT4222_OK != ft4222Status)
	{
		printf("FT4222_I2CMaster_Read failed (error %d)\n",
			(int)ft4222Status);
		goto exit;
	}

	if (bytesRead != bytesToRead)
	{
		printf("FT4222_I2CMaster_Read read %u of %u bytes.\n",
			bytesRead,
			bytesToRead);
		goto exit;
	}

	if (0 != memcmp(originalContent, slogan1, EEPROM_BYTES))
		writeBuffer = slogan1;
	else
		writeBuffer = slogan2;

	printf("Writing \"%.20s...\"\n", writeBuffer);

	for (page = 0; page < EEPROM_BYTES / BYTES_PER_PAGE; page++)
	{
		// First byte to write is address (in EEPROM) of first byte in page.
		pageBuffer[0] = page * BYTES_PER_PAGE;

		// Copy a page's worth of data into the rest of pageBuffer.
		memcpy(&pageBuffer[1],
			writeBuffer + page * BYTES_PER_PAGE,
			BYTES_PER_PAGE);

		bytesToWrite = BYTES_PER_PAGE + 1;
		ft4222Status = FT4222_I2CMaster_Write(ftHandle,
			slaveAddr,
			pageBuffer,
			bytesToWrite,
			&bytesWritten);
		if (FT4222_OK != ft4222Status)
		{
			printf("FT4222_I2CMaster_Write 2 failed (error %d)\n",
				(int)ft4222Status);
			goto exit;
		}

		if (bytesWritten != bytesToWrite)
		{
			printf("FT4222_I2CMaster_Write wrote %u of %u bytes.\n",
				bytesWritten,
				bytesToWrite);
			goto exit;
		}

		// Wait for EEPROM's write-cycle to complete.
		ft4222Status = pollAddressAck(ftHandle, slaveAddr);
		if (FT4222_OK != ft4222Status)
		{
			goto exit;
		}
	}

	memset(newContent, '!', EEPROM_BYTES);

	// Reset slave EEPROM's current word address counter.
	ft4222Status = setWordAddress(ftHandle,
		slaveAddr,
		0);
	if (FT4222_OK != ft4222Status)
	{
		goto exit;
	}

	// Sequential read from slave EEPROM's current word address.
	bytesToRead = _countof(newContent);
	ft4222Status = FT4222_I2CMaster_Read(ftHandle,
		slaveAddr,
		newContent,
		bytesToRead,
		&bytesRead);
	if (FT4222_OK != ft4222Status)
	{
		printf("FT4222_I2CMaster_Read failed (error %d)\n",
			(int)ft4222Status);
		goto exit;
	}

	if (bytesRead != bytesToRead)
	{
		printf("FT4222_I2CMaster_Read read %u of %u bytes.\n",
			bytesRead,
			bytesToRead);
		goto exit;
	}

	printf("\nOriginal content of EEPROM:\n");
	hexdump(originalContent, EEPROM_BYTES);

	printf("\nNew content of EEPROM:\n");
	hexdump(newContent, EEPROM_BYTES);
#endif // 0


	success = 1;
exit:
	return success;
}
#endif

int GetDeviceFT4222(LPDEVINO lpdevinfo)
{
	FT_STATUS                 ftStatus;
	FT_DEVICE_LIST_INFO_NODE *devInfo = NULL;
	DWORD                     numDevs = 0;
	int                       i;
	int                       retCode = 0;
	int                       found4222 = 0;
	//*ppdevInfo = NULL;

	ftStatus = FT_CreateDeviceInfoList(&numDevs);
	if (ftStatus != FT_OK)
	{
		printf("FT_CreateDeviceInfoList failed (error code %d)\n",
			(int)ftStatus);
		retCode = -10;
		goto exit;
	}

	if (numDevs == 0)
	{
		printf("No devices connected.\n");
		retCode = -20;
		goto exit;
	}

	/* Allocate storage */
	devInfo = (FT_DEVICE_LIST_INFO_NODE *)calloc((size_t)numDevs,
		sizeof(FT_DEVICE_LIST_INFO_NODE));
	if (devInfo == NULL)
	{
		printf("Allocation failure.\n");
		retCode = -30;
		goto exit;
	}
	
	


	/* Populate the list of info nodes */
	ftStatus = FT_GetDeviceInfoList(devInfo, &numDevs);
	if (lpdevinfo){
		lpdevinfo->orgalloc = devInfo;
		lpdevinfo->numdev = numDevs;
		lpdevinfo->a_devInfo = devInfo;
		lpdevinfo->b_devInfo = devInfo + 1;
	}

	if (ftStatus != FT_OK)
	{
		printf("FT_GetDeviceInfoList failed (error code %d)\n",
			(int)ftStatus);
		retCode = -40;
		goto exit;
	}

	for (i = 0; i < (int)numDevs; i++)
	{
		unsigned int devType = devInfo[i].Type;
		size_t       descLen;


		devInfo[i].LocId = i;

		if (devType == FT_DEVICE_4222H_0)
		{
			// In mode 0, the FT4222H presents two interfaces: A and B.
			descLen = strlen(devInfo[i].Description);

			if ('A' == devInfo[i].Description[descLen - 1])
			{
				// Interface A may be configured as an I2C master.
				printf("\nDevice %d is interface A of mode-0 FT4222H:\n",
					i);
				printf("  0x%08x  %s  %s %d\n",
					(unsigned int)devInfo[i].ID,
					devInfo[i].SerialNumber,
					devInfo[i].Description, devInfo[i].LocId);

	/*			exercise4222(devInfo[i].LocId);*/
			}
			else
			{
				// Interface B of mode 0 is reserved for GPIO.
				printf("Skipping interface B of mode-0 FT4222H.\n");
			}

			found4222++;
		}

		if (devType == FT_DEVICE_4222H_1_2)
		{
			// In modes 1 and 2, the FT4222H presents four interfaces but
			// none is suitable for I2C.
			descLen = strlen(devInfo[i].Description);

			printf("Skipping interface %c of mode-1/2 FT4222H.\n",
				devInfo[i].Description[descLen - 1]);

			found4222++;
		}

		if (devType == FT_DEVICE_4222H_3)
		{
			// In mode 3, the FT4222H presents a single interface.  
			// It may be configured as an I2C Master.
			printf("\nDevice %d is mode-3 FT4222H (single Master/Slave):\n",
				i);
			printf("  0x%08x  %s  %s\n",
				(unsigned int)devInfo[i].ID,
				devInfo[i].SerialNumber,
				devInfo[i].Description);
			//(void)exercise4222(devInfo[i].LocId);

			found4222++;
		}
	}

	if (!found4222)
		printf("No FT4222 found.\n");

exit:
	//free(devInfo);
	return retCode;
}



extern "C" int send_n_recv_4_ft4222(const unsigned char*snd, int snd_size, unsigned char*recv, int* recv_size, void*etcparam)
{
	int                  success = 0;
	FT_STATUS            ftStatus;
	//FT_HANDLE            ftHandle = (FT_HANDLE)NULL;
	FT4222_STATUS        ft4222Status;
	FT4222_Version       ft4222Version;
	const uint16         slaveAddr = 0x64;
	uint16               bytesToRead;
	uint16               bytesRead = 0;
	uint16               bytesToWrite;
	uint16               bytesWritten = 0;
	char                *writeBuffer;
	uint8              pageBuffer[255];
	uint8              newContent[255];

	int                  page;
	
	NEO_TITLE(send_n_recv_4_ft4222);
	success = 0;
	LPDEVINO lpdevinfo = (LPDEVINO)etcparam;


	ft4222Status = FT4222_I2CMaster_Write(lpdevinfo->a_devInfo->ftHandle,
		slaveAddr,
		(unsigned char*)snd,
		snd_size,
		&bytesWritten);
	if (FT4222_OK != ft4222Status)
	{
		printf("FT4222_I2CMaster_Write 2 failed (error %d)\n",
			(int)ft4222Status);
		success = -1;
		goto exit;
	}

	bytesToRead = *recv_size;
	//Sleep(10);
	cur_sleep(1);

	for (int i = 0; i < 200; i++) {

		ft4222Status = FT4222_I2CMaster_Read(lpdevinfo->a_devInfo->ftHandle,
			slaveAddr,
			recv,
			bytesToRead,
			&bytesRead);
		
		if (FT4222_OK == ft4222Status && recv[0] != 0xff){
			break;
		}

		cur_sleep(10);
			
		//if (recv[0] == 0xff &&   
		//cur_sleep(10);


	}
	if (FT4222_OK != ft4222Status)
	{
		printf("FT4222_I2CMaster_Read failed (error %d)\n",
			(int)ft4222Status);
		success = -1;
		goto exit;
	}

	*recv_size = bytesRead;
	print_value("recv", recv, 255);

	
exit:
	

	
	return success;


}


void get_functions_ft4222(LPST_G3_IO_LIB_FUNCTIONS lpsamplefunction)
{
	*lpsamplefunction = _samplefunction_ft4222;

}


int init_sample_ft4222(void *param)
{
	NEO_TITLE(init_sample_ft4222);

	
	
	
	
	DWORD                     numDevs = 0;
	int ret = GetDeviceFT4222(&_devinfo);
	//exercise4222(&devInfo[0]);
	ret = Connect(&_devinfo);
	g3api_set_user_send_recv_pf(send_n_recv_4_ft4222, &_devinfo);

	/*Wakeup(_devinfo.b_devInfo, 100);

	exercise4222(&_devinfo);*/



	return 0;


}
void end_sample_ft4222()
{
	NEO_TITLE(end_sample_ft4222);
	Disconnect(&_devinfo);

}

int wake_up_and_convert_mode_ft4222()
{

	Wakeup(_devinfo.b_devInfo, 1);
	
	return 0;




}