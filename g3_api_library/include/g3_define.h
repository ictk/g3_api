
#ifndef __G3_DEFINE_HEADER__
#define __G3_DEFINE_HEADER__



//START DEFINE
#define LIB_VERSION  "1.0.0"

#define RET_SUCCESS 0x00
#define ERR_GENERAL 0x80000000
#define ERR_INTERCHIP 0xF0000000

#define RET_ERR_RECV_BUFF_SIZE ERR_GENERAL|0xF0
#define RET_ERR_KEY_BUFF_SIZE ERR_GENERAL|0xF1
#define RET_ERR_RECV_CRC_ERROR ERR_GENERAL|0xF2
#define RET_ERR_SIGN_MODE_PARSE_ERR ERR_GENERAL|0xF3
#define RET_ERR_DIFF_STRUCT_SIZE ERR_GENERAL|0xF4
#define RET_ERR_RECV_ALLOC_ERROR ERR_GENERAL|0xF5

#define RET_ERR_INTERCHIP_VERIFY_ERROR ERR_INTERCHIP|0x01
#define RET_ERR_INTERCHIP_PARSE_ERROR ERR_INTERCHIP|0x03
#define RET_ERR_INTERCHIP_EXECUTION_ERROR ERR_INTERCHIP|0x0F
#define RET_ERR_INTERCHIP_AFTER_WAKE_UP ERR_INTERCHIP|0x11
#define RET_ERR_INTERCHIP_COMMUNICATIONS_ERROR ERR_INTERCHIP|0xFF
#define RET_ERR_INTERCHIP_ABNORMAL_INPUT_DETECTION ERR_INTERCHIP|0x21

#define NULL 0
#define IN 
#define OUT 
#define INOUT 
//END DEFINE


//START ENUM

enum EN_SND_RECV_MODE  
{
	SND_N_RECV=0,
	SND=1,
	RECV=2,	 
};   	

enum EN_AND_OR  
{
	AND=0,
	OR=1,	 
};   	

enum EN_FORBIDDEN_TYPE  
{
	CONDITION=0,
	FREE=1,
	FORBIDDEN=2,	 
};   	

enum EN_RW   
{
	ALL=0,
	MASK_N_ENC =1,
	ENC=2,
	ENC_MAC=3,	 
};   	

enum EN_DATA_SECTOR_TYPE  
{
	VOID=0,
	ECC_PUF=1,
	ECC_PRV=2,
	ECC_PUB=3,
	AES128=4,
	AES256=5,
	SM4=6,
	SHA256=7,
	PASSWORD=8,
	DATA=9,
	COUNTER=10,	 
};   	

enum EN_RESULT  
{
	SUCCESS=0,
	FAIL=-1,	 
};   	

enum EN_DIVERSIFY_MODE  
{
	INHERIT=0,
	SELF=1,	 
};   	

enum EN_BLOCK_MODE  
{
	BL_CBC=0,
	BL_CTR=1,
	BL_GCM=3,	 
};   	

enum EN_CERTIFICATION_WRITE_MODE  
{
	TO_TEMP=0,
	TO_KEY_SECTOR=1,	 
};   	

enum EN_SIGN_OPTION  
{
	SIGN_ECDSA=0,
	SIGN_ECDSA_SHA256=1,
	SIGN_HMAC=2,
	SIGN_SYMM=3,	 
};   	

enum EN_VERIFY_OPTION  
{
	VERYFY_ECDSA=0,
	VERYFY_ECDSA_SHA256=1,
	VERYFY_HMAC=2,
	VERYFY_SYMM=3,
	VERYFY_CERT_PUB_ECDSA=0x10,
	VERYFY_CERT_PUB_ECDSA_SHA256=0x11,	 
};   	

enum EN_DYNAMIC_AUTH  
{
	DYN_AUTH_ECDSA_SHA256=0x21,
	DYN_AUTH_HMAC=0x22,
	DYN_AUTH_SYMM=0x23,
	DYN_AUTH_CERT_PUB_ECDSA_SHA256=0x31,	 
};   	

enum EN_VERIFY_TYPE  
{
	USE_CERT_PUB_ECDSA=0,
	USE_CERT_PUB_ECDSA_WITH_SHA256=1,	 
};   	

enum EN_AREA_TYPE  
{
	SETUP_AREA=0,
	KEY_AREA=1,
	DATA_AREA_0=2,
	DATA_AREA_1=3,	 
};   	

enum EN_RW_INST_OPTION  
{
	PLAIN_TEXT=0,
	CBC=1,
	CTR=2,
	CCM=3,
	GCM=4,
	SESSION_KEY_CBC=0x11,
	SESSION_KEY_CTR=0x12,
	SESSION_KEY_CCM=0x13,
	SESSION_KEY_GCM=0x14,
	MASKED=0xFF,	 
};   	

enum EN_PUB_TYPE  
{
	KEY_SECTOR=0,
	TEMP_PUBLIC_KEY=1,	 
};   	

enum EN_ISSUE_CERT_AREA_TYPE  
{
	ISCRT_KEY_AREA=0,
	ISCRT_DATA_AREA_0=1,
	ISCRT_DATA_AREA_1=2,	 
};   	

enum EN_CONTENT_TYPE  
{
	CHANGE_CIPHER_SPEC=20,
	ALERT=21,
	HANDSHAKE=22,
	APPLICATION_DATA=23,	 
};   	

