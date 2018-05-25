

#ifndef __G3_IO_LIB_H__
#define __G3_IO_LIB_H__


#ifdef WIN32
//#define G3_API extern "C" __declspec(dllexport)

#ifdef G3_IO_LIB_EXPORTS
#define G3_IO_LIB_API extern "C" __declspec(dllexport) 
#else
#define G3_IO_LIB_API  extern "C" __declspec(dllimport) 
#endif

//#ifdef __STDCALL__
//#define CALLTYPE __stdcall
//#else
//#define CALLTYPE
//#endif

#elif __linux__

//#define CALLTYPE

#ifdef __cplusplus 
#define G3_IO_LIB_API extern "C" 
#else
#define G3_IO_LIB_API
#endif 




#else
#error "NO DEFILE"
#endif


typedef enum
{
	G3_IO_IEB100_CDC = 0,
	G3_IO_IEVB100_FT4222 = 1,
	G3_IO_I2C_DEV = 2,

}  EN_G3_IO_LIB_TYPE;


typedef int(*PF_INIT_G3_IO_LIB)(void *param);
typedef int(*PF_WAKE_UP_AND_CONVERT_MODE)();
typedef void(*PF_END_G3_IO_LIB)();


typedef struct _tagST_G3_IO_LIB_FUNCTIONS{
	PF_INIT_G3_IO_LIB init_sample;
	PF_WAKE_UP_AND_CONVERT_MODE wake_up_and_convert_mode;
	PF_END_G3_IO_LIB end_sample;

}ST_G3_IO_LIB_FUNCTIONS, *LPST_G3_IO_LIB_FUNCTIONS;






G3_IO_LIB_API void get_functions(EN_G3_IO_LIB_TYPE en_g3_io_lib_type, LPST_G3_IO_LIB_FUNCTIONS lpsamplefunction);

#endif //__G3_IO_LIB_H__