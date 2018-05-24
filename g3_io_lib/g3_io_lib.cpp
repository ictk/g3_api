// g3_io_lib.cpp : DLL ���� ���α׷��� ���� ������ �Լ��� �����մϴ�.
//

#include "stdafx.h"
#include "g3_io_lib.h"


// ������ ������ �����Դϴ�.
G3_IO_LIB_API int ng3_io_lib=0;

extern "C" void get_functions_ieb100cdc(LPPF_G3_IO_LIB_FUNCTIONS lpsamplefunction);
extern "C" void get_functions_i2c(LPPF_G3_IO_LIB_FUNCTIONS lpsamplefunction);
extern "C" void get_functions_ft4222(LPPF_G3_IO_LIB_FUNCTIONS lpsamplefunction);


// ������ �Լ��� �����Դϴ�.
G3_IO_LIB_API void get_functions(EN_G3_IO_LIB_TYPE en_g3_io_lib_type,LPPF_G3_IO_LIB_FUNCTIONS lpsamplefunction)
{
	switch (en_g3_io_lib_type){
	case G3_IO_IEB100_CDC:
		get_functions_ieb100cdc(lpsamplefunction);
		break;
	case G3_IO_IEVB100_FT4222:
		get_functions_ft4222(lpsamplefunction);
		break;
	case G3_IO_I2C_DEV:
#ifndef WIN32
		get_functions_i2c(lpsamplefunction);
#endif
		break;

	}
	
}
