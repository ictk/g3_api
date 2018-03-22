
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

//#define LIB_VERSION "1.0.0"
G3_API void g3api_set_fp(void *fp);
//START API

//###################################################	
/**
*   @name g3api_get_lib_version
*   @brief  
*

*   @return const char *
*/
//###################################################
G3_API const char * g3api_get_lib_version
(
);

	
//###################################################	
/**
*   @name g3api_set_user_send_recv_pf
*   @brief  
*
*   @param psendrecv 
*   @param etcparam 

*   @return void
*/
//###################################################
G3_API void g3api_set_user_send_recv_pf
(
		IN PFSENDRECV psendrecv,
		IN void* etcparam
);

	
//###################################################	
/**
*   @name g3api_get_device_version
*   @brief  
*

*   @return G3_API_RESULT
*/
//###################################################
G3_API G3_API_RESULT g3api_get_device_version
(
);

	
//###################################################	
/**
*   @name g3api_get_sn
*   @brief  
*

*   @return char*
*/
//###################################################
G3_API char* g3api_get_sn
(
);

	
//###################################################	
/**
*   @name g3api_raw_snd_recv
*   @brief  
*
*   @param snd  
*   @param snd_size 
*   @param recv 
*   @param recv_size 

*   @return G3_API_RESULT
*/
//###################################################
G3_API G3_API_RESULT g3api_raw_snd_recv
(
		IN const byte* snd ,
		IN int snd_size,
		OUT byte* recv,
		OUT int* recv_size
);

	
//###################################################	
/**
*   @name g3api_setup_core
*   @brief  
*
*   @param st_setup_fixed 

*   @return G3_API_RESULT
*/
//###################################################
G3_API G3_API_RESULT g3api_setup_core
(
		INOUT ST_SETUP_CORE* st_setup_fixed
);

	
//###################################################	
/**
*   @name g3api_set_up_keys
*   @brief  
*
*   @param array_set_up_value 
*   @param array_size 

*   @return G3_API_RESULT
*/
//###################################################
G3_API G3_API_RESULT g3api_set_up_keys
(
		INOUT ST_SET_UP_VALUE* array_set_up_value,
		IN int array_size
);

	
//###################################################	
/**
*   @name g3api_read_key_value
*   @brief  
*
*   @param key_index key sector index
*   @param area_type 
*   @param rw_type 
*   @param data_structure read value from setup,key_sector,user data
enable 4 follow structure ST_RW_DATA,ST_RW_DATA_WITH_IV,ST_RW_DATA_WITH_IV_MAC
*   @param structure_size 

*   @return G3_API_RESULT
*/
//###################################################
G3_API G3_API_RESULT g3api_read_key_value
(
		IN int key_index,
		IN EN_AREA_TYPE area_type,
		IN EN_RW_INST_OPTION rw_type,
		IN void* data_structure,
		IN int structure_size
);

	
//###################################################	
/**
*   @name g3api_write_key_value
*   @brief  
*
*   @param key_index key sector index
*   @param area_type 
*   @param rw_type 
*   @param data_structure write value to setup,key_sector,user data
enable 4 follow structure ST_RW_DATA,ST_RW_DATA_WITH_IV,ST_RW_DATA_WITH_IV_MAC
*   @param structure_size 

*   @return G3_API_RESULT
*/
//###################################################
G3_API G3_API_RESULT g3api_write_key_value
(
		IN int key_index,
		IN EN_AREA_TYPE area_type,
		IN EN_RW_INST_OPTION rw_type,
		IN const void* data_structure,
		IN int structure_size
);

	
//###################################################	
/**
*   @name g3api_get_chellange
*   @brief  
*
*   @param chall_size 
*   @param challenge 
*   @param res_chall_size 

*   @return G3_API_RESULT
*/
//###################################################
G3_API G3_API_RESULT g3api_get_chellange
(
		IN int chall_size,
		OUT byte* challenge,
		INOUT int* res_chall_size
);

	
//###################################################	
/**
*   @name g3api_verify_passwd
*   @brief  
*
*   @param key_index key sector index
*   @param passwd 
*   @param passwd_size 

*   @return G3_API_RESULT
*/
//###################################################
G3_API G3_API_RESULT g3api_verify_passwd
(
		IN int key_index,
		IN const byte* passwd,
		IN int passwd_size
);

	
//###################################################	
/**
*   @name g3api_change_password
*   @brief  
*
*   @param key_index key sector index
*   @param passwd 
*   @param passwd_size 

*   @return G3_API_RESULT
*/
//###################################################
G3_API G3_API_RESULT g3api_change_password
(
		IN int key_index,
		IN const byte* passwd,
		IN int passwd_size
);

	
//###################################################	
/**
*   @name g3api_init_puf
*   @brief  
*
*   @param key_index key sector index
*   @param initial 

*   @return G3_API_RESULT
*/
//###################################################
G3_API G3_API_RESULT g3api_init_puf
(
		IN int key_index,
		IN unsigned int initial
);

	
//###################################################	
/**
*   @name g3api_sign
*   @brief  
*
*   @param key_index key sector index
*   @param sign_option 
*   @param msg 
*   @param msg_size 
*   @param sign_structure enable 4 follow structure ST_SIGN_ECDSA,ST_SIGN_SYMM,ST_SIGN_HMAC
*   @param structure_size 

*   @return G3_API_RESULT
*/
//###################################################
G3_API G3_API_RESULT g3api_sign
(
		IN int key_index,
		IN EN_SIGN_OPTION sign_option,
		IN const byte* msg,
		IN int msg_size,
		OUT void * sign_structure,
		IN int structure_size
);

	
//###################################################	
/**
*   @name g3api_verify
*   @brief  
*
*   @param key_index key sector index
*   @param verify_option 
*   @param msg 
*   @param msg_size 
*   @param sign_structure enable 4 follow structure ST_SIGN_ECDSA,ST_SIGN_SYMM,ST_SIGN_HMAC
*   @param structure_size 

*   @return G3_API_RESULT
*/
//###################################################
G3_API G3_API_RESULT g3api_verify
(
		IN int key_index,
		IN EN_VERIFY_OPTION verify_option,
		IN const byte* msg,
		IN int msg_size,
		IN const void* sign_structure,
		IN int structure_size
);

	
//###################################################	
/**
*   @name g3api_dynamic_auth
*   @brief  
*
*   @param key_index key sector index
*   @param dauth_option 
*   @param pos_pub_dynamic 
*   @param msg 
*   @param msg_size 
*   @param sign_structure enable 4 follow structure ST_SIGN_ECDSA,ST_SIGN_SYMM,ST_SIGN_HMAC
*   @param structure_size 

*   @return G3_API_RESULT
*/
//###################################################
G3_API G3_API_RESULT g3api_dynamic_auth
(
		IN int key_index,
		IN EN_DYNAMIC_AUTH dauth_option,
		IN int pos_pub_dynamic,
		IN const byte* msg,
		IN int msg_size,
		IN const void* sign_structure,
		IN int structure_size
);

	
//###################################################	
/**
*   @name g3api_encryption
*   @brief  
*
*   @param key_index key sector index
*   @param block_mode 
*   @param iv 
*   @param data 
*   @param data_size 
*   @param cipher 
*   @param cipher_size 

*   @return G3_API_RESULT
*/
//###################################################
G3_API G3_API_RESULT g3api_encryption
(
		IN int key_index,
		IN EN_BLOCK_MODE block_mode,
		IN const ST_IV * iv,
		IN const byte* data,
		IN int data_size,
		OUT byte* cipher,
		INOUT int* cipher_size
);

	
//###################################################	
/**
*   @name g3api_decryption
*   @brief  
*
*   @param key_index key sector index
*   @param block_mode 
*   @param iv 
*   @param cipher 
*   @param cipher_size 
*   @param data 
*   @param data_size 

*   @return G3_API_RESULT
*/
//###################################################
G3_API G3_API_RESULT g3api_decryption
(
		IN int key_index,
		IN EN_BLOCK_MODE block_mode,
		IN const ST_IV* iv,
		IN const byte* cipher,
		IN int cipher_size,
		OUT byte* data,
		INOUT int* data_size
);

	
//###################################################	
/**
*   @name g3api_encryption_ecies
*   @brief  
*
*   @param key_index key sector index
*   @param rs 

*   @return G3_API_RESULT
*/
//###################################################
G3_API G3_API_RESULT g3api_encryption_ecies
(
		IN int key_index,
		OUT ST_ECIES* rs
);

	
//###################################################	
/**
*   @name g3api_decryption_ecies
*   @brief  
*
*   @param key_index key sector index
*   @param rs 

*   @return G3_API_RESULT
*/
//###################################################
G3_API G3_API_RESULT g3api_decryption_ecies
(
		IN int key_index,
		INOUT ST_ECIES* rs
);

	
//###################################################	
/**
*   @name g3api_session
*   @brief  
*
*   @param key_index key sector index
*   @param en_session_mode 
*   @param indata 
*   @param indata_size 
*   @param outdata 
*   @param outdata_size 

*   @return G3_API_RESULT
*/
//###################################################
G3_API G3_API_RESULT g3api_session
(
		IN int key_index,
		IN EN_SESSION_MODE en_session_mode,
		IN const byte* indata,
		IN int indata_size,
		OUT byte* outdata,
		INOUT int* outdata_size
);

	
//###################################################	
/**
*   @name g3api_set_extern_public_key
*   @brief  
*
*   @param pub_key enable 4 follow structure ST_ECC_PUBLIC,ST_ECC_PUBLIC_COMPRESS
*   @param structure_size 
*   @param puk_hash 

*   @return G3_API_RESULT
*/
//###################################################
G3_API G3_API_RESULT g3api_set_extern_public_key
(
		IN const void* pub_key,
		IN int structure_size,
		OUT ST_DATA_32* puk_hash
);

	
//###################################################	
/**
*   @name g3api_diversify
*   @brief  
*
*   @param key_index key sector index
*   @param diversify_mode 
*   @param param 

*   @return G3_API_RESULT
*/
//###################################################
G3_API G3_API_RESULT g3api_diversify
(
		IN int key_index,
		IN EN_DIVERSIFY_MODE diversify_mode,
		OUT ST_DIVERSIFY_PARAM* param
);

	
//###################################################	
/**
*   @name g3api_get_public_key
*   @brief  
*
*   @param key_index key sector index
*   @param pub_type 
*   @param pub_key enable 4 follow structure ST_ECC_PUBLIC,ST_ECC_PUBLIC_COMPRESS
*   @param structure_size 

*   @return G3_API_RESULT
*/
//###################################################
G3_API G3_API_RESULT g3api_get_public_key
(
		IN int key_index,
		IN EN_PUB_TYPE pub_type,
		OUT void* pub_key,
		IN int structure_size
);

	
//###################################################	
/**
*   @name g3api_certification
*   @brief  
*
*   @param key_index key sector index
*   @param certification_write_mode 
*   @param cert 
*   @param cert_size 

*   @return G3_API_RESULT
*/
//###################################################
G3_API G3_API_RESULT g3api_certification
(
		IN int key_index,
		IN EN_CERTIFICATION_WRITE_MODE certification_write_mode,
		IN const byte* cert,
		IN int cert_size
);

	
//###################################################	
/**
*   @name g3api_issue_certification
*   @brief  
*
*   @param key_index key sector index
*   @param public_key_pos 
*   @param issue_cert_area_type 
*   @param sector_num_to_store 
*   @param key_id 
*   @param cert 
*   @param cert_size 

*   @return G3_API_RESULT
*/
//###################################################
G3_API G3_API_RESULT g3api_issue_certification
(
		IN int key_index,
		IN int public_key_pos,
		IN EN_ISSUE_CERT_AREA_TYPE issue_cert_area_type,
		IN int sector_num_to_store,
		IN int key_id,
		IN const byte* cert,
		IN int cert_size
);

	
//###################################################	
/**
*   @name g3api_ecdh
*   @brief  
*
*   @param en_ecdh_mode 
*   @param Q_b enable 4 follow structure ST_ECC_PUBLIC,ST_ECC_PUBLIC_COMPRESS
*   @param Q_b_struct_size 
*   @param st_ecdh_random 
*   @param Q_chip 
*   @param ecdh_value enable 4 follow structure 
ST_ECDH_PRE_MASTER_SECRET|ST_ECDH_KEY_BLOCK|ST_ECDH_IV
*   @param ecdh_value_struct_size 

*   @return G3_API_RESULT
*/
//###################################################
G3_API G3_API_RESULT g3api_ecdh
(
		IN EN_ECDH_MODE en_ecdh_mode,
		IN const void* Q_b,
		IN int Q_b_struct_size,
		IN const ST_ECDH_RANDOM* st_ecdh_random,
		OUT ST_ECC_PUBLIC* Q_chip,
		OUT void* ecdh_value,
		OUT int ecdh_value_struct_size
);

	
//###################################################	
/**
*   @name g3api_make_tls_inter_header_without_size
*   @brief  
*
*   @param seq_num 
*   @param content_type 
*   @param tls_version 
*   @param tls_inter_header_without_size 

*   @return G3_API_RESULT
*/
//###################################################
G3_API G3_API_RESULT g3api_make_tls_inter_header_without_size
(
		IN int seq_num,
		IN EN_CONTENT_TYPE content_type,
		IN EN_TLS_VERSION tls_version,
		OUT ST_TLS_INTER_HEADER_WITHOUT_SIZE* tls_inter_header_without_size
);

	
//###################################################	
/**
*   @name g3api_tls_mac_encrypt
*   @brief  
*
*   @param tls_inter_header_without_size 
*   @param client_iv 
*   @param header_random 
*   @param msg 
*   @param msg_size 
*   @param crypto 
*   @param crypto_size 

*   @return G3_API_RESULT
*/
//###################################################
G3_API G3_API_RESULT g3api_tls_mac_encrypt
(
		IN const ST_TLS_INTER_HEADER_WITHOUT_SIZE* tls_inter_header_without_size,
		IN const ST_IV* client_iv,
		IN const ST_DATA_16* header_random,
		IN const byte* msg,
		IN int msg_size,
		OUT byte* crypto,
		INOUT int * crypto_size
);

	
//###################################################	
/**
*   @name g3api_tls_decrypt_verify
*   @brief  
*
*   @param tls_inter_header_without_size 
*   @param server_iv 
*   @param crypto 
*   @param crypto_size 
*   @param header_random 
*   @param msg 
*   @param msg_size 

*   @return G3_API_RESULT
*/
//###################################################
G3_API G3_API_RESULT g3api_tls_decrypt_verify
(
		IN const ST_TLS_INTER_HEADER_WITHOUT_SIZE* tls_inter_header_without_size,
		IN const ST_IV* server_iv,
		IN const byte* crypto,
		IN int crypto_size,
		OUT ST_DATA_16* header_random,
		OUT byte* msg,
		INOUT int* msg_size
);

	
//###################################################	
/**
*   @name g3api_tls_get_handshake_digest
*   @brief  
*
*   @param handshake_mode 
*   @param hash_handshake_msg 
*   @param handshake_digest 

*   @return G3_API_RESULT
*/
//###################################################
G3_API G3_API_RESULT g3api_tls_get_handshake_digest
(
		IN EN_HANDSHAKE_MODE handshake_mode,
		IN const ST_DATA_32* hash_handshake_msg,
		OUT ST_TLS_HAND_HANDSHAKE_DIGEST* handshake_digest
);

	
//###################################################	
/**
*   @name g3api_reset
*   @brief  
*

*   @return G3_API_RESULT
*/
//###################################################
G3_API G3_API_RESULT g3api_reset
(
);

	
//###################################################	
/**
*   @name g3api_test
*   @brief  
*
*   @param in 
*   @param in_size 

*   @return G3_API_RESULT
*/
//###################################################
G3_API G3_API_RESULT g3api_test
(
		IN const byte* in,
		IN int in_size
);

	//END API

/**
*   @brief  Swaps the values of two integer parameters.
*
*   @param  a is an initialized integer variable
*   @param  b is an initialized integer variable
*   @return void
*/
G3_API int GetSoftwareVersion(
	char* LCP_Version,
	char* FCP_Version
	);



#endif //__G3_API_HEADER__






