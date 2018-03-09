#include "value_define.h"
#include "g3_api.h"
#include "neoCoLib.h"
#include "neoDebug.h"
#include <openssl/hmac.h>

void print_result(const char * title, int ret);
void print_value(const char * title, const void *buff, int size);
void print_result_value(const char * title, int ret, const void *buff, int size);
void set_buff_from_hexstr(void *pbuff,const char *hexstr);

void general_read_write()
{

	ST_KEY_VALUE recv_key;
	ST_KEY_VALUE write_key;
	int recvbuff_size = 1024;
	int ret = 0;

	ret = g3api_read_key_value(1, EN_AREA_TYPE::KEY_AREA, EN_RW_INST_OPTION::PLAIN_TEXT, &recv_key,  sizeof(ST_KEY_VALUE));
	print_result_value("read key", ret, &recv_key, sizeof(ST_KEY_VALUE));
	
	//printf("ret:0x%x recv %s %d \n", ret, NCL::BytetoHexStr(recvbuff, recvbuff_size).c_str(), recvbuff_size);

	ret = g3api_write_key_value(1, EN_AREA_TYPE::KEY_AREA, EN_RW_INST_OPTION::PLAIN_TEXT, &recv_key, sizeof(ST_KEY_VALUE));
	print_result("write key", ret);
	//printf("ret:0x%x recv %s %d \n", ret, NCL::BytetoHexStr(recvbuff, recvbuff_size).c_str(), recvbuff_size);



	//vecbyte = NCL::HexStr2Byte("72CF56F5BF877DCF5823691682E9824C0B9742D1E0B41D288B478ECEF5218BAA");
	set_buff_from_hexstr(&write_key, "72CF56F5BF877DCF5823691682E9824C0B9742D1E0B41D288B478ECEF5218BAA");
	ret = g3api_write_key_value(0, EN_AREA_TYPE::DATA_AREA_0, EN_RW_INST_OPTION::PLAIN_TEXT, &write_key, sizeof(ST_KEY_VALUE));
	print_result("write key", ret);
	

	//printf("ret:0x%x recv %s %d \n", ret, NCL::BytetoHexStr(recvbuff, recvbuff_size).c_str(), recvbuff_size);

	ret = g3api_read_key_value(0, EN_AREA_TYPE::DATA_AREA_0, EN_RW_INST_OPTION::PLAIN_TEXT, &recv_key, sizeof(ST_KEY_VALUE));

	print_result_value("read key", ret, &recv_key, sizeof(ST_KEY_VALUE));
	

}

