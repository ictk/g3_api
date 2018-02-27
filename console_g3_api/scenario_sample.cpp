#include "value_define.h"
#include "g3_api.h"
#include "neoCoLib.h"
#include "neoDebug.h"

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

//START API_SAMPLE

	int ret = 0;
	unsigned char chal[32] ={0,};
	int chal_size = 32;
	
	
	ret = g3api_get_chellange(32 , chal , &chal_size);
	print_result("g3api_get_chellange", ret);
	print_value("chal",chal,chal_size);
	
	
	
	
	
	ret = g3api_verify_passwd(3 , passwd , sizeof(passwd));
	print_result("g3api_verify_passwd", ret);
	
	
	
	
	
	
	ret = g3api_change_password(3 , passwd , sizeof(passwd));
	print_result("g3api_change_password", ret);
	
	
	
	ST_SIGN_ECDSA st_sign_ecdsa ={0,};;
	
	
	ret = g3api_sign(4 , EN_SIGN_OPTION::SIGN_ECDSA , msg_from_sha256 , sizeof(msg_from_sha256) , &st_sign_ecdsa , sizeof(st_sign_ecdsa));
	print_result("g3api_sign", ret);
	print_value("st_sign_ecdsa",&st_sign_ecdsa,sizeof(st_sign_ecdsa));
	
	
	
	
	
	ret = g3api_verify(1 , EN_VERIFY_OPTION::VERYFY_ECDSA , msg_from_sha256 , sizeof(msg_from_sha256) , &st_sign_ecdsa , sizeof(st_sign_ecdsa));
	print_result("g3api_verify", ret);
	
	
	
	
	
	
	ret = g3api_get_chellange(32 , chal , &chal_size);
	print_result("g3api_get_chellange", ret);
	
	
	
	int pos_pub_dynamic=0;
	
	
	
	ret = g3api_dynamic_auth(1 , EN_DYNAMIC_AUTH::DYN_AUTH_ECDSA_SHA256 , pos_pub_dynamic , chal , chal_size , &st_sign_ecdsa , sizeof(st_sign_ecdsa));
	print_result("g3api_dynamic_auth", ret);
	
	
	
	ST_IV st_iv;
	memcpy(&st_iv,iv,sizeof(ST_IV));
	unsigned char outbuff[256] ={0,};
	int out_size = 256;
	
	
	ret = g3api_encryption(8 , EN_BLOCK_MODE::BL_CBC , &st_iv , plain , sizeof(plain) , outbuff , &out_size);
	print_result("g3api_encryption", ret);
	print_value("outbuff",outbuff,out_size);
	
	
	out_size = 256;
	
	
	ret = g3api_decryption(8 , EN_BLOCK_MODE::BL_CBC , &st_iv , cipher_aes_cbc , sizeof(cipher_aes_cbc) , outbuff , &out_size);
	print_result("g3api_decryption", ret);
	print_value("outbuff",outbuff,out_size);
	
	
	
	
	
	ret = g3api_get_chellange(32 , chal , &chal_size);
	print_result("g3api_get_chellange", ret);
	
	
	
	ST_ECIES st_ecies = {0,};
	
	
	ret = g3api_encryption_ecies(1 , &st_ecies);
	print_result("g3api_encryption_ecies", ret);
	print_value("st_ecies",&st_ecies,sizeof(st_ecies));
	
	
	
	
	
	ret = g3api_decryption_ecies(4 , &st_ecies);
	print_result("g3api_decryption_ecies", ret);
	print_value("st_ecies",&st_ecies,sizeof(st_ecies));
	
	
	ST_ECC_PUBLIC st_ecc_pub;
	
	
	ret = g3api_get_public_key(4 , EN_PUB_TYPE::KEY_SECTOR , &st_ecc_pub , sizeof(ST_ECC_PUBLIC));
	print_result("g3api_get_public_key", ret);
	print_value("st_ecc_pub",&st_ecc_pub,sizeof(ST_ECC_PUBLIC));
	
	
	
	
	
	ret = g3api_certification(6 , EN_CERTIFICATION_WRITE_MODE::TO_TEMP , cert , sizeof(cert));
	print_result("g3api_certification", ret);
	
	
	
	//END API_SAMPLE
}