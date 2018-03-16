#include <g3_api.h>
#include "inter_def.h"
#include <stdlib.h>
#include <memory.h>
#include<stdio.h>
#include<string>
using namespace std;




//#pragma comment(lib,"libBASE.lib")
VAR_BYTES * convert_data_ieb100(void *pure_data, int data_size, int max_res_size);
//int do_normal_process(char inst, char p1, short p2, const void * data, int data_size, void * recv_data, int *real_recv_size);
G3_API_RESULT do_normal_process(char inst, char p1, short p2, const void * data, int data_size, VAR_BYTES ** recv_buff);
void SwapBytes(void* value, int size);
void api_view(const char *title);
G3_API_RESULT do_normal_process_return_ok(char inst, char p1, short p2, const void * data, int data_size);
int check_sign_struct(EN_SIGN_OPTION sign_option, int structure_size);
int check_vefify_struct(EN_VERIFY_OPTION verify_option, int structure_size);
int check_dynamic_auth_struct(EN_DYNAMIC_AUTH verify_etc, int structure_size);
int return_from_recv(VAR_BYTES *precvbuff);
bool append_var_bytes(VAR_BYTES**dist, const void*buffer, int size);
void view_hexstr(const char *title, const void *pbuff, int size);
void test();
VAR_BYTES* alloc_var_bytes(int size);

VAR_BYTES* create_var_bytes(const void*init, int size);
int def_send_n_recv(const unsigned char*snd, int snd_size, unsigned char*recv, int* recv_size, void*etcparam);


PFSENDRECV _psend = def_send_n_recv;
//PF_CONVERT _pconvert_data = convert_data_ieb100;
//PFSENDRECV _precv = NULL;
void * _etcparam = NULL;
bool is_use_ieb_100 = true;
FILE * _fp = stdout;

//
//void g3api_set_user_send_recv_pf(const PFSENDRECV psend, const PFSENDRECV precv){
//	_psend = psend;
//	_precv = precv;
//
//
//}



int def_send_n_recv(const unsigned char*snd, int snd_size, unsigned char*recv, int* recv_size, void*etcparam)
{
	api_view("def_send_n_recv");

	return 0;
}
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



G3_API_RESULT g3api_raw_snd_recv(const unsigned char * snd, int snd_size, unsigned char * recv, int* recv_size){
	int ret = _psend(snd, snd_size, recv, recv_size, _etcparam);
	return ret;
}


void g3api_set_etc_param(void * etcparam){
	_etcparam = etcparam;

}
void g3api_set_fp(void *fp)
{
	_fp = (FILE*)fp;
	
}


VAR_BYTES* g3api_alloc_var_bytes(int size){
	VAR_BYTES*ret = (VAR_BYTES*)malloc(4 + size);
	return ret;
}

void g3api_free_var_bytes(const VAR_BYTES* var_bytes){
	free((void*)var_bytes);
}
G3_API_RESULT g3api_read_key_value(const int key_index, EN_AREA_TYPE area_type, EN_RW_INST_OPTION rw_type, void* data_structure, int structure_size)
//G3_API_RESULT g3api_read_key_value(const int key_index, EN_AREA_TYPE area_type, EN_RW_INST_OPTION rw_type, ST_KEY_VALUE* key_value, ST_IV* iv, ST_MAC* mac)
{


	api_view("g3api_read_key_value");


	VAR_BYTES *precvbuff = NULL;

	//if (*key_value_size < KEY_VALUE_SIZE){
	//	return ERR_KEY_BUFF_SIZE;
	//}

	int ret = do_normal_process(READ, key_index, MAKEWORD(area_type, rw_type), NULL, 0, &precvbuff);
	if (ret < 0) return ret;

	if (KEY_VALUE_SIZE > precvbuff->size){
		/*int err_ret = 0;
		memcpy(&err_ret, precvbuff->buffer, 4);
		SwapBytes(&err_ret, 4);*/
		ret = return_from_recv(precvbuff);// ERR_INTERCHIP | err_ret;
		goto END;
	}

	memcpy(data_structure, precvbuff->buffer, precvbuff->size);
	//*key_value_size = precvbuff->size;

END:
	if (precvbuff) free(precvbuff);
	return ret;
}
G3_API_RESULT g3api_write_key_value(const int key_index, EN_AREA_TYPE area_type, EN_RW_INST_OPTION rw_type, const void* data_structure, int structure_size)
//G3_API_RESULT g3api_write_key_value(const int key_index, EN_AREA_TYPE area_type, EN_RW_INST_OPTION rw_type, const ST_KEY_VALUE* key_value, const ST_IV* iv, const ST_MAC* mac)
//int g3api_write_key_value(const int key_index, AREA_TYPE area_type, EN_RW_INST_OPTION rw_type, const unsigned char * key_value, int key_value_size)
{
	api_view("g3api_write_key_value");
	//if (KEY_VALUE_SIZE > key_value_size){
	//	return RET_RET_ERR_KEY_BUFF_SIZE;
	//}


	return do_normal_process_return_ok(WRITE, key_index, MAKEWORD(area_type, rw_type), data_structure, structure_size);

}