void general_sign_verify()
{

	int recvbuff_size = 1024;
	int ret = 0;
	ST_SIGN_ECDSA sign;

	VECBYTE vecbyte = NCL::HexStr2Byte("72CF56F5BF877DCF5823691682E9824C0B9742D1E0B41D288B478ECEF5218BAA");

	ret = g3api_sign(4, EN_SIGN_OPTION::SIGN_ECDSA, V2A(vecbyte), vecbyte.size(), &sign, sizeof(ST_SIGN_ECDSA));
	print_result_value("sign key", ret, &sign, sizeof(ST_SIGN_ECDSA));

	ret = g3api_verify(1, EN_VERIFY_OPTION::VERYFY_ECDSA, V2A(vecbyte), vecbyte.size(), &sign, sizeof(ST_SIGN_ECDSA));
	print_result("g3api_verify key", ret);




}
void test_scenario_sample()
{

	printf("ST_ECIES :%d \n", sizeof(ST_ECIES));
	print_value("msg_org", msg_org, sizeof(msg_org));


	int ret = 0;
	unsigned char chal[256] ={0,};
	int chal_size = 32;
	
	
	ret = g3api_get_chellange(32 , chal , &chal_size);
	print_result("g3api_get_chellange", ret);
	print_value("chal",chal,chal_size);
	
	
	
	
	
	
	ret = g3api_verify_passwd(3 , passwd , sizeof(passwd));
	print_result("g3api_verify_passwd", ret);
	
	
#if 0	
	
	ST_SIGN_ECDSA st_sign_ecdsa ={0,};;
	
	
	int pos_pub_dynamic=0;
	
	ST_IV st_iv;
	memcpy(&st_iv,iv,sizeof(ST_IV));
	unsigned char outbuff[1028] ={0,};
	int out_size = 1028;
	out_size = 256;
	
	ST_ECIES st_ecies = {0,};
	
	ST_ECC_PUBLIC st_ecc_pub;
	
	ST_ECC_PUBLIC Q_chip ={0,};
	ST_ECDH_KEY_BLOCK st_ecdh_key_block = {0,};
	ST_ECDH_RANDOM st_ecdh_random ={0,};
	
	
	ret = g3api_ecdh(EN_ECDH_MODE::GEN_TLS_BLOCK , outer_pub_key , sizeof(outer_pub_key) , &st_ecdh_random , &Q_chip , &st_ecdh_key_block , sizeof(ST_ECDH_KEY_BLOCK));
	print_result("g3api_ecdh", ret);
	print_value("st_ecdh_key_block",&st_ecdh_key_block,sizeof(ST_ECDH_KEY_BLOCK));
	print_value("Q_chip",&Q_chip,sizeof(ST_ECC_PUBLIC));
	
	
	
	ST_ECDH_IV st_ecdh_iv = { 0, };
	memcpy(&st_ecdh_random, server_ecdh_random, sizeof(server_ecdh_random));
	
	ret = g3api_ecdh(EN_ECDH_MODE::SET_TLS_SESSION_KEY, outer_pub_key, sizeof(outer_pub_key), &st_ecdh_random, &Q_chip, &st_ecdh_iv, sizeof(ST_ECDH_IV));
	print_result("g3api_ecdh", ret);
	print_value("st_ecdh_iv",&st_ecdh_iv,sizeof(ST_ECDH_IV));
	print_value("Q_chip",&Q_chip,sizeof(ST_ECC_PUBLIC));
	

	
	ST_IV client_iv = {0,};
	ST_DATA_16
	 head_rand = {0,};
	
	memcpy(&client_iv,st_ecdh_key_block.client_iv,sizeof(ST_IV));
	out_size = 1028;
	
	
	ret = g3api_tls_mac_encrypt(0 , EN_CONTENT_TYPE::APPLICATION_DATA , EN_TLS_VERSION::TLS_1_2 , &client_iv , &head_rand , msg_org , sizeof(msg_org) , outbuff , &out_size);
	print_result("g3api_tls_mac_encrypt", ret);
	print_value("outbuff",outbuff,out_size);
	
	
	
	//ST_IV server_iv = {0,};
	//memcpy(&server_iv,st_ecdh_key_block.server_iv,sizeof(ST_IV));
	unsigned char outbuff2[1024] ={0,};
	int out_size2 = 1024;

	
	ret = g3api_tls_decrypt_verify(0, (EN_CONTENT_TYPE)1, EN_TLS_VERSION::TLS_1_2, (ST_IV*)server_iv, server_cipher, sizeof(server_cipher), &head_rand, outbuff2, &out_size2);
	print_result("g3api_tls_decrypt_verify", ret);
	print_value("head_rand", &head_rand, sizeof(ST_DATA_16));
	print_value("outbuff", outbuff2, out_size2);
#endif
	
	ret = g3api_certification(6, EN_CERTIFICATION_WRITE_MODE::TO_KEY_SECTOR, cert, sizeof(cert));
	print_result("g3api_certification", ret);

	
}
void test_scenario_sample_ref()
{

	printf("ST_ECIES :%d \n", sizeof(ST_ECIES));
	print_value("msg_org", msg_org, sizeof(msg_org));
	//START API_SAMPLE

	int ret = 0;
	unsigned char chal[32] ={0,};
	int chal_size = 32;
	
	
	ret = g3api_get_chellange(32 , chal , &chal_size);
	print_result("g3api_get_chellange", ret);
	print_value("chal",chal,chal_size);
	
	
	
	
	
	
	ret = g3api_verify_passwd(3 , passwd , sizeof(passwd));
	print_result("g3api_verify_passwd", ret);
	
	
	
	
	ST_SIGN_ECDSA st_sign_ecdsa ={0,};;
	
	
	int pos_pub_dynamic=0;
	
	ST_IV st_iv;
	memcpy(&st_iv,iv,sizeof(ST_IV));
	unsigned char outbuff[1028] ={0,};
	int out_size = 1028;
	out_size = 256;
	
	ST_ECIES st_ecies = {0,};
	
	ST_ECC_PUBLIC st_ecc_pub;
	
	
	
	ret = g3api_certification(6 , EN_CERTIFICATION_WRITE_MODE::TO_TEMP , cert , sizeof(cert));
	print_result("g3api_certification", ret);
	
	
	
	ST_ECC_PUBLIC Q_chip ={0,};
	ST_ECDH_KEY_BLOCK st_ecdh_key_block = {0,};
	ST_ECDH_RANDOM st_ecdh_random ={0,};
	
	
	ret = g3api_ecdh(EN_ECDH_MODE::GEN_TLS_BLOCK , outer_pub_key , sizeof(outer_pub_key) , &st_ecdh_random , &Q_chip , &st_ecdh_key_block , sizeof(ST_ECDH_KEY_BLOCK));
	print_result("g3api_ecdh", ret);
	print_value("st_ecdh_key_block",&st_ecdh_key_block,sizeof(ST_ECDH_KEY_BLOCK));
	print_value("Q_chip",&Q_chip,sizeof(ST_ECC_PUBLIC));
	
	
	
	ST_ECDH_IV st_ecdh_iv = { 0, };
	
	
	ret = g3api_ecdh(EN_ECDH_MODE::SET_TLS_SESSION_KEY , outer_pub_key , sizeof(outer_pub_key) , &st_ecdh_random , &Q_chip , &st_ecdh_iv , sizeof(ST_ECDH_KEY_BLOCK));
	print_result("g3api_ecdh", ret);
	print_value("st_ecdh_iv",&st_ecdh_iv,sizeof(ST_ECDH_IV));
	print_value("Q_chip",&Q_chip,sizeof(ST_ECC_PUBLIC));
	
	
	
	ST_IV client_iv = {0,};
	ST_DATA_16
	 head_rand = {0,};
	
	memcpy(&client_iv,st_ecdh_key_block.client_iv,sizeof(ST_IV));
	out_size = 1028;
	
	
	ret = g3api_tls_mac_encrypt(0 , EN_CONTENT_TYPE::APPLICATION_DATA , EN_TLS_VERSION::TLS_1_2 , &client_iv , &head_rand , msg_org , sizeof(msg_org) , outbuff , &out_size);
	print_result("g3api_tls_mac_encrypt", ret);
	print_value("outbuff",outbuff,out_size);
	
	
	
	ST_IV server_iv = {0,};
	memcpy(&server_iv,st_ecdh_key_block.server_iv,sizeof(ST_IV));
	unsigned char outbuff2[256] ={0,};
	int out_size2 = 256;
	
	
	ret = g3api_tls_decrypt_verify(0 , EN_CONTENT_TYPE::APPLICATION_DATA , EN_TLS_VERSION::TLS_1_2 , &server_iv , outbuff , out_size , &head_rand , outbuff2 , &out_size2);
	print_result("g3api_tls_decrypt_verify", ret);
	
	
	
	//END API_SAMPLE
}