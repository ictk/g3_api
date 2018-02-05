#include"g3_api.h"
#include "inter_def.h"
#include <stdlib.h>
#include <memory.h>
#include<stdio.h>





//#pragma comment(lib,"libBASE.lib")
VAR_BYTES * convert_data_ieb100(void *pure_data, int data_size);
//int do_normal_process(char inst, char p1, short p2, const void * data, int data_size, void * recv_data, int *real_recv_size);
int do_normal_process(char inst, char p1, short p2, const void * data, int data_size, VAR_BYTES ** recv_buff);
void SwapBytes(void* value, int size);
void api_view(const char *title);
int do_normal_process_return_ok(char inst, char p1, short p2, const void * data, int data_size);
int check_sign_struct(SIGN_OPTION sign_option, int structure_size);
int check_vefify_struct(VERIFY_OPTION verify_option, int structure_size);
int check_dynamic_auth_struct(DYNAMIC_AUTH verify_etc, int structure_size);
int return_from_recv(VAR_BYTES *precvbuff);

PFSENDRECV _psend = NULL;
//PFSENDRECV _precv = NULL;
void * _etcparam = NULL;
bool is_use_ieb_100 = true;
//
//void g3api_set_user_send_recv_pf(const PFSENDRECV psend, const PFSENDRECV precv){
//	_psend = psend;
//	_precv = precv;
//
//
//}

PF_CONVERT _pconvert_data = convert_data_ieb100;


const char * g3api_get_lib_version(){
	api_view("g3api_get_lib_version");
	static char szVersion[32] = LIB_VERSION;
	return szVersion;
}

void g3api_set_user_send_recv_pf(PFSENDRECV psendrecv, void * etcparam){
	api_view("g3api_set_user_send_recv_pf");
	_psend = psendrecv;
	_etcparam = etcparam;

}

int send_receiv_packet(LPWRITE_PACKET write_packet,int delay){
	
	_psend((unsigned char *)write_packet, write_packet->header.length, NULL, 0, _etcparam);


	//_precv()


	return 0;

}



int g3api_raw_snd_recv(const unsigned char * snd, int snd_size, unsigned char * recv, int* recv_size){
	int ret = _psend(snd, snd_size, recv, recv_size, _etcparam);
	return ret;
}


void g3api_set_etc_param(void * etcparam){
	_etcparam = etcparam;

}


VAR_BYTES* g3api_alloc_var_bytes(int size){
	VAR_BYTES*ret = (VAR_BYTES*)malloc(4 + size);
	return ret;
}

void g3api_free_var_bytes(const VAR_BYTES* var_bytes){
	free((void*)var_bytes);
}

int g3api_read_key_value(const int key_index, AREA_TYPE area_type, RW_TYPE rw_type, unsigned char * key_value, int* key_value_size){
	api_view("g3api_read_key_value");


	VAR_BYTES *precvbuff = NULL;

	if (*key_value_size < ERR_KEY_BUFF_SIZE){
		return ERR_KEY_BUFF_SIZE;
	}

	int ret = do_normal_process(READ, key_index, MAKEWORD(area_type, rw_type), NULL, 0, &precvbuff);
	if (ret < 0) return ret;

	if (KEY_VALUE_SIZE > precvbuff->size){
		/*int err_ret = 0;
		memcpy(&err_ret, precvbuff->buffer, 4);
		SwapBytes(&err_ret, 4);*/
		ret = return_from_recv(precvbuff);// ERR_INTERCHIP | err_ret;
		goto END;
	}
	memcpy(key_value, precvbuff->buffer, precvbuff->size);
	*key_value_size = precvbuff->size;

END:
	if (precvbuff) free(precvbuff);
	return ret;
}
int g3api_write_key_value(const int key_index, AREA_TYPE area_type, RW_TYPE rw_type, const unsigned char * key_value, int key_value_size){
	api_view("g3api_write_key_value");
	if (KEY_VALUE_SIZE > key_value_size){
		return ERR_KEY_BUFF_SIZE;
	}


	return do_normal_process_return_ok(WRITE, key_index, MAKEWORD(area_type, rw_type), key_value, key_value_size);

}


int g3api_get_chellange(int chall_size, unsigned char * challenge, int* res_chall_size){
	
	api_view("g3api_get_chellange");
	VAR_BYTES *precvbuff = NULL;
	
	int nret = do_normal_process(GET_CHAL, chall_size, 0, NULL, 0, &precvbuff);
	if (nret < 0) {
		goto END;;
	}
	if (precvbuff->size < *res_chall_size){
		nret = ERR_RECV_BUFF_SIZE;
		goto END;
	}

	memcpy(challenge, precvbuff->buffer, precvbuff->size);

END:
	if (precvbuff) free(precvbuff);

	return nret;



	
}

