
#ifndef __G3_API_HEADER__
#define __G3_API_HEADER__

#include"g3_define.h"


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
G3_API const char * CALLTYPE g3api_get_lib_version
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
G3_API void CALLTYPE g3api_set_user_send_recv_pf
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
G3_API G3_API_RESULT CALLTYPE g3api_get_device_version
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
G3_API char* CALLTYPE g3api_get_sn
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
G3_API G3_API_RESULT CALLTYPE g3api_raw_snd_recv
(
		IN const byte* snd ,
		IN int snd_size,
		OUT byte* recv,
		OUT int* recv_size
);

	
//###################################################	
/**
*   @name g3api_read_key_value
*   @brief  read value from setup,key_sector,user data
*
*   @param	key_index		: Key sector index(p1)
*   @param	area_type		: The type of area to read(p2_lower)
*   @param	rw_type			: The mode of the read command(p2_upper) 
*   @param	data			: For masked operation( rw_type -> 0xFF )
*   @param	data_size		: The size of the mask
*   @param	data_structure	: Read data, enable 3 follow structure ST_RW_DATA,ST_RW_DATA_WITH_IV,ST_RW_DATA_WITH_IV_MAC
*   @param	structure_size  : The size of data_structure

*   @return G3_API_RESULT
*/
//###################################################
G3_API G3_API_RESULT CALLTYPE g3api_read_key_value
(
		IN int key_index,
		IN EN_AREA_TYPE area_type,
		IN EN_RW_INST_OPTION rw_type,
		IN const void* data,
		IN int data_size,
		OUT void* data_structure,
		OUT int structure_size
);

	
//###################################################	
/**
*   @name g3api_write_key_value
*   @brief  write value to setup,key_sector,user data
*
*   @param	key_index		: Key sector index(p1)
*   @param	area_type		: The type of area to write(p2_lower)
*   @param	rw_type			: The mode of the command(p2_upper) 
*   @param	data_structure	: Data to write, enable 4 follow structure ST_RW_DATA,ST_RW_DATA_WITH_IV,ST_RW_DATA_WITH_IV_MAC			  
*   @param	structure_size	: The size of data_structure

*   @return G3_API_RESULT
*/
//###################################################
G3_API G3_API_RESULT CALLTYPE g3api_write_key_value
(
		IN int key_index,
		IN EN_AREA_TYPE area_type,
		IN EN_RW_INST_OPTION rw_type,
		IN const void* data_structure,
		IN int structure_size
);

	
//###################################################	
/**
*   @name g3api_get_challenge
*   @brief  Get challenge (random value) 
*
*   @param	chall_size		: The size of challenge to get
*   @param	challenge		: The buffer to put challenge 
*   @param	res_chall_size	: The size of buffer to put challenge

*   @return G3_API_RESULT
*/
//###################################################
G3_API G3_API_RESULT CALLTYPE g3api_get_challenge
(
		IN int chall_size,
		OUT byte* challenge,
		INOUT int* res_chall_size
);

	
//###################################################	
/**
*   @name g3api_verify_passwd
*   @brief	Verify the password of the target sector with input password and if it succeeded, obtain AC
*
*   @param key_index		: Key sector index(p1)
*   @param passwd			: Input password key
*   @param passwd_size		: The size of of password key

*   @return G3_API_RESULT
*/
//###################################################
G3_API G3_API_RESULT CALLTYPE g3api_verify_passwd
(
		IN int key_index,
		IN const byte* passwd,
		IN int passwd_size
);

	
//###################################################	
/**
*   @name g3api_change_password
*   @brief	Change the password of the target sector to input password
*
*   @param key_index		: Key sector index(p1)
*   @param passwd			: Input password
*   @param passwd_size		: The size of password key

*   @return G3_API_RESULT
*/
//###################################################
G3_API G3_API_RESULT CALLTYPE g3api_change_password
(
		IN int key_index,
		IN const byte* passwd,
		IN int passwd_size
);

	
//###################################################	
/**
*   @name g3api_init_puf
*   @brief  Write the revision value into the target sector, the target sector should be an ECC PUF
*
*   @param key_index		: Key sector index(p1)
*   @param initial			: The revision value (4 bytes)

*   @return G3_API_RESULT
*/
//###################################################
G3_API G3_API_RESULT CALLTYPE g3api_init_puf
(
		IN int key_index,
		IN unsigned int initial
);

	
//###################################################	
/**
*   @name g3api_sign
*   @brief  Generate a signature with input msg
*
*   @param key_index		: Key sector index(p1)
*   @param sign_option		: The option of command(p2)
*   @param msg				: Input data, it will be used to generate a signature
*   @param msg_size			: The size of msg
*   @param sign_structure	: Enable 4 follow structure ST_SIGN_ECDSA,ST_SIGN_SYMM,ST_SIGN_HMAC
*   @param structure_size	: The size of sign_structure

*   @return G3_API_RESULT
*/
//###################################################
G3_API G3_API_RESULT CALLTYPE g3api_sign
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
*   @brief  Verify the signature 
*
*   @param key_index		: Key sector index(p1)
*   @param verify_option	: The option of command(p2)
*   @param msg				: Input data, it contains data and signature
*   @param msg_size			: The size of input data
*   @param sign_structure	: Output from the command, enable 3 follow structure ST_SIGN_ECDSA,ST_SIGN_SYMM,ST_SIGN_HMAC
*   @param structure_size	: The size of sign_structure

