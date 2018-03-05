#ifndef __INTER_DEFINE_HEADER__
#define __INTER_DEFINE_HEADER__
#include "g3_define.h"


//typedef unsigned char byte 


//START STRUCTURE

#pragma pack(push, 1)

typedef struct _tagSECTOR{
	unsigned char first_byte;
	unsigned char second_byte;
	unsigned char ac[6];;
}SECTOR, *LPSECTOR;

typedef struct _tagHEADER_WRITE_PACKET{
	unsigned char  length;
	unsigned char  ins;
	unsigned char  p1;
	unsigned short  p2;;
}HEADER_WRITE_PACKET, *LPHEADER_WRITE_PACKET;

typedef struct _tagWRITE_PACKET{
	HEADER_WRITE_PACKET header;
	VAR_BYTES data;
	unsigned short  crc;;
}WRITE_PACKET, *LPWRITE_PACKET;
   
#pragma pack(pop)  
	//END STRUCTURE

















































































































#endif //__INTER_DEFINE_HEADER__