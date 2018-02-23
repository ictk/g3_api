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

	ret = g3api_read_key_value(1, EN_AREA_TYPE::KEY_AREA, EN_RW_INST_OPTION::PLAIN_TEXT, &recv_key,NULL,NULL);
	print_result_value("read key", ret, &recv_key, sizeof(ST_KEY_VALUE));
	
	//printf("ret:0x%x recv %s %d \n", ret, NCL::BytetoHexStr(recvbuff, recvbuff_size).c_str(), recvbuff_size);

	ret = g3api_write_key_value(1, EN_AREA_TYPE::KEY_AREA, EN_RW_INST_OPTION::PLAIN_TEXT, &recv_key, NULL, NULL);
	print_result("write key", ret);
	//printf("ret:0x%x recv %s %d \n", ret, NCL::BytetoHexStr(recvbuff, recvbuff_size).c_str(), recvbuff_size);



	//vecbyte = NCL::HexStr2Byte("72CF56F5BF877DCF5823691682E9824C0B9742D1E0B41D288B478ECEF5218BAA");
	set_buff_from_hexstr(&write_key, "72CF56F5BF877DCF5823691682E9824C0B9742D1E0B41D288B478ECEF5218BAA");
	ret = g3api_write_key_value(0, EN_AREA_TYPE::DATA_AREA_0, EN_RW_INST_OPTION::PLAIN_TEXT, &write_key,NULL,NULL);
	print_result("write key", ret);
	

	//printf("ret:0x%x recv %s %d \n", ret, NCL::BytetoHexStr(recvbuff, recvbuff_size).c_str(), recvbuff_size);

	ret = g3api_read_key_value(0, EN_AREA_TYPE::DATA_AREA_0, EN_RW_INST_OPTION::PLAIN_TEXT, &recv_key,NULL,NULL);
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