int g3api_verify_passwd(const int key_index, const unsigned char * passwd, int passwd_size){
	api_view("g3api_verify_passwd");
	return  do_normal_process_return_ok(VERIFY_PWD, key_index, 0, passwd, passwd_size);


	
}

int g3api_change_password(const int key_index, const unsigned char * passwd, int passwd_size){
	api_view("g3api_change_password");
	int recv_ret = 0;
	int recv_ret_size = 4;
	return  do_normal_process_return_ok(CHANGE_PWD, key_index, 0, passwd, passwd_size);

}

int g3api_init_puf(const int key_index, unsigned int initial){
	api_view("g3api_init_puf");
	SwapBytes(&initial,4);

	int nret = do_normal_process_return_ok(INIT_PRIV_KEY, key_index, 0, &initial, 4);
	return nret;
}

int g3api_sign(const int key_index, SIGN_OPTION ecdsa_option, const unsigned char * msg, int msg_size, void * sign_structure, int structure_size){
	api_view("g3api_sign");

	int nret = check_sign_struct(ecdsa_option, structure_size);
	if (nret<0) return nret;

	
	//int recv_size = structure_size;
	VAR_BYTES *precvbuff = NULL;
	nret = do_normal_process(SIGN, key_index, ecdsa_option, msg, msg_size, &precvbuff);

	if (nret < 0) {
		goto END;;
	}

	if (!precvbuff){
		nret = ERR_RECV_ALLOC_ERROR;
		goto END;
	}

	nret = return_from_recv(precvbuff);// ERR_INTERCHIP | err_ret;
	if (nret < 0) {
		goto END;;
	}

	if (precvbuff->size != structure_size) {
		nret =  ERR_DIFF_STRUCT_SIZE;
		goto END;
	}

	

	memcpy(sign_structure, precvbuff->buffer, precvbuff->size);
END:

	if (precvbuff) free(precvbuff);


	return nret;
}
int g3api_verify(const int key_index, VERIFY_OPTION verify_option, const unsigned char * msg, int msg_size, const void * sign_structure, int structure_size)
{
	api_view("g3api_verify");
	int nret = check_vefify_struct(verify_option, structure_size);
	if (nret<0) return nret;
	
	unsigned char * pbuff = (unsigned char *)malloc(msg_size + structure_size);
	memcpy(pbuff, msg, msg_size);
	memcpy(pbuff + msg_size, sign_structure, structure_size);



	


	nret = do_normal_process_return_ok(VERIFY, key_index, verify_option, pbuff, msg_size + structure_size);
	free(pbuff);

	return nret;
}


int g3api_dynamic_auth(int key_index, DYNAMIC_AUTH dauth_option, int pos_pub_dynamic, const unsigned char * msg, int msg_size, const void * sign_structure, int structure_size)
{
	api_view("g3api_verify_dynamic");
	int nret = check_dynamic_auth_struct(dauth_option, structure_size);
	if (nret<0) return nret;
	
	unsigned char * pbuff = (unsigned char *)malloc(msg_size + structure_size);
	memcpy(pbuff, msg, msg_size);
	memcpy(pbuff + msg_size, sign_structure, structure_size);

	
	
	nret = do_normal_process_return_ok(VERIFY, key_index, MAKEWORD(dauth_option, pos_pub_dynamic), pbuff, msg_size + structure_size);
	free(pbuff);

	return nret;


}

int g3api_encryption(int key_index, BLOCK_MODE block_mode, const unsigned char * data, int data_size, ST_IV * iv, unsigned char * cipher, int cipher_size)
{

	api_view("g3api_encryption");
	VAR_BYTES *precvbuff = NULL;
	int nret = do_normal_process(ENCRYPT, key_index, block_mode, data, data_size, &precvbuff);
	if (nret < 0) goto END;
	if (precvbuff->size < sizeof(ST_IV) + 16){
		nret = ERR_RECV_BUFF_SIZE;
		goto END;
	}



END:
	if (precvbuff) free(precvbuff);

	return nret;



}

int g3api_decryption(int key_index, BLOCK_MODE block_mode, const ST_IV * iv, unsigned char * cipher, const int cipher_size, unsigned char * data, int data_size)
{
	api_view("g3api_decryption");
	VAR_BYTES *precvbuff = NULL;
	int nret = do_normal_process(DECRYPT, 0, 0, NULL, 0, &precvbuff);
	if (nret < 0) goto END;


END:
	if (precvbuff) free(precvbuff);

	return nret;
}
//START API

int g3api_get_device_version()
{
	api_view("g3api_get_device_version");
	return 0;
}	
	
char* g3api_get_sn()
{
	api_view("g3api_get_sn");
	return 0;
}	
	
