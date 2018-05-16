
#ifndef __UTIL_H
#define __UTIL_H

#include "sample_def.h"
#include <g3_api.h>
#ifdef __cplusplus 
extern "C" { 
#endif 

VAR_BYTES* alloc_var_bytes_i2c(int size);
void print_result(const char * title, int ret);
void print_value(const char * title, const void *buff, int size);
void print_result_value(const char * title, int ret, const void *buff, int size);
void swap_bytes(void* value, int size);
#ifdef __cplusplus 
}
#endif 


#endif /*__UTIL_H*/