enum EN_TLS_VERSION  
{
	SSL_3_0=0x0300,
	TLS_1_0=0x0301,
	TLS_1_1=0x0302,
	TLS_1_2=0x0303,	 
};   	

enum EN_ECDH_MODE  
{
	NORMAL_ECDH=0x0000,
	GEN_TLS_BLOCK=0x0011,
	SET_TLS_SESSION_KEY=0x0012,	 
};   	
//END ENUM





typedef int(*PFTEST) (int, int);

//START TYPE_DEF

typedef unsigned int dword;
typedef unsigned short word;
typedef unsigned char byte;

typedef int(*PFSENDRECV) (const unsigned char*,int,unsigned char*,int*,  void*etcparam );
typedef int G3_API_RESULT;
//END TYPE_DEF




//START STRUCTURE

#pragma pack(push, 1)

typedef struct _tagVAR_BYTES{
	int size;
	int allocsize;
	byte buffer[1];;
}VAR_BYTES, *LPVAR_BYTES;

typedef struct _tagST_SIGN_ECDSA{
	byte r[32];
	byte s[32];;
}ST_SIGN_ECDSA, *LPST_SIGN_ECDSA;

typedef struct _tagST_SIGN_SYMM{
	byte sign[16];;
}ST_SIGN_SYMM, *LPST_SIGN_SYMM;

typedef struct _tagST_SIGN_HMAC{
	byte sign[32];;
}ST_SIGN_HMAC, *LPST_SIGN_HMAC;

typedef struct _tagST_ECC_PUBLIC{
	byte puk[64];;
}ST_ECC_PUBLIC, *LPST_ECC_PUBLIC;

typedef struct _tagST_ECC_PUBLIC_COMPRESS{
	byte puk[33];;
}ST_ECC_PUBLIC_COMPRESS, *LPST_ECC_PUBLIC_COMPRESS;

typedef struct _tagST_ECC_PRV{
	byte prk[32];;
}ST_ECC_PRV, *LPST_ECC_PRV;

typedef struct _tagST_DIVERSIFY_PARAM{
	byte param[16];;
}ST_DIVERSIFY_PARAM, *LPST_DIVERSIFY_PARAM;

typedef struct _tagST_KEY_VALUE{
	byte key_value[32];;
}ST_KEY_VALUE, *LPST_KEY_VALUE;

typedef struct _tagST_IV{
	byte iv[16];;
}ST_IV, *LPST_IV;

typedef struct _tagST_RW_DATA{
	byte data[32];;
}ST_RW_DATA, *LPST_RW_DATA;

typedef struct _tagST_RW_DATA_WITH_IV{
	byte data[32];
	byte iv[16];;
}ST_RW_DATA_WITH_IV, *LPST_RW_DATA_WITH_IV;

typedef struct _tagST_RW_DATA_WITH_IV_MAC{
	byte data[32];
	byte iv[16];
	byte mac[16];;
}ST_RW_DATA_WITH_IV_MAC, *LPST_RW_DATA_WITH_IV_MAC;

typedef struct _tagST_ECIES{
	byte r[64];
	byte s[32];;
}ST_ECIES, *LPST_ECIES;

typedef struct _tagST_AC_CONDITION{
	EN_AND_OR and_or;
	EN_FORBIDDEN_TYPE forbidden_type;
	short key_number[2];;
}ST_AC_CONDITION, *LPST_AC_CONDITION;

typedef struct _tagST_KEY_SECTOR{
	EN_DATA_SECTOR_TYPE data_sector_type;
	EN_RW rw;
	ST_AC_CONDITION ac_cond[3];;
}ST_KEY_SECTOR, *LPST_KEY_SECTOR;

typedef struct _tagST_SETUP_CORE{
	ST_KEY_SECTOR root;
	ST_KEY_SECTOR data_0;
	ST_KEY_SECTOR data_1;;
}ST_SETUP_CORE, *LPST_SETUP_CORE;

typedef struct _tagST_SET_UP_VALUE{
	int setup_sector_index;
	ST_KEY_SECTOR key_sector;
	ST_KEY_VALUE value;
	EN_RESULT result_setup_area;
	EN_RESULT result_write_value;;
}ST_SET_UP_VALUE, *LPST_SET_UP_VALUE;

typedef struct _tagST_ECDH_PRE_MASTER_SECRET{
	byte pre_master_secret[32];;
}ST_ECDH_PRE_MASTER_SECRET, *LPST_ECDH_PRE_MASTER_SECRET;

typedef struct _tagST_ECDH_KEY_BLOCK{
	byte client_mac_key[32];
	byte server_mac_key[32];
	byte client_key[16];
	byte server_key[16];
	byte client_iv[16];
	byte server_iv[16];;
}ST_ECDH_KEY_BLOCK, *LPST_ECDH_KEY_BLOCK;

typedef struct _tagST_ECDH_IV{
	byte client_iv[16];
	byte server_iv[16];;
}ST_ECDH_IV, *LPST_ECDH_IV;

typedef struct _tagST_ECDH_RANDOM{
	byte server[32];
	byte client[32];;
}ST_ECDH_RANDOM, *LPST_ECDH_RANDOM;
   
#pragma pack(pop)  
	//END STRUCTURE


#endif//__G3_DEFINE_HEADER__


