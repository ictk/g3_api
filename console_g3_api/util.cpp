
#include "CSerialRS232.h"
#include "neoCoLib.h"
#include "neoDebug.h"
#include "g3_api.h"
#include "sample_def.h"
extern FILE * _fp;

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
VAR_BYTES* alloc_var_bytes_i2c(int size)
{
	VAR_BYTES*ret = (VAR_BYTES*)malloc(8 + size);
	ret->allocsize = size;
	ret->size = size;
	memset(ret->buffer, 0, size);
	return ret;
}