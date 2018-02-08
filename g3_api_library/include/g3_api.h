
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
G3_API int g3api_write_key_value(const int key_index, AREA_TYPE area_type, RW_TYPE rw_type,const unsigned char * key_value, int key_value_size);
G3_API int g3api_read_key_value(const int key_index, AREA_TYPE area_type, RW_TYPE rw_type, unsigned char * key_value, int* key_value_size);
G3_API int g3api_get_chellange( int chall_size, unsigned char * challenge, int* res_chall_size);
G3_API int g3api_verify_passwd(const int key_index,const unsigned char * passwd, int passwd_size);
G3_API int g3api_change_password(const int key_index,const unsigned char * passwd, int passwd_size);
G3_API int g3api_init_puf(const int key_index, unsigned int initial);
G3_API int g3api_sign(const int key_index, SIGN_OPTION sign_option,const unsigned char * msg, int msg_size, void * sign_structure, int structure_size);
G3_API int g3api_verify(const int key_index, VERIFY_OPTION verify_option,const unsigned char * msg, int msg_size,const void * sign_structure, int structure_size);
G3_API int g3api_dynamic_auth( int key_index, DYNAMIC_AUTH dauth_option, int pos_pub_dynamic,const unsigned char * msg, int msg_size,const void * sign_structure, int structure_size);
G3_API int g3api_encryption( int key_index, BLOCK_MODE block_mode,const unsigned char * data, int data_size, ST_IV * iv, unsigned char * cipher, int* cipher_size);
G3_API int g3api_decryption( int key_index, BLOCK_MODE block_mode,const ST_IV * iv, unsigned char * cipher,const int cipher_size, unsigned char * data, int* data_size);
G3_API int g3api_encryption_ecies( int key_index,const unsigned char * data, int data_size, ST_SIGN_ECDSA* rs);
G3_API int g3api_decryption_ecies( int key_index,const ST_SIGN_ECDSA* rs, unsigned char * data, int data_size);
G3_API int g3api_ecdh( int key_index,const void * Q_b, int Q_b_size, ST_ECC_PUBLIC* Q_chip, ST_ECC_PUBLIC* ecdh_value);
G3_API int g3api_session( int key_index);
G3_API int g3api_diversify( int key_index, DIVERSIFY_MODE diversify_mode, ST_DIVERSIFY_PARAM* param);
G3_API int g3api_get_public_key( int key_index, PUB_TYPE pub_type, void* pub_key, int structure_size);
G3_API int g3api_certification( int key_index, CERTIFICATION_WRITE_MODE certification_write_mode,const unsigned char * cert, int cert_size);
G3_API int g3api_issue_certification( int key_index, int public_key_pos, ISSUE_CERT_AREA_TYPE issue_cert_area_type, int sector_num_to_store, int key_id,const unsigned char * cert, int cert_size);
G3_API int g3api_reset();
G3_API int g3api_test(const unsigned char * in, int in_size);
G3_API int g3api_test2( unsigned char * out, int* out_size);
G3_API int g3api_test3( ST_ECC_PUBLIC* param);
G3_API int g3api_test4( PFTEST pfsend);
G3_API int g3api_test5( PFSENDRECV pfsend);
G3_API int g3api_test6(const unsigned char * in, int in_size, PFSENDRECV pfsend);
G3_API int g3api_test7(const unsigned char * in, int in_size);
G3_API int g3api_test8( PFSENDRECV pfsend,const unsigned char * in, int in_size);
//END API



G3_API int GetSoftwareVersion(
	char* LCP_Version,
	char* FCP_Version
	);





























































































#endif //__G3_API_HEADER__






