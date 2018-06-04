// g3_io_lib.cpp : DLL 응용 프로그램을 위해 내보낸 함수를 정의합니다.
//

#include "g3_io_lib.h"


// 내보낸 변수의 예제입니다.
G3_IO_LIB_API int ng3_io_lib=0;

extern "C" void get_functions_ieb100cdc(LPST_G3_IO_LIB_FUNCTIONS lpsamplefunction);
extern "C" void get_functions_i2c(LPST_G3_IO_LIB_FUNCTIONS lpsamplefunction);
extern "C" void get_functions_ft4222(LPST_G3_IO_LIB_FUNCTIONS lpsamplefunction);


// 내보낸 함수의 예제입니다.


//###################################################	
/**
*   @brief	Selects get_functions according to g3_io_lib_type
*	@param	en_g3_io_lib_type	: G3_IO_LIB_TYPE
*								  It can be one of the following values :
*									@arg	G3_IO_IEB100_CDC
*									@arg	G3_IO_IEVB100_FT4222
*									@arg	G3_IO_I2C_DEV
*	@param	lpsamplefunction	: Pointer to a ST_G3_IO_LIB_FUNCTIONS structure that contains functions to initialize the device
*								
*   @return void
*/
//###################################################
G3_IO_LIB_API void get_functions(EN_G3_IO_LIB_TYPE en_g3_io_lib_type,LPST_G3_IO_LIB_FUNCTIONS lpsamplefunction)
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