int g3api_get_chellange(int chall_size, unsigned char * challenge, int* res_chall_size){
	
	api_view("g3api_get_chellange");
	VAR_BYTES *precvbuff = NULL;
	if (!res_chall_size) return RET_ERR_RECV_ALLOC_ERROR;
	//if (res_chall_size) *res_chall_size =0;

	int nret = do_normal_process(GET_CHAL, chall_size, 0, NULL, 0, &precvbuff);
	if (nret < 0) {
		*res_chall_size = 0;
		goto END;;
	}
	if (!precvbuff){

		goto END;;

	}
	if ( precvbuff->size > *res_chall_size){
		nret = RET_ERR_RECV_BUFF_SIZE;
		goto END;
	}

	if(challenge) memcpy(challenge, precvbuff->buffer, precvbuff->size);
	if (res_chall_size) *res_chall_size = precvbuff->size;

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
G3_API_RESULT g3api_sign(const int key_index, EN_SIGN_OPTION sign_option, const unsigned char * msg, int msg_size, void * sign_structure, int structure_size)
//int g3api_sign(const int key_index, SIGN_OPTION ecdsa_option, const unsigned char * msg, int msg_size, void * sign_structure, int structure_size)
{
	api_view("g3api_sign");

	int nret = check_sign_struct(sign_option, structure_size);
	if (nret<0) return nret;

	
	//int recv_size = structure_size;
	VAR_BYTES *precvbuff = NULL;
	nret = do_normal_process(SIGN, key_index, sign_option, msg, msg_size, &precvbuff);

	if (nret < 0) {
		goto END;;
	}

	if (!precvbuff){
		nret = RET_ERR_RECV_ALLOC_ERROR;
		goto END;
	}

	nret = return_from_recv(precvbuff);// RET_ERR_INTERCHIP | err_ret;
	if (nret < 0) {
		goto END;;
	}

	if (precvbuff->size != structure_size) {
		nret =  RET_ERR_DIFF_STRUCT_SIZE;
		goto END;
	}

	

	memcpy(sign_structure, precvbuff->buffer, precvbuff->size);
END:

	if (precvbuff) free(precvbuff);


	return nret;
}
G3_API_RESULT g3api_verify(const int key_index, EN_VERIFY_OPTION verify_option, const unsigned char * msg, int msg_size, const void * sign_structure, int structure_size)
//int g3api_verify(const int key_index, VERIFY_OPTION verify_option, const unsigned char * msg, int msg_size, const void * sign_structure, int structure_size)
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

G3_API_RESULT g3api_dynamic_auth(int key_index, EN_DYNAMIC_AUTH dauth_option, int pos_pub_dynamic, const unsigned char * msg, int msg_size, const void * sign_structure, int structure_size)
//int g3api_dynamic_auth(int key_index, DYNAMIC_AUTH dauth_option, int pos_pub_dynamic, const unsigned char * msg, int msg_size, const void * sign_structure, int structure_size)
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


G3_API_RESULT g3api_encryption(IN int key_index, IN EN_BLOCK_MODE block_mode, IN const ST_IV * iv, IN const unsigned char* data, IN int data_size, OUT unsigned char* cipher, INOUT int* cipher_size)
{

	

	api_view("g3api_encryption");
	VAR_BYTES *precvbuff = NULL;
	VAR_BYTES * buff = create_var_bytes(iv, sizeof(ST_IV));
	append_var_bytes(&buff, data, data_size);

	view_hexstr("g3api_encryption test", buff->buffer, buff->size);

	int nret = do_normal_process(ENCRYPT, key_index, block_mode, data, data_size, &precvbuff);
	if (nret < 0) goto END;
//if(iv) memcpy(iv, precvbuff->buffer, sizeof(ST_IV));
	if (cipher) memcpy(cipher, precvbuff->buffer + sizeof(ST_IV), precvbuff->size - sizeof(ST_IV));
	if (cipher_size) *cipher_size = precvbuff->size - sizeof(ST_IV);



END:
	if (precvbuff) free(precvbuff);

	return nret;



}

G3_API_RESULT g3api_decryption(IN int key_index, IN EN_BLOCK_MODE block_mode, IN const ST_IV* iv, IN const unsigned char* cipher, IN int cipher_size, OUT unsigned char* data, INOUT int* data_size)
{

	
	api_view("g3api_decryption");
	VAR_BYTES *precvbuff = NULL;

	VAR_BYTES * buff = create_var_bytes(iv, sizeof(ST_IV));
	append_var_bytes(&buff, cipher, cipher_size);
	
	view_hexstr("g3api_decryption test", buff->buffer, buff->size);

	int nret = do_normal_process(DECRYPT, key_index, block_mode, buff->buffer, buff->size, &precvbuff);
	
	if (nret < 0) goto END;

	if (data) memcpy(data, precvbuff->buffer, precvbuff->size);
	if (data_size) *data_size = precvbuff->size;




END:
	if (buff) free(buff);
	if (precvbuff) free(precvbuff);

	return nret;
}

G3_API_RESULT g3api_encryption_ecies(IN int key_index, OUT ST_ECIES* rs)
{

	api_view("g3api_encryption_ecies");
	VAR_BYTES *precvbuff = NULL;
	int nret = do_normal_process(ENCRYPT, key_index, 0x10 , NULL, 0, &precvbuff);
	if (nret < 0) goto END;

	if (precvbuff->size != sizeof(ST_ECIES)){
		nret = RET_ERR_RECV_BUFF_SIZE;
		goto END;
	}
	if (rs) memcpy(rs, precvbuff->buffer, precvbuff->size);


END:
	if (precvbuff) free(precvbuff);

	return nret;



}

G3_API_RESULT g3api_decryption_ecies(IN int key_index, INOUT ST_ECIES* rs)
{

	api_view("g3api_decryption_ecies");
	VAR_BYTES *precvbuff = NULL;
	if (!rs){
		return RET_ERR_RECV_ALLOC_ERROR;


	}
	int nret = do_normal_process(DECRYPT, key_index, 0x10, rs->r, sizeof(rs->r), &precvbuff);
	if (nret < 0) goto END;
	
	if (precvbuff->size != sizeof( ((ST_ECIES*)0)->s)){
		nret = RET_ERR_RECV_BUFF_SIZE;
		goto END;
	}

	if (rs) memcpy(rs->s, precvbuff->buffer, precvbuff->size);


END:
	if (precvbuff) free(precvbuff);

	return nret;



}


G3_API_RESULT g3api_get_public_key(int key_index, EN_PUB_TYPE pub_type, void* pub_key, int structure_size)

{

	api_view("g3api_get_public_key");
	VAR_BYTES *precvbuff = NULL;
	short upperbyte = 0;
	switch (structure_size){
	case sizeof(ST_ECC_PUBLIC) :
		upperbyte = 1;
		break;
	case sizeof(ST_ECC_PUBLIC_COMPRESS) :
		upperbyte = 0;
		break;
									

	default:
		return RET_ERR_DIFF_STRUCT_SIZE;

	}


	
	int nret = do_normal_process(GET_PUB_KEY, key_index, MAKEWORD(upperbyte, pub_type), NULL, 0, &precvbuff);
	
	if (nret < 0) goto END;

	if (pub_key) memcpy(pub_key, precvbuff->buffer, precvbuff->size);




END:
	if (precvbuff) free(precvbuff);

	return nret;



}

G3_API_RESULT g3api_session(IN int key_index, IN EN_SESSION_MODE en_session_mode, IN const byte* indata, IN int indata_size, OUT byte* outdata, INOUT int* outdata_size)
{

	api_view("g3api_session");
	VAR_BYTES *precvbuff = NULL;
	

	int nret = do_normal_process(SESSION, key_index, en_session_mode, indata, indata_size, &precvbuff);


	if (nret < 0) goto END;

	if (outdata_size){
		if (precvbuff->size > *outdata_size){
			nret = RET_ERR_RECV_BUFF_SIZE;
			goto END;
		}
	}


END:
	if (precvbuff) free(precvbuff);

	return nret;



}


G3_API_RESULT g3api_set_extern_public_key(IN const void* pub_key, IN int structure_size, OUT ST_DATA_32* puk_hash)
{

	api_view("g3api_set_extern_public_key");
	VAR_BYTES *precvbuff = NULL;
	int nret = do_normal_process(SESSION, 1, EN_SESSION_MODE::EXT_PUB_KEY, pub_key, structure_size, &precvbuff);


	if (nret < 0) goto END;

	if (precvbuff->size != sizeof(ST_DATA_32)){
		nret = RET_ERR_RECV_BUFF_SIZE;
		goto END;
	}
	memcpy(puk_hash, precvbuff->buffer, precvbuff->size);




END:
	if (precvbuff) free(precvbuff);

	return nret;



}

G3_API_RESULT g3api_certification(int key_index, EN_CERTIFICATION_WRITE_MODE certification_write_mode, const unsigned char * cert, int cert_size)
//G3_API_RESULT g3api_certification(int key_index, CERTIFICATION_WRITE_MODE certification_write_mode, const unsigned char * cert, int cert_size)
{
	
	api_view("g3api_certification");
	int nret = 0;
	int unit_size = 240;

	const unsigned char * psubcert = cert;

	int remain_size = cert_size;
	int index = 0;
	while (remain_size>0)
	{
		int realsize = min(remain_size, unit_size);
		if (remain_size <= unit_size)//마지막루프 
		{
			index = 0xff;
		}
		VAR_BYTES *precvbuff = NULL;
		nret = do_normal_process_return_ok(CERT, key_index, MAKEWORD(index, certification_write_mode), psubcert, realsize);
		if (nret < 0) return nret;
		if (precvbuff) {
			free(precvbuff);
			precvbuff = NULL;
		}

		
		psubcert += unit_size;
		remain_size -= unit_size;
		


		index++;
	} ;


	return nret;



}

G3_API_RESULT g3api_issue_certification(int key_index, int public_key_pos, EN_ISSUE_CERT_AREA_TYPE issue_cert_area_type, int sector_num_to_store, int key_id, const unsigned char * cert, int cert_size)

//int g3api_issue_certification(int key_index, const unsigned char * cert, int cert_size)
{

	api_view("g3api_issue_certification");
	int nret = 0;
	int unit_size = 240;

	const unsigned char * psubcert = cert;

	int remain_size = cert_size;
	int index = 0;
	while (remain_size>0)
	{
		int realsize = min(remain_size, unit_size);
		
		VAR_BYTES *precvbuff = NULL;
		int unit_pub_pos = -1;
		if (public_key_pos < unit_size && public_key_pos>=0) unit_pub_pos = public_key_pos;
		nret = do_normal_process_return_ok(ISSUE_CERT, key_index, MAKEWORD(index, unit_pub_pos), psubcert, realsize);
		if (nret < 0) return nret;
		if (precvbuff) {
			free(precvbuff);
			precvbuff = NULL;
		}


		psubcert += unit_size;
		remain_size -= unit_size;
		public_key_pos -= unit_size;



		index++;
	};
	index = 0xff;
	unsigned char buff[8];
	buff[0] = issue_cert_area_type;
	buff[1] = sector_num_to_store;
	SwapBytes(&key_id, 2);
	memcpy(&buff[2], &key_id, 2);
	

	nret = do_normal_process_return_ok(ISSUE_CERT, key_index, 0XFFFF, buff, 4);




	return nret;



	api_view("g3api_issue_certification");
	VAR_BYTES *precvbuff = NULL;
	nret = do_normal_process(ISSUE_CERT, 0, 0, NULL, 0, &precvbuff);
	if (nret < 0) goto END;


END:
	if (precvbuff) free(precvbuff);

	return nret;



}


G3_API_RESULT g3api_ecdh(IN EN_ECDH_MODE en_ecdh_mode, IN const void* Q_b, IN int Q_b_struct_size, IN const ST_ECDH_RANDOM* st_ecdh_random, OUT ST_ECC_PUBLIC* Q_chip, OUT void* ecdh_value, OUT int ecdh_value_struct_size)
{


	api_view("g3api_ecdh");
	VAR_BYTES *precvbuff = NULL;
	int p2 = 0x0000;
	
	VAR_BYTES * buff = create_var_bytes(Q_b, Q_b_struct_size);
	
	switch (en_ecdh_mode)
	{
	case NORMAL_ECDH:
		break;
	case GEN_TLS_BLOCK:
	case SET_TLS_SESSION_KEY:
		append_var_bytes(&buff, st_ecdh_random, sizeof(ST_ECDH_RANDOM));

		break;
	}
	
	if (ecdh_value_struct_size == sizeof(ST_ECDH_PRE_MASTER_SECRET)){

	}
	int nret = do_normal_process(ECDH, 0, en_ecdh_mode, buff->buffer, buff->size, &precvbuff);
	if (nret < 0) goto END;
	if (precvbuff->size != sizeof(ST_ECC_PUBLIC) + ecdh_value_struct_size){
		nret = RET_ERR_RECV_BUFF_SIZE;
		goto END;
	}

	memcpy(Q_chip, precvbuff->buffer, sizeof(ST_ECC_PUBLIC));
	memcpy(ecdh_value, precvbuff->buffer + sizeof(ST_ECC_PUBLIC), ecdh_value_struct_size);


END:
	if (precvbuff) free(precvbuff);

	return nret;



}

G3_API_RESULT tls_crypto_temp(int cmd, IN int seq_num, IN EN_CONTENT_TYPE content_type, IN EN_TLS_VERSION tls_version, int msg_size, 
	IN const ST_IV* iv, 
	IN const byte* init_buff, IN int init_buff_size,
	IN const byte* in, IN int in_size, 
	int tail_size,
	VAR_BYTES **pprecvbuff)
{


	if (!iv || !in || !pprecvbuff){
		return RET_ERR_RECV_ALLOC_ERROR;
	}

	

	//VAR_BYTES *precvbuff = NULL;
	TLS_INTER_HEADER tls_inter_header = { 0, };
	tls_inter_header.lo_be_sequence = seq_num;
	tls_inter_header.tls_be_ver = tls_version;
	tls_inter_header.msg_be_size = msg_size;
	tls_inter_header.content_type = content_type;


	SwapBytes(&tls_inter_header.lo_be_sequence, 4);
	SwapBytes(&tls_inter_header.tls_be_ver, 2);
	SwapBytes(&tls_inter_header.msg_be_size, 2);




	VAR_BYTES * buff = create_var_bytes(&tls_inter_header, sizeof(TLS_INTER_HEADER));

	
	append_var_bytes(&buff, iv, sizeof(ST_IV));
	if(init_buff) append_var_bytes(&buff, init_buff, init_buff_size);


	int nret = do_normal_process_return_ok(cmd, 0, 0, buff->buffer, buff->size);
	if (nret < 0) goto END;
	//if (buff)  free(buff);



	byte* pubb = (byte*)in;
	//byte* pubb = (byte*) msg;
	view_hexstr("in", in, in_size);

	//int tail_size = in_size % 16;
	int remain_size = in_size - tail_size;
	int unit_size = 240;

	int index = 0;
	while (remain_size>0)
	{
		int realsize = min(remain_size, unit_size);
		fprintf(_fp, "remain_size:%d realsize : %d\n", remain_size, realsize);

		//VAR_BYTES *precvbuff = NULL;
		int unit_pub_pos = -1;

		view_hexstr("pubb:", pubb, realsize);
		nret = do_normal_process(cmd, 0, 1, pubb, realsize, pprecvbuff);
		if (nret < 0) return nret;
		//if (precvbuff) {
		//	free(precvbuff);
		//	precvbuff = NULL;
		//}

		pubb += realsize;
		remain_size -= realsize;

		index++;
	};
	fprintf(_fp, "remain_size:%d tail_size : %d\n", remain_size, tail_size);
	view_hexstr("pubb:", pubb, tail_size);
	nret = do_normal_process(cmd, 0, 0xff, pubb, tail_size, pprecvbuff);
	if (nret < 0) goto END;



	//if (out_size && (precvbuff->size > *out_size)){
	//	nret = RET_ERR_RECV_BUFF_SIZE;
	//	goto END;
	//}
	//if (out){
	//	memcpy(out, precvbuff->buffer, precvbuff->size);
	//	*out_size = precvbuff->size;
	//}


END:
	if (buff) free(buff);
	

	return nret;



}


G3_API_RESULT g3api_tls_mac_encrypt(IN int seq_num, IN EN_CONTENT_TYPE content_type, IN EN_TLS_VERSION tls_version, IN const ST_IV* client_iv, IN const ST_DATA_16* header_random, IN const byte* msg, IN int msg_size, OUT byte* crypto, INOUT int * crypto_size)
{


	api_view("g3api_tls_mac_encrypt");
	VAR_BYTES *precvbuff = NULL;

	if (!header_random){
		return RET_ERR_RECV_ALLOC_ERROR;
	}
	
	VAR_BYTES * buff = alloc_var_bytes( 0);
	
	append_var_bytes(&buff, header_random, sizeof(ST_DATA_16));
	append_var_bytes(&buff, msg, msg_size);


	int nret = tls_crypto_temp(TLS_MAC_ENC, seq_num, content_type, tls_version, msg_size, client_iv, 
		NULL,0,
		buff->buffer, buff->size, buff->size % 16, &precvbuff);



	//
	//VAR_BYTES *precvbuff = NULL;
	//TLS_INTER_HEADER tls_inter_header = {0,};
	//tls_inter_header.lo_be_sequence = seq_num;
	//tls_inter_header.tls_be_ver = tls_version;
	//tls_inter_header.msg_be_size = msg_size;
	//tls_inter_header.content_type = content_type;

	//
	//SwapBytes(&tls_inter_header.lo_be_sequence,4);
	//SwapBytes(&tls_inter_header.tls_be_ver, 2);
	//SwapBytes(&tls_inter_header.msg_be_size, 2);

	//


	//VAR_BYTES * buff = create_var_bytes(&tls_inter_header, sizeof(TLS_INTER_HEADER));
	//append_var_bytes(&buff, client_iv, sizeof(ST_IV));
	//



	//int nret = do_normal_process_return_ok(TLS_MAC_ENC, 0, 0, buff->buffer, buff->size);
	//if (nret < 0) goto END;
	//if (buff)  free(buff);


	//buff = create_var_bytes(msg, msg_size);
	//append_var_bytes(&buff, header_random, sizeof(ST_DATA_16));
	//


	//byte* pubb = buff->buffer;
	////byte* pubb = (byte*) msg;

	//
	//int tail_size = buff->size % 16;
	//int remain_size = buff->size - tail_size;
	//int unit_size = 240;

	//int index = 0;
	//while (remain_size>0)
	//{
	//	int realsize = min(remain_size, unit_size);
	//	fprintf(_fp, "remain_size:%d realsize : %d\n", remain_size,realsize);

	//	//VAR_BYTES *precvbuff = NULL;
	//	int unit_pub_pos = -1;


	//	nret = do_normal_process(TLS_MAC_ENC, 0, 1, pubb,realsize, &precvbuff);
	//	if (nret < 0) return nret;
	//	//if (precvbuff) {
	//	//	free(precvbuff);
	//	//	precvbuff = NULL;
	//	//}

	//	pubb += unit_size;
	//	remain_size -= unit_size;

	//	index++;
	//};
	//fprintf(_fp, "remain_size:%d tail_size : %d\n", remain_size, tail_size);

	//nret = do_normal_process(TLS_MAC_ENC, 0, 0xff, pubb, tail_size, &precvbuff);
	//if (nret < 0) goto END;

	if (crypto_size && (precvbuff->size > *crypto_size)){
		nret = RET_ERR_RECV_BUFF_SIZE;
		goto END;
	}
	if (crypto){
		memcpy(crypto, precvbuff->buffer, precvbuff->size);
		*crypto_size = precvbuff->size;
	}
	

END:
	if (buff) free(buff);
	//if (precvbuff) free(precvbuff);

	return nret;



}
G3_API_RESULT g3api_tls_decrypt_verify(IN int seq_num, IN EN_CONTENT_TYPE content_type, IN EN_TLS_VERSION tls_version, 
	IN const ST_IV* server_iv, 
	IN const byte* crypto, IN int crypto_size, 
	OUT ST_DATA_16* header_random, 
	OUT byte* msg, INOUT int* msg_size)
{


	api_view("g3api_tls_decrypt_verify");
	VAR_BYTES *precvbuff = NULL;

	VAR_BYTES * buff = create_var_bytes(msg, *msg_size);
	append_var_bytes(&buff, header_random, sizeof(ST_DATA_16));


	int nret = tls_crypto_temp(TLS_DEC_VERIFY, seq_num, content_type, tls_version, crypto_size, server_iv,
		crypto + crypto_size-32, 32,
		//NULL,0,
		crypto, crypto_size,48,
		&precvbuff);
	
	if (nret < 0) goto END;
	
	nret = precvbuff->buffer[0];

	if (msg_size && (precvbuff->size > *msg_size + sizeof(ST_DATA_16)+1)){
		nret = RET_ERR_RECV_BUFF_SIZE;
		goto END;
	}

	memcpy(header_random, &precvbuff->buffer[1], sizeof(ST_DATA_16));
	memcpy(msg, &precvbuff->buffer[1 + sizeof(ST_DATA_16)], precvbuff->size - 1 - sizeof(ST_DATA_16));

	if (msg_size) *msg_size = precvbuff->size - 1 - sizeof(ST_DATA_16);


END:
	if (precvbuff) free(precvbuff);

	return nret;



}
VAR_BYTES * _testbuff = NULL;

G3_API_RESULT g3api_test(const unsigned char * in, int in_size)
{
	api_view("g3api_test");
	//_testbuff = create_var_bytes(in, in_size);
	//int ret = _psend(_testbuff->buffer, _testbuff->size, NULL, NULL, NULL);

	VAR_BYTES * pvsnd = create_var_bytes("0123456789", 30);
	VAR_BYTES * precv = alloc_var_bytes(32);
	int size = 32;


	/*printf("pvsnd->buffer:0x%x\n", pvsnd);
	printf("pvsnd->buffer:0x%x\n", pvsnd);
	printf("pvsnd->buffer:0x%x\n", precv);
	printf("pvsnd->buffer:0x%x\n", _psend);*/

	int ret = _psend(pvsnd->buffer, pvsnd->size, precv->buffer, &precv->size, NULL);
	printf("%d %d\n", precv->size, ret);
	view_hexstr("precv", precv->buffer, precv->size);
	
	return 0;
}
void asfdaafdasf(){

	VAR_BYTES * pvsnd = create_var_bytes("0123456789", 10);
	VAR_BYTES * precv = alloc_var_bytes(32);
	int size = 32;



	int ret = _psend(pvsnd->buffer, pvsnd->size, precv->buffer, &precv->size, NULL);
	printf("%d %d\n", precv->size, ret);
	view_hexstr("precv", precv->buffer, precv->size);
}

G3_API_RESULT g3api_test7(const unsigned char * in, int in_size)
{
	api_view("g3api_test7");

	//VAR_BYTES * pvsnd = create_var_bytes("0123456789", 30);
	//VAR_BYTES * precv = alloc_var_bytes(32);
	//int size = 32;
	//int ret = 0;

	/*printf("pvsnd->buffer:0x%x\n", pvsnd);
	printf("pvsnd->buffer:0x%x\n", pvsnd);
	printf("pvsnd->buffer:0x%x\n", precv);
	printf("pvsnd->buffer:0x%x\n", _psend);*/
	asfdaafdasf();


	return 0;
}

G3_API_RESULT g3api_test6(const unsigned char * in, int in_size, PFSENDRECV pfsend)
{
	api_view("g3api_test6");

	_testbuff = create_var_bytes(in, in_size);

	VAR_BYTES * pvsnd = create_var_bytes("0123456789", 10);
	VAR_BYTES * precv = alloc_var_bytes(32);
	int size = 32;



	int ret = _psend(pvsnd->buffer, pvsnd->size, precv->buffer, &precv->size, NULL);
	printf("%d %d\n", precv->size, ret);
	view_hexstr("precv", precv->buffer, precv->size);

	return 0;
}

G3_API_RESULT g3api_test2(unsigned char * out, int* out_size)
{
	api_view("g3api_test2");
	printf("assign size :%d", *out_size);
	_testbuff = alloc_var_bytes(32);;
	if (_testbuff->size > *out_size){
		printf("assinge size is not enough\n");
		return -1;
	}

	memcpy(out, _testbuff->buffer, _testbuff->size);
	memcpy(out + _testbuff->size, _testbuff->buffer, _testbuff->size);
	*out_size = _testbuff->size * 2;

	
	

	return 0;
}

G3_API_RESULT g3api_test3(ST_ECC_PUBLIC* param)
{
	api_view("g3api_test3");
	printf("0x%x", param);
	unsigned char * pchar = (unsigned char *)param;
	for (int i = 0; i < sizeof(ST_ECC_PUBLIC); i++){
		*pchar = i % 255;
		pchar++;
	}
	return 0;
}


G3_API_RESULT g3api_test4(PFTEST pfsend)
{
	api_view("g3api_test4");

	


	pfsend(23, 42);

	
	return 0;
}
G3_API_RESULT g3api_test5(PFSENDRECV pfsend)
{
	api_view("g3api_test5");
	
	
	VAR_BYTES * pvsnd = create_var_bytes("0123456789", 10);
	VAR_BYTES * precv = alloc_var_bytes(32);
	int size = 32;



	int ret = _psend(pvsnd->buffer, pvsnd->size, precv->buffer, &precv->size, NULL);
	printf("%d %d\n", precv->size, ret);
	view_hexstr("precv", precv->buffer, precv->size);
	return 0;
}
G3_API_RESULT GetSoftwareVersion(
	char* LCP_Version,
	char* FCP_Version
	)
{
	int return_status = 0;
	string LCP_V("test");
	string FCP_V("test");
	strcpy(LCP_Version, LCP_V.c_str());
	strcpy(FCP_Version, FCP_V.c_str());

	return return_status;
}



G3_API_RESULT g3api_test8(PFSENDRECV pfsend, const unsigned char * in, int in_size)
 {
	 api_view("g3api_test8");
	 asfdaafdasf();
	 return 0;
 }
//START API

G3_API_RESULT g3api_get_device_version()
{
	api_view("g3api_get_device_version");
	return 0;
}	
	
char* g3api_get_sn()
{
	api_view("g3api_get_sn");
	return 0;
}	
	
G3_API_RESULT g3api_setup_core(INOUT ST_SETUP_CORE* st_setup_fixed)
{
	api_view("g3api_setup_core");
	return 0;
}	
	
G3_API_RESULT g3api_set_up_keys(INOUT ST_SET_UP_VALUE* array_set_up_value,IN int array_size)
{
	api_view("g3api_set_up_keys");
	return 0;
}	
	
G3_API_RESULT g3api_diversify(IN int key_index,IN EN_DIVERSIFY_MODE diversify_mode,OUT ST_DIVERSIFY_PARAM* param)
{

	api_view("g3api_diversify");
	VAR_BYTES *precvbuff = NULL;
	int nret = do_normal_process(DIVERSIFY, 0, 0, NULL, 0, &precvbuff);
	if (nret < 0) goto END;


END:
	if (precvbuff) free(precvbuff);
	
	return nret;

	
	
}	
	
G3_API_RESULT g3api_reset()
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































