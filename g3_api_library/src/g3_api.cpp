#include"g3_api.h"
#include "inter_def.h"
#include <stdlib.h>
#include <memory.h>
#include<stdio.h>

//#pragma comment(lib,"libBASE.lib")
unsigned long calcCRC(unsigned char* data, int iLength);
void SwapBytes(void* value, int size);

const char * g3api_get_lib_version(){
	static char szVersion[32] = LIB_VERSION;
	return szVersion;
}
PFSENDRECV _psend = NULL;
PFSENDRECV _precv = NULL;
void * _etcparam = NULL;
bool is_use_ieb_100 = true;
//
//void g3api_set_user_send_recv_pf(const PFSENDRECV psend, const PFSENDRECV precv){
//	_psend = psend;
//	_precv = precv;
//
//
//}



void g3api_set_user_send_recv_pf(PFSENDRECV psendrecv, void * etcparam){
	_psend = psendrecv;
	_etcparam = etcparam;

}

int send_receiv_packet(LPWRITE_PACKET write_packet,int delay){
	
	_psend((unsigned char *)write_packet, write_packet->header.length, NULL, 0, _etcparam);


	//_precv()


	return 0;

}




LPWRITE_PACKET make_write_packet(char inst,char p1,short p2, const void * data, int data_size,int *packet_size){
	//sizeof(WRITE_PACKET) is included crc
	int total_write_packet_size = sizeof(WRITE_PACKET) + data_size;//included crc
	int total_write_packet_size_without_crc = sizeof(HEADER_WRITE_PACKET) + data_size;//included crc

	LPWRITE_PACKET lp_write_packet = (LPWRITE_PACKET)malloc(total_write_packet_size);
	memset(lp_write_packet, 0x00, total_write_packet_size);
	lp_write_packet->header.ins = inst;
	lp_write_packet->header.p1 = p1;
	lp_write_packet->header.p2 = p2;
	lp_write_packet->header.length = total_write_packet_size;
	if (data_size > 0) memcpy(lp_write_packet->data, data, data_size);
	
	unsigned long crc = calcCRC((unsigned char*)lp_write_packet, total_write_packet_size_without_crc);
	memcpy(&lp_write_packet->data[data_size], &crc, 2);

	printf("0x%x 0x%x 0x%x \n", crc, lp_write_packet->data[total_write_packet_size_without_crc], lp_write_packet->data[total_write_packet_size_without_crc+1]);
	printf("total_write_packet_size:%d \ntotal_write_packet_size_without_crc:%d\n", total_write_packet_size, total_write_packet_size_without_crc);
	if (packet_size) *packet_size = total_write_packet_size;
	return lp_write_packet;
}

LPWRITE_IEB100_PACKET make_write_ieb100_packet(char rom_inst, char res_size, char rom_type, const void * data, int data_size, int *packet_size){

	//sizeof(WRITE_PACKET) is included crc
	int total_write_packet_size = sizeof(HEADER_WRITE_IEB100_PACKET) + data_size+1;//included crc
	int body_size_big_end = 4 +1+ 1+data_size;//dummy+res_size+rom_type+data


	LPWRITE_IEB100_PACKET lp_write_packet = (LPWRITE_IEB100_PACKET)malloc(total_write_packet_size);
	memset(lp_write_packet, 0x00, total_write_packet_size);
	lp_write_packet->header.rom_inst = rom_inst;
	lp_write_packet->header.body_size_big_end = body_size_big_end;
	lp_write_packet->header.rom_type = rom_type;
	SwapBytes(&lp_write_packet->header.body_size_big_end, 4);
	lp_write_packet->header.res_size = res_size;
	
	if (data_size > 0) memcpy(lp_write_packet->data, data, data_size);
	if (packet_size) *packet_size = total_write_packet_size;

	printf("total_write_packet_size:%d \body_size_big_end:%d\n", total_write_packet_size, body_size_big_end);

	return lp_write_packet;
}

VAR_BYTES * convert_data(void *pure_data,int data_size){
	VAR_BYTES * pret = (VAR_BYTES *)malloc(4 + data_size);
	pret->allocsize = data_size;
	pret->size = data_size;
	memcpy(pret->buffer, pure_data, data_size);
	return pret;
}

