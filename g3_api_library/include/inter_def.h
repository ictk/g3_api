
#include "g3_define.h"


//typedef unsigned char byte 


//START STRUCTURE
//END STRUCTURE
#pragma pack(push, 1)   
typedef struct _tagSECTOR{
	unsigned char first_byte;
	unsigned char second_byte;
	unsigned char ac[6];;
}SECTOR, *LPSECTOR;



typedef struct _tagHEADER_WRITE_PACKET{
	unsigned char  inst_flag;
	unsigned char  length;
	unsigned char  ins;
	unsigned char  p1;
	unsigned short  p2;;
}HEADER_WRITE_PACKET, *LPHEADER_WRITE_PACKET;

typedef struct _tagWRITE_PACKET{
	HEADER_WRITE_PACKET header;
	unsigned char data[2];;//CRC 를 위해 2바이트 할당
}WRITE_PACKET, *LPWRITE_PACKET;


typedef struct _tagHEADER_WRITE_IEB100_PACKET{
	unsigned char  rom_inst;
	unsigned unsigned long  body_size_big_end;//dummy+res_size+rom_type+data_size
	unsigned unsigned long  dummy;
	unsigned char  res_size;
	//unsigned char  rom_type;
}HEADER_WRITE_IEB100_PACKET, *LPHEADER_WRITE_IEB100_PACKET;

typedef struct _tagWRITE_IEB100_PACKET{
	HEADER_WRITE_IEB100_PACKET header;
	unsigned char data[1];;
}WRITE_IEB100_PACKET, *LPWRITE_IEB100_PACKET;

#pragma pack(pop)  







typedef LPVAR_BYTES(*PF_CONVERT)(void *pure_data, int data_size);


#define	READ	0x80
#define	WRITE	0x81
#define	VERIFY_PWD	0x82
#define	CHANGE_PWD	0x83
#define	GET_CHAL	0x84
#define	INIT_PRIV_KEY	0x85
#define	SIGN	0x86
#define	VERIFY	0x87
#define	ENCRYPT	0x88
#define	DECRYPT	0x89
#define	SESSION	0x8A
#define	DIVERSIFY	0x8B
#define	GET_PUB_KEY	0x8C
#define	CERT	0x8D
#define	ISSUE_CERT	0x8E
#define	RESET	0x9F

#define	RET_SUCCESS	0x00

#define ERR_GENERAL 0x80000000
#define ERR_INTERCHIP 0xF0000000



#define ERR_RECV_BUFF_SIZE ERR_GENERAL|0xF0
#define ERR_KEY_BUFF_SIZE ERR_GENERAL|0xF1
#define ERR_RECV_CRC_ERROR  ERR_GENERAL|0xF2
#define ERR_SIGN_MODE_PARSE_ERR  ERR_GENERAL|0xF3
#define ERR_DIFF_STRUCT_SIZE  ERR_GENERAL|0xF4
#define ERR_RECV_ALLOC_ERROR  ERR_GENERAL|0xF5




#define	ERR_INTERCHIP_VERIFY_ERROR	ERR_INTERCHIP|0x01
#define	ERR_INTERCHIP_PARSE_ERROR	ERR_INTERCHIP|0x03
#define	ERR_INTERCHIP_EXECUTION_ERROR	ERR_INTERCHIP|0x0F
#define	ERR_INTERCHIP_AFTER_WAKE_UP	ERR_INTERCHIP|0x11
#define	ERR_INTERCHIP_COMMUNICATIONS_ERROR	ERR_INTERCHIP|0xFF
#define	ERR_INTERCHIP_ABNORMAL_INPUT_DETECTION	ERR_INTERCHIP|0x21


#define MAKEWORD(l_,h_)   ((unsigned short)(((unsigned char)(l_))|(((unsigned short)((unsigned char)(h_)))<<8)))
//#define MAKEWORD_BIG(l_,h_)   ((unsigned short)(((unsigned char)(h_))|(((unsigned short)((unsigned char)(l_)))<<8)))
#define KEY_VALUE_SIZE 32

#ifndef min
#define min(a,b)    (((a) < (b)) ? (a) : (b))
#endif