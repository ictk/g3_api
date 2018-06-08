
#include "CSerialRS232.h"
#include "neoCoLib.h"
#include "neoDebug.h"

#include "g3_io_lib.h"
#include "util.h"

#pragma warning(disable:4996)

extern FILE * _fp;

void cur_sleep(int wakeupTime){
	
	NCL::Sleep(wakeupTime);
}
void print_result(const char * title,int ret)
{
	fprintf(_fp,"\n%s ret:0x%x \n", title, ret);
}

void print_value(const char * title, const void *buff,int size)
{
	fprintf(_fp,"\n%s %s %d \n", title, NCL::BytetoHexStr(buff, size).c_str(), size);
}
void print_result_value(const char * title, int ret,const void *buff, int size)
{
	fprintf(_fp,"\n%s ret:0x%x\n%s %d \n", title, ret,NCL::BytetoHexStr(buff, size).c_str(), size);
}

void set_buff_from_hexstr(void *pbuff, const char *hexstr)
{
	VECBYTE vecbyte = NCL::HexStr2Byte(hexstr);
	memcpy(pbuff, V2A(vecbyte), vecbyte.size());
}


void swap_bytes(void* value, int size)
{
	unsigned char * pvalue = (unsigned char *)value;
	unsigned char * pnewvalue = (unsigned char *)malloc(size);

	for (int i = 0; i < size; i++){
		*(pnewvalue + size - 1 - i) = *(pvalue + i);
	}
	memcpy(value, pnewvalue, size);
	free(pnewvalue);

}

#define test

#ifdef test


void set_buffer_from_hexstr2(void *dest, char *src, int size)
{
	unsigned char * pvalue; *pvalue = *src;
	unsigned char * byte   = (unsigned char*)malloc(size);

	int pos = 0;
	int length = 0;

	while (*src != NULL)
	{
		pvalue++;
		length++;
	}
	printf("len : %d\n", length);

#if 1
	printf("set : \r\n");
	for (int i = 0; i < length / 2; i++)
	{
		sscanf(src + pos, "%2hhX", (byte + i));
		pos += 2;

		printf("%02X", *(byte + i));
	}
	printf("\n");

	memcpy((unsigned char*)dest, byte, size);

#endif
}

void int2hexbyte(unsigned char *dest, int int_value, int position)
{
	char hexstr[20], byte[20];

	sprintf(hexstr, "%X", int_value);
	sscanf(hexstr, "%2hhX", &byte);
	memcpy(dest + position, &byte, 1);
}

#endif
//
//VAR_BYTES* alloc_var_bytes_i2c(int size)
//{
//	VAR_BYTES*ret = (VAR_BYTES*)malloc(8 + size);
//	ret->allocsize = size;
//	ret->size = size;
//	memset(ret->buffer, 0, size);
//	return ret;
//}