VAR_BYTES * convert_data_ieb100(void *pure_data, int data_size){
	int packet_ieb100_size = 0;
	LPWRITE_IEB100_PACKET lpwrite_ieb100_packet = make_write_ieb100_packet(0x7, 0x24, 0x3, pure_data, data_size, &packet_ieb100_size);

	VAR_BYTES * pret = (VAR_BYTES *)malloc(4 + packet_ieb100_size);
	pret->allocsize = packet_ieb100_size;
	pret->size = packet_ieb100_size;
	memcpy(pret->buffer, lpwrite_ieb100_packet, packet_ieb100_size);
	free(lpwrite_ieb100_packet);
	return pret;
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

int g3api_get_chellange(int chall_size, unsigned char * challenge, int* res_chall_size){
	int packet_size = 0;
	int packet_ieb100_size = 0;
	LPWRITE_PACKET lp_write_packet = make_write_packet(GET_CHAL, chall_size, 0, NULL, 0, &packet_size);
	VAR_BYTES *psend_buff =   convert_data_ieb100(lp_write_packet, packet_size);
	free(lp_write_packet);
	//(LPWRITE_PACKET)malloc(sizeof(WRITE_PACKET));
	//LPWRITE_IEB100_PACKET lpwrite_ieb100_packet = make_write_ieb100_packet(0x7, 0x24, 0x3, lp_write_packet, packet_size, &packet_ieb100_size);

	

	
	//memcpy(challenge, lpwrite_ieb100_packet, packet_ieb100_size);
	
	unsigned char buff[1024] = { 0, };
	int recv_size = 1024;

	_psend((unsigned char *)psend_buff->buffer, psend_buff->size, buff, &recv_size, _etcparam);

	recv_size = buff[0];

	unsigned long calc_crc = calcCRC((unsigned char*)buff , recv_size-2);
	unsigned short crc = 0;
	memcpy(&crc, buff + recv_size - 2,2);
	printf("crc:0x%.4x calc_crc:0x%.4x\n", crc, calc_crc);
	memcpy(challenge, &buff[1], recv_size-3);
	*res_chall_size = recv_size - 3;


	//send_receiv_packet(lpwrite_ieb100_packet, packet_ieb100_size);
	free(psend_buff);
	
	return 0;
}


//START API


	
int g3api_get_device_version(){
	return 0;
}	
	
char* g3api_get_sn(){
	return 0;
}	
	
int g3api_setup_core( SETUP_CORE st_setup_fixed){
	return 0;
}	
	
int g3api_set_up_keys( SET_UP_UNIT_ARRAY keys_configure){
	return 0;
}	
	
	
int g3api_write_key_value(const int key_index, RW_TYPE rw_type,const unsigned char * key_value, int key_value_size){
	return 0;
}	
	
int g3api_read_key_value(const int key_index, RW_TYPE rw_type, unsigned char * key_value, int key_value_size){
	return 0;
}	
	

	
int g3api_verify_passwd(const int key_index,const unsigned char * passwd, int passwd_size){
	return 0;
}	
	
int g3api_change_password(const int key_index,const unsigned char * passwd, int passwd_size){
	return 0;
}	
	
int g3api_init_puf(const int key_index, unsigned int initial){
	return 0;
}	
	
int g3api_sign(const int key_index, SIGN_OPTION ecdsa_option,const unsigned char * msg, int msg_size, void * sign_structure, int structure_size){
	return 0;
}	
	
int g3api_verify(const int key_index, SIGN_OPTION ecdsa_option, bool is_use_cert,const unsigned char * msg, int msg_size,const void * sign_structure, int structure_size){
	return 0;
}	
	
int g3api_verify_dynamic( int key_index, SIGN_OPTION ecdsa_option, bool is_use_cert,const unsigned char * challenge, int chall_size,const unsigned char * sign, int sign_size){
	return 0;
}	
	
int g3api_encryption( int key_index, BLOCK_MODE block_mode,const unsigned char * data, int data_size, ST_IV * iv, unsigned char * cipher, int cipher_size){
	return 0;
}	
	
int g3api_decryption( int key_index, BLOCK_MODE block_mode,const ST_IV * iv, unsigned char * cipher,const int cipher_size, unsigned char * data, int data_size){
	return 0;
}	
	
int g3api_encryption_ecies( int key_index,const unsigned char * data, int data_size, ST_SIGN_ECDSA* rs){
	return 0;
}	
	
int g3api_decryption_ecies( int key_index,const ST_SIGN_ECDSA* rs, unsigned char * data, int data_size){
	return 0;
}	
	
int g3api_ecdh( int key_index,const void * Q_b, int Q_b_size, ST_ECC_PUBLIC* Q_chip, ST_ECC_PUBLIC* ecdh_value){
	return 0;
}	
	
int g3api_session( int key_index){
	return 0;
}	
	
int g3api_diversify( int key_index, DIVERSIFY_MODE diversify_mode, ST_DIVERSIFY_PARAM* param){
	return 0;
}	
	
int g3api_get_public_key( int key_index, PUB_TYPE pub_type, void* pub_key, int structure_size){
	return 0;
}	
	
int g3api_certification( int key_index, CERTIFICATION_WRITE_MODE certification_write_mode,const unsigned char * cert, int cert_size){
	return 0;
}	
	
int g3api_issue_certification( int key_index,const unsigned char * cert, int cert_size){
	return 0;
}	
	
int g3api_reset(){
	return 0;
}	
	//END API






















