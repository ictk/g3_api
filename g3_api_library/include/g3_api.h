
#ifndef __G3_API_HEADER__
#define __G3_API_HEADER__

#include"g3_define.h"


#ifdef WIN32
#define G3_API extern "C" __declspec(dllexport)
#elif __linux__
#define G3_API 
#else
#error "NO DEFILE"
#endif

#define LIB_VERSION "1.0.0"

//START API
G3_API const char * g3api_get_lib_version();
G3_API void g3api_set_user_send_recv_pf( PFSENDRECV psendrecv, void * etcparam);
G3_API int g3api_get_device_version();
G3_API char* g3api_get_sn();
G3_API int g3api_setup_core( SETUP_CORE st_setup_fixed);
G3_API int g3api_set_up_keys( SET_UP_UNIT_ARRAY keys_configure);
G3_API int g3api_raw_snd_recv(const unsigned char * snd , int snd_size, unsigned char * recv, int* recv_size);
G3_API int g3api_write_key_value(const int key_index, RW_TYPE rw_type,const unsigned char * key_value, int key_value_size);
G3_API int g3api_read_key_value(const int key_index, RW_TYPE rw_type, unsigned char * key_value, int key_value_size);
G3_API int g3api_get_chellange( int chall_size, unsigned char * challenge, int* res_chall_size);
G3_API int g3api_verify_passwd(const int key_index,const unsigned char * passwd, int passwd_size);
G3_API int g3api_change_password(const int key_index,const unsigned char * passwd, int passwd_size);
G3_API int g3api_init_puf(const int key_index, unsigned int initial);
G3_API int g3api_sign(const int key_index, SIGN_OPTION ecdsa_option,const unsigned char * msg, int msg_size, void * sign_structure, int structure_size);
G3_API int g3api_verify(const int key_index, SIGN_OPTION ecdsa_option, bool is_use_cert,const unsigned char * msg, int msg_size,const void * sign_structure, int structure_size);
G3_API int g3api_verify_dynamic( int key_index, SIGN_OPTION ecdsa_option, bool is_use_cert,const unsigned char * challenge, int chall_size,const unsigned char * sign, int sign_size);
G3_API int g3api_encryption( int key_index, BLOCK_MODE block_mode,const unsigned char * data, int data_size, ST_IV * iv, unsigned char * cipher, int cipher_size);
G3_API int g3api_decryption( int key_index, BLOCK_MODE block_mode,const ST_IV * iv, unsigned char * cipher,const int cipher_size, unsigned char * data, int data_size);
G3_API int g3api_encryption_ecies( int key_index,const unsigned char * data, int data_size, ST_SIGN_ECDSA* rs);
G3_API int g3api_decryption_ecies( int key_index,const ST_SIGN_ECDSA* rs, unsigned char * data, int data_size);
G3_API int g3api_ecdh( int key_index,const void * Q_b, int Q_b_size, ST_ECC_PUBLIC* Q_chip, ST_ECC_PUBLIC* ecdh_value);
G3_API int g3api_session( int key_index);
G3_API int g3api_diversify( int key_index, DIVERSIFY_MODE diversify_mode, ST_DIVERSIFY_PARAM* param);
G3_API int g3api_get_public_key( int key_index, PUB_TYPE pub_type, void* pub_key, int structure_size);
G3_API int g3api_certification( int key_index, CERTIFICATION_WRITE_MODE certification_write_mode,const unsigned char * cert, int cert_size);
G3_API int g3api_issue_certification( int key_index,const unsigned char * cert, int cert_size);
G3_API int g3api_reset();
//END API


















#endif //__G3_API_HEADER__






