
#ifndef __G3_DEFINE_HEADER__
#define __G3_DEFINE_HEADER__

#define NULL 0
//typedef int(*PFSENDRECV) (unsigned char *, int, void*);
//typedef const int(*PFSENDRECV) (unsigned char*, int, void*, SND_RECV_MODE mode);

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
//END ENUM






















































































































//START STRUCTURE

typedef struct _tagVAR_BYTES{
	int size;
	int allocsize;
	unsigned char buffer[1];;
}VAR_BYTES, *LPVAR_BYTES;

typedef struct _tagST_SIGN_ECDSA{
	unsigned char r[32];
	unsigned char s[32];;
}ST_SIGN_ECDSA, *LPST_SIGN_ECDSA;

typedef struct _tagST_SIGN_SYMM{
	unsigned char sign[16];;
}ST_SIGN_SYMM, *LPST_SIGN_SYMM;

typedef struct _tagST_SIGN_HMAC{
	unsigned char sign[32];;
}ST_SIGN_HMAC, *LPST_SIGN_HMAC;

typedef struct _tagST_ECC_PUBLIC{
	unsigned char puk[64];;
}ST_ECC_PUBLIC, *LPST_ECC_PUBLIC;

typedef struct _tagST_ECC_PUBLIC_COMPRESS{
	unsigned char puk[33];;
}ST_ECC_PUBLIC_COMPRESS, *LPST_ECC_PUBLIC_COMPRESS;

typedef struct _tagST_ECC_PRV{
	unsigned char prk[32];;
}ST_ECC_PRV, *LPST_ECC_PRV;

typedef struct _tagST_DIVERSIFY_PARAM{
	unsigned char param[16];;
}ST_DIVERSIFY_PARAM, *LPST_DIVERSIFY_PARAM;

typedef struct _tagST_KEY_VALUE{
	unsigned char key_value[32];;
}ST_KEY_VALUE, *LPST_KEY_VALUE;

typedef struct _tagST_IV{
	unsigned char iv[16];;
}ST_IV, *LPST_IV;

typedef struct _tagST_MAC{
	unsigned char mac[16];;
}ST_MAC, *LPST_MAC;

typedef struct _tagST_ECIES{
	unsigned char r[32];
	unsigned char s[16];;
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
//END STRUCTURE













typedef int(*PFTEST) (int, int);

//START TYPE_DEF
typedef int(*PFSENDRECV) (const unsigned char*,int,unsigned char*,int*,  void*etcparam );
typedef int G3_API_RESULT;
//END TYPE_DEF
















#endif//__G3_DEFINE_HEADER__