*   @return G3_API_RESULT
*/
//###################################################
G3_API G3_API_RESULT CALLTYPE g3api_verify
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
*   @brief  Verify the signature and obtain AC. Input signature must be generated with challenge that generated in G3
*		
*   @param key_index		: Key sector index(p1)
*   @param dauth_option		: The mode of the command(p2)
*   @param pos_pub_dynamic	: A random position
*   @param msg				: Input data, it contains data and signature
*   @param msg_size			: The size of input data 
*   @param sign_structure	: Output from the command, enable 3 follow structure ST_SIGN_ECDSA,ST_SIGN_SYMM,ST_SIGN_HMAC
*   @param structure_size	: The size of sign_sturucture

*   @return G3_API_RESULT
*/
//###################################################
G3_API G3_API_RESULT CALLTYPE g3api_dynamic_auth
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
*   @brief  Encrypt a given plain data
*
*   @param key_index		: Key sector index(p1)
*   @param key_type			: Key type of the key for encryption(p2_upper)
*   @param block_mode		: The block cipher operation mode(p2_lower)
*   @param iv				: Initial vector 
*   @param data				: The plain data for encryption
*   @param data_size		: The size of plain data
*   @param cipher			: Output from the command, cipher data
*   @param cipher_size		: The size of cipher data