int g3api_setup_core( SETUP_CORE st_setup_fixed)
{
	api_view("g3api_setup_core");
	return 0;
}	
	
int g3api_set_up_keys( SET_UP_UNIT_ARRAY keys_configure)
{
	api_view("g3api_set_up_keys");
	return 0;
}	
	
int g3api_encryption( int key_index, BLOCK_MODE block_mode,const unsigned char * data, int data_size, ST_IV * iv, unsigned char * cipher, int cipher_size)
{

	api_view("g3api_encryption");
	VAR_BYTES *precvbuff = NULL;
	int nret = do_normal_process(ENCRYPT, 0, 0, NULL, 0, &precvbuff);
	if (nret < 0) goto END;


END:
	if (precvbuff) free(precvbuff);
	
	return nret;

	
	
}	
	
	
int g3api_encryption_ecies( int key_index,const unsigned char * data, int data_size, ST_SIGN_ECDSA* rs)
{

	api_view("g3api_encryption_ecies");
	VAR_BYTES *precvbuff = NULL;
	int nret = do_normal_process(ENCRYPT, 0, 0, NULL, 0, &precvbuff);
	if (nret < 0) goto END;


END:
	if (precvbuff) free(precvbuff);
	
	return nret;

	
	
}	
	
int g3api_decryption_ecies( int key_index,const ST_SIGN_ECDSA* rs, unsigned char * data, int data_size)
{

	api_view("g3api_decryption_ecies");
	VAR_BYTES *precvbuff = NULL;
	int nret = do_normal_process(DECRYPT, 0, 0, NULL, 0, &precvbuff);
	if (nret < 0) goto END;


END:
	if (precvbuff) free(precvbuff);
	
	return nret;

	
	
}	
	
int g3api_ecdh( int key_index,const void * Q_b, int Q_b_size, ST_ECC_PUBLIC* Q_chip, ST_ECC_PUBLIC* ecdh_value)
{

	api_view("g3api_ecdh");
	VAR_BYTES *precvbuff = NULL;
	int nret = do_normal_process(SESSION, 0, 0, NULL, 0, &precvbuff);
	if (nret < 0) goto END;


END:
	if (precvbuff) free(precvbuff);
	
	return nret;

	
	
}	
	
int g3api_session( int key_index)
{

	api_view("g3api_session");
	VAR_BYTES *precvbuff = NULL;
	int nret = do_normal_process(SESSION, 0, 0, NULL, 0, &precvbuff);
	if (nret < 0) goto END;


END:
	if (precvbuff) free(precvbuff);
	
	return nret;

	
	
}	
	
int g3api_diversify( int key_index, DIVERSIFY_MODE diversify_mode, ST_DIVERSIFY_PARAM* param)
{

	api_view("g3api_diversify");
	VAR_BYTES *precvbuff = NULL;
	int nret = do_normal_process(DIVERSIFY, 0, 0, NULL, 0, &precvbuff);
	if (nret < 0) goto END;


END:
	if (precvbuff) free(precvbuff);
	
	return nret;

	
	
}	
	
int g3api_get_public_key( int key_index, PUB_TYPE pub_type, void* pub_key, int structure_size)
{

	api_view("g3api_get_public_key");
	VAR_BYTES *precvbuff = NULL;
	int nret = do_normal_process(GET_PUB_KEY, 0, 0, NULL, 0, &precvbuff);
	if (nret < 0) goto END;


END:
	if (precvbuff) free(precvbuff);
	
	return nret;

	
	
}	
	
int g3api_certification( int key_index, CERTIFICATION_WRITE_MODE certification_write_mode,const unsigned char * cert, int cert_size)
{

	api_view("g3api_certification");
	VAR_BYTES *precvbuff = NULL;
	int nret = do_normal_process(CERT, 0, 0, NULL, 0, &precvbuff);
	if (nret < 0) goto END;


END:
	if (precvbuff) free(precvbuff);
	
	return nret;

	
	
}	
	
int g3api_issue_certification( int key_index,const unsigned char * cert, int cert_size)
{

	api_view("g3api_issue_certification");
	VAR_BYTES *precvbuff = NULL;
	int nret = do_normal_process(ISSUE_CERT, 0, 0, NULL, 0, &precvbuff);
	if (nret < 0) goto END;


END:
	if (precvbuff) free(precvbuff);
	
	return nret;

	
	
}	
	
int g3api_reset()
{

	api_view("g3api_reset");
	VAR_BYTES *precvbuff = NULL;
	int nret = do_normal_process(RESET, 0, 0, NULL, 0, &precvbuff);
	if (nret < 0) goto END;


END:
	if (precvbuff) free(precvbuff);
	
	return nret;

	
	
}	
	//END API