*   @return G3_API_RESULT
*/
//###################################################
G3_API G3_API_RESULT CALLTYPE g3api_encryption
(
		IN int key_index,
		IN EN_KEY_TYPE key_type,
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
*   @brief  Decrypt a given cipher data
*
*   @param key_index		: Key sector index(p1)
*   @param key_type			: Key type of the key for decryption(p2_upper)
*   @param block_mode		: The block cipher operation mode(p2_lower)
*   @param iv				: Initial vector
*   @param cipher			: The cipher data for decryption
*   @param cipher_size		: The size of cipher data
*   @param data				: Output from the command, plain data
*   @param data_size		: The size of plain data

*   @return G3_API_RESULT
*/
//###################################################
G3_API G3_API_RESULT CALLTYPE g3api_decryption
(
		IN int key_index,
		IN EN_KEY_TYPE key_type,
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
*   @brief  Encrypt a given plain data with ECIES
*
*   @param key_index		: Key sector index(p1)
*   @param rs				: R (R=rG, r:random) - ECC private key, S=x of (rKB=kBR), r: random, KB : public key of B, kB : private key of B)

*   @return G3_API_RESULT
*/
//###################################################
G3_API G3_API_RESULT CALLTYPE g3api_encryption_ecies
(
		IN int key_index,
		OUT ST_ECIES* rs
);

	
//###################################################	
/**
*   @name g3api_decryption_ecies
*   @brief  Decrypt a given cipher data with ECIES
*
*   @param key_index		: Key sector index(p1)
*   @param rs				: R (R=rG, r:random) - ECC private key, S=x of (rKB=kBR), r: random, KB : public key of B, kB : private key of B)

*   @return G3_API_RESULT
*/
//###################################################
G3_API G3_API_RESULT CALLTYPE g3api_decryption_ecies
(
		IN int key_index,
		INOUT ST_ECIES* rs
);

	
//###################################################	
/**
*   @name g3api_session
*   @brief  Generate sessions. It provides four modes : Symmetric key, Factory key, External Session key and External public key
*
*   @param key_index		: Key sector index(p1)
*   @param en_session_mode	: Selection of the mode of session instruction(p2)
*   @param indata			: Parameter to make a session key
*   @param indata_size		: The size of input data
*   @param outdata			: Output from the command
*   @param outdata_size		: The size of output

*   @return G3_API_RESULT
*/
//###################################################
G3_API G3_API_RESULT CALLTYPE g3api_session
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
*   @brief  Load input public key to temporary memory
*
*   @param pub_key			: Public key to load, enable 2 follow structure ST_ECC_PUBLIC,ST_ECC_PUBLIC_COMPRESS
*   @param structure_size	: The size of the public key buffer
*   @param puk_hash			: Output from the command, hashed data

*   @return G3_API_RESULT
*/
//###################################################
G3_API G3_API_RESULT CALLTYPE g3api_set_extern_public_key
(
		IN const void* pub_key,
		IN int structure_size,
		OUT ST_DATA_32* puk_hash
);

	
//###################################################	
/**
*   @name g3api_diversify
*   @brief  Diversify a symmetric key by using diversify AC. It can be executed in two mode : self mode and inherit mode
*			If rw_operation bits of the target key setting is 11, diversify command requires a MAC
*
*   @param key_index		: Key sector index(p1)
*   @param diversify_mode	: Selection of the mode in self mode or inherit mode(p2)
*   @param data				: Parameter to be diversified
*   @param data_size		: The size of data buffer

*   @return G3_API_RESULT
*/
//###################################################
G3_API G3_API_RESULT CALLTYPE g3api_diversify
(
		IN int key_index,
		IN EN_DIVERSIFY_MODE diversify_mode,
		IN const byte* data,
		IN int data_size
);

	
//###################################################	
/**
*   @name g3api_get_public_key
*   @brief  Output a public key in a compress form(33bytes) or X,Y coordinate form(64 bytes)
*
*   @param key_index		: Key sector index(p1)
*   @param pub_type			: Select public key in key sector or temporary memory
*   @param pub_key			: The buffer to put the public key. Enable 2 follow structure ST_ECC_PUBLIC, ST_ECC_PUBLIC_COMPRESS
*   @param structure_size	: The size of buffer

*   @return G3_API_RESULT
*/
//###################################################
G3_API G3_API_RESULT CALLTYPE g3api_get_public_key
(
		IN int key_index,
		IN EN_PUB_TYPE pub_type,
		OUT void* pub_key,
		IN int structure_size
);

	
//###################################################	
/**
*   @name g3api_certification
*   @brief  Verify a certificate, and then update a public key or store it in public key of temporary memory
*			The session can be generated by the public key of temporary memory
*
*   @param key_index				: Key sector index(p1)
*   @param certification_write_mode : Provide two modes : update temporary public key or write public ke to key sector
*   @param cert						: Input a certificate to verify
*   @param cert_size				: The size of certificate

*   @return G3_API_RESULT
*/
//###################################################
G3_API G3_API_RESULT CALLTYPE g3api_certification
(
		IN int key_index,
		IN EN_CERTIFICATION_WRITE_MODE certification_write_mode,
		IN const byte* cert,
		IN int cert_size
);

	
//###################################################	
/**
*   @name g3api_issue_certification
*   @brief  Issue a certificate and store it. Add the pair public key of private key in target sector(p1) to certificate
*			The length of the certificate cannot exceed 1024 bytes.
*
*   @param key_index			: Key sector index(p1)
*   @param public_key_pos		: The public key position
*   @param issue_cert_area_type	: The area type where the issued certificate will be stored
*   @param sector_num_to_store  : The sector number to store the issued certificate
*   @param key_id				: Factory key ID or the sector number of private key
*   @param encrypted_key		: When using key_id as a factory key id, encrypted_key must be given
*   @param cert					: TBS certificate
*   @param cert_size			: The size of tbs certificate

*   @return G3_API_RESULT
*/
//###################################################
G3_API G3_API_RESULT CALLTYPE g3api_issue_certification
(
		IN int key_index,
		IN int public_key_pos,
		IN EN_ISSUE_CERT_AREA_TYPE issue_cert_area_type,
		IN int sector_num_to_store,
		IN int key_id,
		IN const ST_DATA_32* encrypted_key,
		IN const byte* cert,
		IN int cert_size
);

	
//###################################################	
/**
*   @name g3api_ecdh
*   @brief  Used for session key agreement. 
*			Normal_ECDH mode outputs public key chip[64] || pre master secret[32]
*			Generate TLS KEY BLOCK mode outputs public key chip[64] || TLS key block[128]
*			Set TLS session key to temporary memory mode outputs public key chip[64] || client write iv[16] || server write iv[16]
*
*   @param en_ecdh_mode				: Provide 3 levels of key agreement functions : ECDH / Gen TLS Key Block / Set TLS Session key to temporary memory
*   @param Q_b						: Public key - enable 2 follow structure ST_ECC_PUBLIC, ST_ECC_PUBLIC_COMPRESS
*   @param Q_b_struct_size			: The size of public key ( 33 byte or 64 byte )
*   @param st_ecdh_random			: ServerHello.random[32] || ClientHello.random[32] 
*   @param Q_chip					: Public Key Chip ( dchipG )
*   @param ecdh_value				: Enable 3 follow structure ST_ECDH_PRE_MASTER_SECRET | ST_ECDH_KEY_BLOCK | ST_ECDH_IV
*   @param ecdh_value_struct_size	: The size of ecdh_value 

*   @return G3_API_RESULT
*/
//###################################################
G3_API G3_API_RESULT CALLTYPE g3api_ecdh
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
*   @brief  Generate tls header without size : TLS Sequence Num[8] || TLS type[1] || TLS Version[2]
*
*   @param seq_num							: The TLS sequence low 4 byte
*   @param content_type						: The content type[1]
*   @param tls_version						: The TLS version[2]
*   @param tls_inter_header_without_size	: The structure for the TLS header without size

*   @return G3_API_RESULT
*/
//###################################################
G3_API G3_API_RESULT CALLTYPE g3api_make_tls_inter_header_without_size
(
		IN int seq_num,
		IN EN_CONTENT_TYPE content_type,
		IN EN_TLS_VERSION tls_version,
		OUT ST_TLS_INTER_HEADER_WITHOUT_SIZE* tls_inter_header_without_size
);

	
//###################################################	
/**
*   @name g3api_tls_mac_encrypt
*   @brief  Generate an encrypted TLS record using the TLS session key block stored in temporary memory
*
*   @param tls_inter_header_without_size	: TLS_HEADER ( TLS Sequence Num[8] || TLS type[1] || TLS Version[2] ) 
*   @param client_iv						: Client_Write_IV[16]
*   @param header_random					: The first input data must contain 16 bytes of random IV to prevent attacks
*   @param msg								: The plain text
*   @param msg_size							: The size of the plain text
*   @param crypto							: The cipher text
*   @param crypto_size						: The size of the cipher text

*   @return G3_API_RESULT
*/
//###################################################
G3_API G3_API_RESULT CALLTYPE g3api_tls_mac_encrypt
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
*   @brief  Generate a decrypted TLS fragment from an input encrypted TLS record using the TLS session key block stored in temporary memory
*
*   @param tls_inter_header_without_size	: TLS_HEADER ( TLS Sequence Num[8] || TLS type[1] || TLS Version[2] ) 
*   @param server_iv						: Server_Write_IV[16]
*   @param crypto							: The cipher text
*   @param crypto_size						: The size of the cipher text
*   @param header_random					: The first output data must contain 16 bytes of random IV to prevent attacks
*   @param msg								: The plain text
*   @param msg_size							: The size of the plain text

*   @return G3_API_RESULT
*/
//###################################################
G3_API G3_API_RESULT CALLTYPE g3api_tls_decrypt_verify
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
*   @brief  Used for finishing the TLS session key agreement
*
*   @param handshake_mode		: It has two modes : client handshake and server handshake
*   @param hash_handshake_msg	: The data for handshaking
*   @param handshake_digest		: The buffer to put the handshake digest

*   @return G3_API_RESULT
*/
//###################################################
G3_API G3_API_RESULT CALLTYPE g3api_tls_get_handshake_digest
(
		IN EN_HANDSHAKE_MODE handshake_mode,
		IN const ST_DATA_32* hash_handshake_msg,
		OUT ST_TLS_HAND_HANDSHAKE_DIGEST* handshake_digest
);


//###################################################	
/**
*   @name g3api_sha256_mode
*   @brief  For SHA256 calculation
*	
*	@param sha256_mode	: Sha256 command is executed in three steps : initialization, update and finalization
*   @param data			: The data to be subjected to the sha256 operation
*   @param data_size	: The size of input data
*   @param outdata		: The buffer to put the outputs from sha256

*   @return G3_API_RESULT
*/
//###################################################
G3_API G3_API_RESULT CALLTYPE g3api_sha256
(
		IN EN_SHA256_MODE sha256_mode,
		IN const byte* data,
		IN int data_size,
		OUT ST_DATA_32* outdata
);


//###################################################	
/**
*   @name g3api_reset
*   @brief  Reset the G3, and then initialize authentication results and a session
*

*   @return G3_API_RESULT
*/
//###################################################
G3_API G3_API_RESULT CALLTYPE g3api_reset
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
G3_API G3_API_RESULT CALLTYPE g3api_test
(
		IN PFTEST in,
		IN int in_size
);

	
//###################################################	
/**
*   @name g3api_test2
*   @brief  
*
*   @param test 
*   @param out_size 

*   @return G3_API_RESULT
*/
//###################################################
G3_API G3_API_RESULT CALLTYPE g3api_test2
(
		IN char* test,
		IN int* out_size
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






