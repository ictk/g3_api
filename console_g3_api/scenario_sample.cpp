#include "value_define.h"

#include "neoCoLib.h"
#include "neoDebug.h"
#include <g3_api.h>
//#include <openssl/hmac.h>
#include "util.h"

void print_result_value(const char * title, int ret, const void *buff, int size);
void set_buff_from_hexstr(void *pbuff,const char *hexstr);

void initialize()
{
	ST_KEY_VALUE recv_key;
	ST_KEY_VALUE write_key;
	byte rcv_buffer[1024];
	int rcv_buffer_size = 1024;

	int ret = 0;

	const unsigned char passwd2[] = { 0x11, 0x22, 0x33, 0x44 };

	// get Root_AC
	ret = g3api_verify_passwd(0, passwd2, sizeof(passwd2));
	print_result("g3api_verify_passwd", ret);

	// write setup area sector 4
	set_buff_from_hexstr(&write_key, "80540000000000004E5400000000000000540000000000000054000000000000");
	ret = g3api_write_key_value(4, SETUP_AREA, PLAIN_TEXT, &write_key, sizeof(ST_KEY_VALUE));
	print_result("init  write key", ret);

	// write setup area sector 2
	set_buff_from_hexstr(&write_key, "0E00000000000000005400000000000000540000000000000054000000000000");
	ret = g3api_write_key_value(2, SETUP_AREA, PLAIN_TEXT, &write_key, sizeof(ST_KEY_VALUE));
	print_result("init  write key", ret);

	// write key area sector 0
	set_buff_from_hexstr(&write_key, "0405050511223344000000000000000000000000000000000000000000000000");
	ret = g3api_write_key_value(0, KEY_AREA, PLAIN_TEXT, &write_key, sizeof(ST_KEY_VALUE));
	print_result("init  write key", ret);

	// get Root_AC
	ret = g3api_verify_passwd(0, passwd2, sizeof(passwd2));
	print_result("g3api_verify_passwd", ret);
}

void general_read_write()
{
	ST_KEY_VALUE recv_key;
	ST_KEY_VALUE write_key;
	byte rcv_buffer[1024];
	int rcv_buffer_size = 32;

	const unsigned char passwd2[] = { 0x11, 0x22, 0x33, 0x44 };
	int ret = 0;

	byte msg[48];
	int msg_size = 32;

	ST_SIGN_SYMM sign;

	ST_RW_DATA_WITH_IV write_iv;
	ST_RW_DATA_WITH_IV read_iv;

	ST_RW_DATA_WITH_IV_MAC write_mac;
	ST_RW_DATA_WITH_IV_MAC read_mac;

	ST_DATA_64 write_mask;
	ST_RW_DATA_WITH_MASK write_with_mask;
	byte session_mac[64];
	byte signature[16];
	ST_IV session_iv;
	byte session_key[32];
	int session_key_size = 16;

	// write setup area sector 10
	set_buff_from_hexstr(&write_key, "9E540000000000009E031B001B0000009E001B001B0000004E54000000000000");
	ret = g3api_write_key_value(10, SETUP_AREA, PLAIN_TEXT, &write_key, sizeof(ST_KEY_VALUE));
	print_result("write key setup 10", ret);

	// write key area sector 27 ( aes128_key )
	set_buff_from_hexstr(&write_key, "6B8B3A2D115E4683A540FF6C1515A13D21AABF36472D3C112FD134AD5F4F3122");
	ret = g3api_write_key_value(27, KEY_AREA, PLAIN_TEXT, &write_key, sizeof(ST_KEY_VALUE));
	print_result("write key 27", ret);

	// sign & verify dynamic_auth sector 27
	ret = g3api_get_challenge(32, msg + 16, &msg_size);
	print_result("g3api_get_challenge", ret);
	print_value("challenge_value", msg + 16, msg_size);

	ret = g3api_sign(27, SIGN_SYMM, msg + 16, msg_size, &sign, sizeof(ST_SIGN_SYMM));
	print_result_value("sign key_symm 27", ret, &sign, sizeof(ST_SIGN_SYMM));

	set_buff_from_hexstr(msg, "861B0003000000000000000000000000");
	ret = g3api_dynamic_auth(27, DYN_AUTH_SYMM, 0x10, msg, sizeof(msg), &sign, sizeof(ST_SIGN_SYMM));
	print_result("g3api_verify dynamic auth 27", ret);

	// session_key
	memset(session_key, 0, sizeof(ST_DATA_32));
	set_buff_from_hexstr(&session_iv, "871B1023000000000000000000000000");
	memcpy(signature, &sign, 16);
	ret = g3api_encryption(27, SECTOR_KEY, BL_CBC, &session_iv, signature, sizeof(ST_SIGN_SYMM), session_key, &session_key_size);
	ret = g3api_write_key_value(1, KEY_AREA, PLAIN_TEXT, session_key, sizeof(ST_KEY_VALUE));
	
	// write key area sector 24
	set_buff_from_hexstr(&write_key, "A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0");
	ret = g3api_write_key_value(24, KEY_AREA, PLAIN_TEXT, &write_key, sizeof(ST_KEY_VALUE));
	print_result("write key 24", ret);
	
	// write data0 area sector 0
	set_buff_from_hexstr(&write_key, "A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0");
	ret = g3api_write_key_value(0, DATA_AREA_0, PLAIN_TEXT, &write_key, sizeof(ST_KEY_VALUE));
	print_result("write key data0 0", ret);

	// write data1 area sector 0
	set_buff_from_hexstr(&write_key, "A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0");
	ret = g3api_write_key_value(0, DATA_AREA_1, PLAIN_TEXT, &write_key, sizeof(ST_KEY_VALUE));
	print_result("write key data1 0", ret);

	// write key area sector 26 iv
	set_buff_from_hexstr(&write_iv, "10D1079D8F2862AA39CF960BF45A47B5370DBE0D9992F840C243FF763EA37C2E811A0101000000000000000000000000");
	ret = g3api_write_key_value(26, KEY_AREA, CBC, &write_iv, sizeof(ST_RW_DATA_WITH_IV));
	print_result("write key 26", ret);
	
	// write key area sector 26 session cbc
	set_buff_from_hexstr(&write_iv, "7F0E62ED59A6DA36B296D95BEDDD2370B5C225819C1B649C0AA9226430ED4456811A1101000000000000000000000000");
	ret = g3api_write_key_value(26, KEY_AREA, SESSION_KEY_CBC, &write_iv, sizeof(ST_RW_DATA_WITH_IV));
	print_result("write key 26 session cbc", ret);

	// write key area sector 26 session cbc with mac
	memset(msg, 0, 48);
	memset(rcv_buffer, 0, 1024);
	set_buff_from_hexstr(&session_iv, "811A1501000000000000000000000000");
	set_buff_from_hexstr(msg, "A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0");
	// cipher_text
	ret = g3api_encryption(1, SECTOR_KEY, BL_CBC, &session_iv, msg, msg_size, rcv_buffer, &rcv_buffer_size);
	//print_result_value("session_cipher_text", ret, rcv_buffer, rcv_buffer_size);
	memcpy(rcv_buffer + 32, &session_iv, sizeof(ST_IV));
	// mac
	ret = g3api_encryption(1, SECTOR_KEY, BL_CBC, &session_iv, rcv_buffer, rcv_buffer_size, rcv_buffer + 16 + 32, &rcv_buffer_size);
	memcpy(rcv_buffer + 48, rcv_buffer + 48 + 16, 16);
	ret = g3api_write_key_value(26, KEY_AREA, SESSION_KEY_CBC_with_MAC, rcv_buffer, sizeof(ST_RW_DATA_WITH_IV_MAC));
	print_result("write key 26 session cbc mac", ret);
	
	
	// write key area sector 25 with mac
	set_buff_from_hexstr(&write_mac, "D458239ADBF1AA69486D0C492A3F5D3CA32B45E041BFB917ACE8CA23A47922C681190501000000000000000000000000A1D8C26F685D944F67D6C31CE43EA944");
	ret = g3api_write_key_value(25, KEY_AREA, CBC_with_MAC, &write_mac, sizeof(ST_RW_DATA_WITH_IV_MAC));
	print_result("write key with mac", ret);

	// write key area sector 24 mask
	set_buff_from_hexstr(&write_with_mask, "0000000000000000000000000000000000000000000000000000000000000000A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0");
	ret = g3api_write_key_value(24, KEY_AREA, MASKED, &write_with_mask, sizeof(ST_RW_DATA_WITH_MASK));
	print_result("write key 24 mask", ret);

	// read setup area sector 10
	ret = g3api_read_key_value(10, SETUP_AREA, PLAIN_TEXT, NULL, 0, &recv_key,  sizeof(ST_KEY_VALUE));
	print_result_value("read key setup 10", ret, &recv_key, sizeof(ST_KEY_VALUE));
	memset(&recv_key, 0, sizeof(ST_KEY_VALUE));

	// read key area sector 24
	set_buff_from_hexstr(&write_key, "0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A");
	ret = g3api_read_key_value(24, KEY_AREA, MASKED, &write_key, sizeof(ST_KEY_VALUE), &recv_key, sizeof(ST_KEY_VALUE));
	print_result_value("read key 24 mask", ret, &recv_key, sizeof(ST_KEY_VALUE));
	memset(&recv_key, 0, sizeof(ST_KEY_VALUE));

	// read key area sector 25
	ret = g3api_read_key_value(25, KEY_AREA, CBC_with_MAC, NULL, 0, &read_mac, sizeof(ST_RW_DATA_WITH_IV_MAC));
	print_result_value("read key 25 mac", ret, &read_mac, sizeof(ST_RW_DATA_WITH_IV_MAC));
	memset(&read_mac, 0, sizeof(ST_RW_DATA_WITH_IV_MAC));
	
	// read key area sector 26 iv
	ret = g3api_read_key_value(26, KEY_AREA, CBC, NULL, 0, &read_iv, sizeof(ST_RW_DATA_WITH_IV));
	print_result_value("read key 26 iv", ret, &read_iv, sizeof(ST_RW_DATA_WITH_IV));
	memset(&read_iv, 0, sizeof(ST_RW_DATA_WITH_IV));
	

	// read key area sector 26 session cbc
	ret = g3api_read_key_value(26, KEY_AREA, SESSION_KEY_CBC, NULL, 0, &read_iv, sizeof(ST_RW_DATA_WITH_IV));
	print_result_value("read key 26 session cbc", ret, &read_iv, sizeof(ST_RW_DATA_WITH_IV));
	memset(&read_iv, 0, sizeof(ST_RW_DATA_WITH_IV));
	

	// read key area sector 26 session cbc mac
	ret = g3api_read_key_value(26, KEY_AREA, SESSION_KEY_CBC_with_MAC, NULL, 0, &read_mac, sizeof(ST_RW_DATA_WITH_IV_MAC));
	print_result_value("read key 26 session cbc mac", ret, &read_mac, sizeof(ST_RW_DATA_WITH_IV_MAC));
	memset(&read_mac, 0, sizeof(ST_RW_DATA_WITH_IV_MAC));
	
	// read data0 area secotr 0
	ret = g3api_read_key_value(0, DATA_AREA_0, PLAIN_TEXT, NULL, 0, &recv_key, sizeof(ST_KEY_VALUE));
	print_result_value("read key data0 0", ret, &recv_key, sizeof(ST_KEY_VALUE));
	memset(&recv_key, 0, sizeof(ST_KEY_VALUE));

	// read data1 area sector 0
	ret = g3api_read_key_value(0, DATA_AREA_1, PLAIN_TEXT, NULL, 0, &recv_key, sizeof(ST_KEY_VALUE));
	print_result_value("read key data1 0", ret, &recv_key, sizeof(ST_KEY_VALUE));
	memset(&recv_key, 0, sizeof(ST_KEY_VALUE));
	

}
void general_password()
{
	ST_KEY_VALUE recv_key;
	ST_KEY_VALUE write_key;
	byte rcv_buffer[1024];
	int rcv_buffer_size = 32;

	const unsigned char passwd2[] = { 0x11, 0x22, 0x33, 0x44 };
	const unsigned char passwd3[] = { 0x11, 0x22, 0x33, 0x45 };
	int ret = 0;


	// write setup area sector 11
	set_buff_from_hexstr(&write_key, "8E540000000000008E540000000000008E540000000000008E54000000000000");
	ret = g3api_write_key_value(11, SETUP_AREA, PLAIN_TEXT, &write_key, sizeof(ST_KEY_VALUE));
	print_result("write key", ret);

	// write key area sector 28
	set_buff_from_hexstr(&write_key, "0403050511223344000000000000000000000000000000000000000000000000");
	ret = g3api_write_key_value(28, KEY_AREA, PLAIN_TEXT, &write_key, sizeof(ST_KEY_VALUE));
	print_result("write key", ret);

	// write key area sector 29
	set_buff_from_hexstr(&write_key, "0403050511223344000000000000000000000000000000000000000000000000");
	ret = g3api_write_key_value(28, KEY_AREA, PLAIN_TEXT, &write_key, sizeof(ST_KEY_VALUE));
	print_result("write key", ret);

	// verify password sector 28 ( valid )
	ret = g3api_verify_passwd(28, passwd2, sizeof(passwd2));
	print_result("g3api_verify_passwd", ret);

	// verify password sector 28 ( invalid )
	ret = g3api_verify_passwd(28, passwd3, sizeof(passwd2));
	print_result("g3api_verify_passwd", ret);

	// verify password sector 28 ( invalid )
	ret = g3api_verify_passwd(28, passwd3, sizeof(passwd2));
	print_result("g3api_verify_passwd", ret);

	// verify password sector 28 ( invalid )
	ret = g3api_verify_passwd(28, passwd3, sizeof(passwd2));
	print_result("g3api_verify_passwd", ret);

	// verify password sector 28 ( invalid )
	ret = g3api_verify_passwd(28, passwd3, sizeof(passwd2));
	print_result("g3api_verify_passwd", ret);

	// verify password sector 28 ( invalid )
	ret = g3api_verify_passwd(28, passwd3, sizeof(passwd2));
	print_result("g3api_verify_passwd", ret);

	// verify password sector 28 ( invalid )
	ret = g3api_verify_passwd(28, passwd3, sizeof(passwd2));
	print_result("g3api_verify_passwd", ret);

	// change password sector 28
	ret = g3api_change_password(28, passwd3, sizeof(passwd3));
	print_result("g3api_change_passwd", ret);

	// verify password sector 28 ( valid )
	ret = g3api_verify_passwd(28, passwd3, sizeof(passwd2));
	print_result("g3api_verify_passwd", ret);
}
void general_sign_verify()
{
	ST_KEY_VALUE recv_key;
	ST_KEY_VALUE write_key;
	byte rcv_buffer[1024];
	int rcv_buffer_size = 1024;

	ST_SIGN_ECDSA sign;
	ST_SIGN_HMAC sign2;
	ST_SIGN_SYMM sign3;

	ST_DATA_32 st_data_32;

	const unsigned char passwd2[] = { 0x11, 0x22, 0x33, 0x44 };
	byte msg[48];
	int msg_size = 32;

	byte symm_input[48];
	int ret = 0;

	byte session_b[16];
	byte session_out[32];
	int session_out_size = 32;


	// write setup area sector 12
	set_buff_from_hexstr(&write_key, "4E540000000000002E540000000000003E540000000000000E54000000000000");
	ret = g3api_write_key_value(12, SETUP_AREA, PLAIN_TEXT, &write_key, sizeof(ST_KEY_VALUE));
	print_result("write key", ret);

	// write key area sector 32 ( aes128_key )
	set_buff_from_hexstr(&write_key, "6B8B3A2D115E4683A540FF6C1515A13D21AABF36472D3C112FD134AD5F4F3122");
	ret = g3api_write_key_value(32, KEY_AREA, PLAIN_TEXT, &write_key, sizeof(ST_KEY_VALUE));
	print_result("write key", ret);

	// write key area sector 33 ( ecc_prv_key )
	set_buff_from_hexstr(&write_key, "8F0511C5F59C131D60BB96A12C07AB0D3E4D75D1CEE4FD747DF41D41696AA2A3");
	ret = g3api_write_key_value(33, KEY_AREA, PLAIN_TEXT, &write_key, sizeof(ST_KEY_VALUE));
	print_result("write key", ret);

	// write key area sector 34 ( ecc_pub_key_1 )
	set_buff_from_hexstr(&write_key, "7CC2F04BFCB22ACD94A230EAA57D90FD65AD7CDC16695FB3A1C4A71D7A2E7481");
	ret = g3api_write_key_value(34, KEY_AREA, PLAIN_TEXT, &write_key, sizeof(ST_KEY_VALUE));
	print_result("write key", ret);

	// write key area sector 35 ( ecc_pub_key_2 )
	set_buff_from_hexstr(&write_key, "961F49DCD5F33971FBF0320BA3CEB6F6A1CB8EA2D98AEBC24B023197EB76C625");
	ret = g3api_write_key_value(35, KEY_AREA, PLAIN_TEXT, &write_key, sizeof(ST_KEY_VALUE));
	print_result("write key", ret);

	VECBYTE vecbyte = NCL::HexStr2Byte("72CF56F5BF877DCF5823691682E9824C0B9742D1E0B41D288B478ECEF5218BAA");

	// sign&verify - ECDSA_EX_HASH
	ret = g3api_sign(33, SIGN_ECDSA_EXT_SHA256, V2A(vecbyte), vecbyte.size(), &sign, sizeof(ST_SIGN_ECDSA));
	print_result_value("sign key_ecdsa_ex_hash", ret, &sign, sizeof(ST_SIGN_ECDSA));

	ret = g3api_verify(34, VERIFY_ECDSA_EXT_SHA256, V2A(vecbyte), vecbyte.size(), &sign, sizeof(ST_SIGN_ECDSA));
	print_result("g3api_verify key_ecdsa_ex_hash", ret);

	// sign&verify - ECDSA_SHA256
	ret = g3api_sign(33, SIGN_ECDSA_WITH_SHA256, V2A(vecbyte), vecbyte.size(), &sign, sizeof(ST_SIGN_ECDSA));
	print_result_value("sign key_ecdsa_sha256", ret, &sign, sizeof(ST_SIGN_ECDSA));

	ret = g3api_verify(34, VERIFY_ECDSA_WITH_SHA256, V2A(vecbyte), vecbyte.size(), &sign, sizeof(ST_SIGN_ECDSA));
	print_result("g3api_verify key_ecdsa_sha256", ret);

	// sign&verify - symmetric
	ret = g3api_sign(32, SIGN_SYMM, V2A(vecbyte), vecbyte.size(), &sign3, sizeof(ST_SIGN_SYMM));
	print_result_value("sign key_symm", ret, &sign3, sizeof(ST_SIGN_SYMM));
	 
	set_buff_from_hexstr(symm_input, "8620000300000000000000000000000072CF56F5BF877DCF5823691682E9824C0B9742D1E0B41D288B478ECEF5218BAA");

	ret = g3api_verify(32, VERIFY_SYMM, symm_input, sizeof(symm_input), &sign3, sizeof(ST_SIGN_SYMM));
	print_result("g3api_verify key_symm", ret);
	memset(&sign3, 0, sizeof(ST_SIGN_SYMM));

	// sign&verify - symmetric session key
	set_buff_from_hexstr(session_b, "4A5E31F5D1D5B6C438D1F155A1F3FE5A");
	ret = g3api_session(32, SYMM_KEY, session_b, sizeof(session_b), session_out, &session_out_size);
	print_result_value("session_ins", ret, session_out, session_out_size);

	ret = g3api_sign(0, SIGN_SESSION_SYMM, V2A(vecbyte), vecbyte.size(), &sign3, sizeof(ST_SIGN_SYMM));
	print_result_value("sign key symmetric session key", ret, &sign3, sizeof(ST_SIGN_SYMM));

	set_buff_from_hexstr(symm_input, "8600000400000000000000000000000072CF56F5BF877DCF5823691682E9824C0B9742D1E0B41D288B478ECEF5218BAA");

	ret = g3api_verify(0, VERIFY_SESSION_SYMM, symm_input, sizeof(symm_input), &sign3, sizeof(ST_SIGN_SYMM));
	print_result("g3api verify symmetric session key", ret);
	memset(&sign3, 0, sizeof(ST_SIGN_SYMM));


	// sign & verify  - dynamic_auth symmetric
	ret = g3api_get_challenge(32, msg + 16, &msg_size);
	print_result("g3api_get_challenge", ret);
	print_value("challenge_value(1)", msg + 16, msg_size);

	ret = g3api_sign(32, SIGN_SYMM, msg + 16, msg_size, &sign3, sizeof(ST_SIGN_SYMM));
	print_result_value("sign key_symm", ret, &sign3, sizeof(ST_SIGN_SYMM));

	set_buff_from_hexstr(msg, "86200003000000000000000000000000");
	ret = g3api_dynamic_auth(32, DYN_AUTH_SYMM, 0x10, msg, sizeof(msg), &sign3, sizeof(ST_SIGN_SYMM));
	print_result("g3api_verify dynamic authentication symmetric", ret);


	// sign & verify - dynamic authentication ECDSA with SHA256
	memset(msg, 0, sizeof(msg));
	ret = g3api_get_challenge(32, msg, &msg_size);
	print_result("g3api_get_challenge", ret);
	print_value("challenge_value(2)", msg, msg_size);

	memset(&sign, 0, sizeof(sign));
	ret = g3api_sign(33, SIGN_ECDSA_WITH_SHA256, msg, msg_size, &sign, sizeof(ST_SIGN_ECDSA));
	print_result_value("sign key ecdsa", ret, &sign, sizeof(ST_SIGN_ECDSA));

	ret = g3api_dynamic_auth(34, DYN_AUTH_ECDSA_SHA256, 0x00, msg, msg_size, &sign, sizeof(ST_SIGN_ECDSA));
	print_result("g3api verify dynamic authentication ecdsa sha256", ret);


	// write setup area sector 12
	set_buff_from_hexstr(&write_key, "4E540000000000007E540000000000003E540000000000000E54000000000000");
	ret = g3api_write_key_value(12, SETUP_AREA, PLAIN_TEXT, &write_key, sizeof(ST_KEY_VALUE));
	print_result("write key", ret);

	// write key area sector 32 ( SHA256 )
	set_buff_from_hexstr(&write_key, "6B8B3A2D115E4683A540FF6C1515A13D21AABF36472D3C112FD134AD5F4F3122");
	ret = g3api_write_key_value(33, KEY_AREA, PLAIN_TEXT, &write_key, sizeof(ST_KEY_VALUE));
	print_result("write key", ret);

	// sign&verify - hmac
	ret = g3api_sign(33, SIGN_HMAC, V2A(vecbyte), vecbyte.size(), &sign2, sizeof(ST_SIGN_HMAC));
	print_result_value("sign key hmac", ret, &sign2, sizeof(ST_SIGN_HMAC));

	ret = g3api_verify(33, VERIFY_HMAC, V2A(vecbyte), vecbyte.size(), &sign2, sizeof(ST_SIGN_HMAC));
	print_result("g3api_verify key hmac", ret);

	ret = g3api_set_extern_public_key(ext_pubkey, sizeof(ext_pubkey), &st_data_32);
	print_result("g3api_set_extern_public_key key", ret);
	print_value("chal", &st_data_32, sizeof(ST_DATA_32));

	ret = g3api_verify(1, VERIFY_EXT_PUB_ECDSA_WITH_SHA256, org_msg, sizeof(org_msg), sign_rs, sizeof(sign_rs));
	print_result("g3api_verify key_ext_sha256", ret);

	ret = g3api_verify(1, VERIFY_EXT_PUB_ECDSA_EXT_SHA256, org_msg_hash, sizeof(org_msg_hash), sign_rs, sizeof(sign_rs));
	print_result("g3api_verify key_ext_ex_hash", ret);



}
void general_enc_dec()
{
	ST_KEY_VALUE recv_key;
	ST_KEY_VALUE write_key;
	byte rcv_buffer[1024];
	int rcv_buffer_size = 32;

	const unsigned char passwd2[] = { 0x11, 0x22, 0x33, 0x44 };
	int ret = 0;

	ST_IV iv;
	byte plain_text[16],cipher_text[16];
	int cipher_text_size = 16;

	ST_ECIES ecies;
	byte msg[32];
	int msg_size = 32;

	byte session_b[16];
	byte session_out[32];
	int session_out_size = 32;


	// write setup area sector 13
	set_buff_from_hexstr(&write_key, "4E540000000000002E540000000000003E540000000000000E54000000000000");
	ret = g3api_write_key_value(13, SETUP_AREA, PLAIN_TEXT, &write_key, sizeof(ST_KEY_VALUE));
	print_result("write key", ret);

	// write key area sector 36 ( aes128_key )
	set_buff_from_hexstr(&write_key, "6B8B3A2D115E4683A540FF6C1515A13D21AABF36472D3C112FD134AD5F4F3122");
	ret = g3api_write_key_value(36, KEY_AREA, PLAIN_TEXT, &write_key, sizeof(ST_KEY_VALUE));
	print_result("write key", ret);

	// write key area sector 37 ( ecc_prv_key )
	set_buff_from_hexstr(&write_key, "8F0511C5F59C131D60BB96A12C07AB0D3E4D75D1CEE4FD747DF41D41696AA2A3");
	ret = g3api_write_key_value(37, KEY_AREA, PLAIN_TEXT, &write_key, sizeof(ST_KEY_VALUE));
	print_result("write key", ret);

	// write key area sector 38 ( ecc_pub_key_1 )
	set_buff_from_hexstr(&write_key, "7CC2F04BFCB22ACD94A230EAA57D90FD65AD7CDC16695FB3A1C4A71D7A2E7481");
	ret = g3api_write_key_value(38, KEY_AREA, PLAIN_TEXT, &write_key, sizeof(ST_KEY_VALUE));
	print_result("write key", ret);

	// write key area sector 39 ( ecc_pub_key_2 )
	set_buff_from_hexstr(&write_key, "961F49DCD5F33971FbF0320BA3CEB6F6A1CB8EA2D98AEBC24B023197EB76C625");
	ret = g3api_write_key_value(39, KEY_AREA, PLAIN_TEXT, &write_key, sizeof(ST_KEY_VALUE));
	print_result("write key", ret);

	// encrypt_cbc
	set_buff_from_hexstr(&iv, "00000000000000000000000000000000");
	set_buff_from_hexstr(plain_text, "A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0");
	ret = g3api_encryption(36, SECTOR_KEY, BL_CBC, &iv, plain_text, sizeof(plain_text), cipher_text, &cipher_text_size);
	print_result("encrypt cbc", ret);
	print_value("cipher text", cipher_text, sizeof(cipher_text));

	memset(plain_text, 0, sizeof(plain_text));

	// decrpyt_cbc
	ret = g3api_decryption(36, SECTOR_KEY, BL_CBC, &iv, cipher_text, sizeof(cipher_text), plain_text, &cipher_text_size);
	print_result("decrypt cbc", ret);
	print_value("plain text", plain_text, sizeof(plain_text));

	memset(cipher_text, 0, cipher_text_size);

	// encrypt_ecies
	ret = g3api_get_challenge(32, msg, &msg_size);
	print_result("g3api_get_challenge", ret);
	print_value("challenge_value", msg, msg_size);
	
	ret = g3api_encryption_ecies(38, &ecies);
	print_result("encrpyt ecies", ret);
	//print_value("ecies->r", (ecies->r, sizeof(ecies->r));
	//print_value("ecies->s", ecies->s, sizeof(ecies->s));

	// decrypt_ecies
	ret = g3api_decryption_ecies(37, &ecies);
	print_result("decrpyt ecies", ret);

	// session_
	set_buff_from_hexstr(session_b, "4A5E31F5D1D5B6C438D1F155A1F3FE5A");
	ret = g3api_session(36, SYMM_KEY, session_b, sizeof(session_b), session_out, &session_out_size);
	print_result_value("session_ins", ret, session_out, session_out_size);

	// enc_session_key
	set_buff_from_hexstr(&iv, "00000000000000000000000000000000");
	set_buff_from_hexstr(plain_text, "A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0");
	ret = g3api_encryption(0, SESSION_KEY, BL_CBC, &iv, plain_text, sizeof(plain_text), cipher_text, &cipher_text_size);
	print_result_value("enc_session_key", ret, cipher_text,cipher_text_size);
	memset(plain_text, 0, sizeof(plain_text));

	// dec_session_key
	ret = g3api_decryption(0, SESSION_KEY, BL_CBC, &iv, cipher_text, sizeof(cipher_text), plain_text, &cipher_text_size);
	print_result_value("dec_session_key", ret, plain_text, sizeof(plain_text));

	memset(cipher_text, 0, cipher_text_size);
	memset(plain_text, 0, sizeof(plain_text));

}
void general_diversify()
{
	ST_KEY_VALUE recv_key;
	ST_KEY_VALUE write_key;
	byte rcv_buffer[1024];
	int rcv_buffer_size = 32;

	ST_DATA_16 data;
	ST_DATA_32 data2;

	const unsigned char passwd2[] = { 0x11, 0x22, 0x33, 0x44 };
	int ret = 0;

	// write setup area sector 14
	set_buff_from_hexstr(&write_key, "4E540000000000004E540000000000000E540000000000000E54000000000000");
	ret = g3api_write_key_value(14, SETUP_AREA, PLAIN_TEXT, &write_key, sizeof(ST_KEY_VALUE));
	print_result("write key", ret);

	// write key area sector 40
	set_buff_from_hexstr(&write_key, "6B8B3A2D115E4683A540FF6C1515A13D21AABF36472D3C112FD134AD5F4F3122");
	ret = g3api_write_key_value(40, KEY_AREA, PLAIN_TEXT, &write_key, sizeof(ST_KEY_VALUE));
	print_result("write key", ret);

	// write key area sector 41
	set_buff_from_hexstr(&write_key, "6B8B3A2D115E4683A540FF6C1515A13D21AABF36472D3C112FD134AD5F4F3122");
	ret = g3api_write_key_value(41, KEY_AREA, PLAIN_TEXT, &write_key, sizeof(ST_KEY_VALUE));
	print_result("write key", ret);

	// g3api_diversify without MAC
	set_buff_from_hexstr(&data, "00000000000000000000000000000000");
	ret = g3api_diversify(40, SELF, data.data, sizeof(data));
	print_result("g3api_diversify_self", ret);

	// g3api_diversify with MAC
	set_buff_from_hexstr(&data2, "000000000000000000000000000000006A3D9CF10CD15242145D119A10D74FCB");
	ret = g3api_diversify(41, SELF, data2.data, sizeof(data2));
	print_result("g3api_diversify self with mac", ret);


}
void general_certificate()
{
	ST_KEY_VALUE recv_key;
	ST_KEY_VALUE write_key;
	byte cert[1024];
	int cert_size = 567;

	set_buff_from_hexstr(cert, "30820233A003020102020900B366C6CD34956A56300A06082A8648CE3D040302304C310B3009060355040613024B52311F301D060355040A0C164943544B20486F6C64696E677320636F2E204C54442E311C301A06035504030C134943544B2053656C66205369676E6564204341301E170D3138303430353035343734335A170D3438303332383035343734335A3081B3310B3009060355040613024B52310E300C06035504110C0531333438383114301206035504080C0B4779656F6E6767692D646F3114301206035504070C0B53656F6E676E616D2D7369311F301D060355040A0C164943544B20486F6C64696E677320636F2E204C54442E311C301A060355040B0C135365637572697479205226442043656E7465723129302706035504030C2030303030303030303030303030303030303030303030303030303030303030303059301306072A8648CE3D020106082A8648CE3D0301070342000469520DAFC528A8BE57C9CF25FC22414346468D0588C4CFE42EF634F3D5A6253889324325BED11402CF9FD0CD22FDCDB51EDCCCBA1255C1F0A87627D0B2C68EC1A3819530819230090603551D1304023000301F0603551D230418301680147DB615A129C3CCCCD3CCE9107E5735BD257BAC5B301D0603551D0E041604143D449AFA6CA08D0A2CABB1A451A02CAB517F7D4C300B0603551D0F0404030203E830130603551D25040C300A06082B0601050507030230230603551D11041C301A820A2A2E6963746B2E636F6D820C7777772E6963746B2E636F6D");


	byte issued_cert[1024];
	int issued_cert_size = 0;

	ST_DATA_32 encrypted_key;
	//set_buff_from_hexstr(issued_cert, "");
	
	const unsigned char passwd2[] = { 0x11, 0x22, 0x33, 0x44 };
	int ret = 0;

	// write setup area sector 15
	set_buff_from_hexstr(&write_key, "2E540000000000003E540000000000000E540000000000000E54000000000000");
	ret = g3api_write_key_value(15, SETUP_AREA, PLAIN_TEXT, &write_key, sizeof(ST_KEY_VALUE));
	print_result("write key", ret);

	// write key area sector 44 ( ecc_prv_key )
	set_buff_from_hexstr(&write_key, "8F0511C5F59C131D60BB96A12C07AB0D3E4D75D1CEE4FD747DF41D41696AA2A3");
	ret = g3api_write_key_value(44, KEY_AREA, PLAIN_TEXT, &write_key, sizeof(ST_KEY_VALUE));
	print_result("write key", ret);

	// write key area sector 45 ( ecc_pub_key_1 )
	set_buff_from_hexstr(&write_key, "7CC2F04BFCB22ACD94A230EAA57D90FD65AD7CDC16695FB3A1C4A71D7A2E7481");
	ret = g3api_write_key_value(45, KEY_AREA, PLAIN_TEXT, &write_key, sizeof(ST_KEY_VALUE));
	print_result("write key", ret);

	// write key area sector 46 ( ecc_pub_key_2 )
	set_buff_from_hexstr(&write_key, "961F49DCD5F33971FBF0320BA3CEB6F6A1CB8EA2D98AEBC24B023197EB76C625");
	ret = g3api_write_key_value(46, KEY_AREA, PLAIN_TEXT, &write_key, sizeof(ST_KEY_VALUE));
	print_result("write key", ret);


	// g3api issue certificate
	ret = g3api_issue_certification(44, 0x15E, ISCRT_DATA_AREA_0, 0, 0x2C, NULL, cert, cert_size);
	print_result("g3api issue certification", ret);

	// read issued cert 
	int cnt = 21;
	for (int i = 0; i < cnt; i++)
	{	
		ret = g3api_read_key_value(i, DATA_AREA_0, PLAIN_TEXT,NULL,0, &recv_key, sizeof(ST_KEY_VALUE));
		memcpy(issued_cert+(i*sizeof(ST_KEY_VALUE)), &recv_key, sizeof(ST_KEY_VALUE));
		memset(&recv_key, 0, sizeof(ST_KEY_VALUE));
	}
	issued_cert_size = issued_cert[2] * 256 + issued_cert[3] + 4;
	print_value("issued_cert", issued_cert, issued_cert_size);

	// g3api certificate
	ret = g3api_certification(45, TO_TEMP, issued_cert, issued_cert_size);
	print_result("g3api certification", ret);
	memset(issued_cert, 0, 1024);
	issued_cert_size = 0;




	// g3api issue certificate encrypted prv key
	set_buff_from_hexstr(&encrypted_key, "AA286EAE7A9F20BB5B9DF56EBA11985285DB33417D9A1A603E73FF58161158CA");
	ret = g3api_issue_certification(44, 0x15E, ISCRT_DATA_AREA_1, 0, 0x1000, &encrypted_key, cert, cert_size);
	print_result("g3api issue certification", ret);

	// read issued cert 
	for (int i = 0; i < cnt; i++)
	{
		ret = g3api_read_key_value(i, DATA_AREA_1, PLAIN_TEXT, NULL, 0, &recv_key, sizeof(ST_KEY_VALUE));
		memcpy(issued_cert + (i*sizeof(ST_KEY_VALUE)), &recv_key, sizeof(ST_KEY_VALUE));
		memset(&recv_key, 0, sizeof(ST_KEY_VALUE));
	}
	issued_cert_size = issued_cert[2] * 256 + issued_cert[3] + 4;
	print_value("issued_cert2", issued_cert, issued_cert_size);

	// g3api certificate
	ret = g3api_certification(45, TO_TEMP, issued_cert, issued_cert_size);
	print_result("g3api certification2", ret);
	memset(issued_cert, 0, 1024);
	issued_cert_size = 0;


}
void general_session()
{
	ST_KEY_VALUE recv_key;
	ST_KEY_VALUE write_key;

	const unsigned char passwd2[] = { 0x11, 0x22, 0x33, 0x44 };
	int ret = 0;

	byte session_b[16];
	byte output_32[32];
	int output_32_size = 32;

	byte output_16[16];
	int output_16_size = 16;

	byte factory_data[18];

	ST_ECC_PUBLIC ecc_pub;

	// write setup area sector 16
	set_buff_from_hexstr(&write_key, "4E540000000000004E540000000000000E540000000000000E54000000000000");
	ret = g3api_write_key_value(16, SETUP_AREA, PLAIN_TEXT, &write_key, sizeof(ST_KEY_VALUE));
	print_result("write key", ret);

	// write key area sector 48 ( aes128 key )
	set_buff_from_hexstr(&write_key, "6B8B3A2D115E4683A540FF6C1515A13D21AABF36472D3C112FD134AD5F4F3122");
	ret = g3api_write_key_value(48, KEY_AREA, PLAIN_TEXT, &write_key, sizeof(ST_KEY_VALUE));
	print_result("write key", ret);

	// session_symmetric
	set_buff_from_hexstr(session_b, "4A5E31F5D1D5B6C438D1F155A1F3FE5A");
	ret = g3api_session(48, SYMM_KEY, session_b, sizeof(session_b), output_32, &output_32_size);
	print_result("session symmetric", ret);
	print_value("sessino output", output_32,output_32_size);
	memset(output_32, 0, sizeof(output_32));

	// session factory key
	set_buff_from_hexstr(factory_data, "1000");
	memcpy(factory_data+2, session_b, sizeof(session_b));
	ret = g3api_session(0, FACTORY_AES, factory_data, sizeof(factory_data), output_16, &output_16_size);
	print_result_value("session factory key", ret, output_16, sizeof(output_16));
	memset(output_16, 0, sizeof(output_16));

	// external session key
	ret = g3api_session(0, EXT_SESSION_KEY_AES, session_b, sizeof(session_b), output_16, &output_16_size);
	print_result_value("external session key", ret, output_16, output_16_size);

	// external public key
	set_buff_from_hexstr(&ecc_pub, "7CC2F04BFCB22ACD94A230EAA57D90FD65AD7CDC16695FB3A1C4A71D7A2E7481961F49DCD5F33971FBF0320BA3CEB6F6A1CB8EA2D98AEBC24B023197EB76C625");
	ret = g3api_set_extern_public_key(&ecc_pub,sizeof(ST_ECC_PUBLIC),(ST_DATA_32 *)output_32);
	print_result_value("external public key", ret, output_32, sizeof(output_32));

}
void general_etc()
{
	ST_KEY_VALUE recv_key;
	ST_KEY_VALUE write_key;

	const unsigned char passwd2[] = { 0x11, 0x22, 0x33, 0x44 };
	int ret = 0;

	ST_ECC_PUBLIC PUB_KEY_64;
	ST_ECC_PUBLIC_COMPRESS PUB_KEY_33;

	byte msg[4];
	ST_DATA_32 output[32];

	


	// write setup area sector 17
	set_buff_from_hexstr(&write_key, "1E540000000000002E540000000000003E540000000000000E54000000000000");
	ret = g3api_write_key_value(17, SETUP_AREA, PLAIN_TEXT, &write_key, sizeof(ST_KEY_VALUE));
	print_result("write key", ret);

	// write key area sector 53 ( ecc prv key )
	set_buff_from_hexstr(&write_key, "8F0511C5F59C131D60BB96A12C07AB0D3E4D75D1CEE4FD747DF41D41696AA2A3");
	ret = g3api_write_key_value(53, KEY_AREA, PLAIN_TEXT, &write_key, sizeof(ST_KEY_VALUE));
	print_result("write key", ret);

	// write key area sector 54 ( ecc pub key_1 )
	set_buff_from_hexstr(&write_key, "7CC2F04BFCB22ACD94A230EAA57D90FD65AD7CDC16695FB3A1C4A71D7A2E7481");
	ret = g3api_write_key_value(54, KEY_AREA, PLAIN_TEXT, &write_key, sizeof(ST_KEY_VALUE));
	print_result("write key", ret);

	// write key area sector 55 ( ecc pub key_2 )
	set_buff_from_hexstr(&write_key, "961F49DCD5F33971FBF0320BACEB6F6A1cCBEA2D98AEBC24B023197EB76C625");
	ret = g3api_write_key_value(55, KEY_AREA, PLAIN_TEXT, &write_key, sizeof(ST_KEY_VALUE));
	print_result("write key", ret);

	// init_priv_key sector 52 ( ecc puf )
	ret = g3api_init_puf(52, 0x01);
	print_result("init priv key", ret);

	// get public key sector 52
	ret = g3api_get_public_key(52, KEY_SECTOR, &PUB_KEY_64, sizeof(PUB_KEY_64));
	print_result("get public key ecc puf 64", ret);
	print_value("public key", &PUB_KEY_64, sizeof(PUB_KEY_64));

	// get public key sector 52
	ret = g3api_get_public_key(52, KEY_SECTOR, &PUB_KEY_33, sizeof(PUB_KEY_33));
	print_result("get public key ecc puf 33", ret);
	print_value("public key", &PUB_KEY_33, sizeof(PUB_KEY_33));

	memset(&PUB_KEY_64, 0, sizeof(PUB_KEY_64));
	memset(&PUB_KEY_33, 0, sizeof(PUB_KEY_33));

	// get public key sector 53
	ret = g3api_get_public_key(53, KEY_SECTOR, &PUB_KEY_64, sizeof(PUB_KEY_64));
	print_result("get public key ecc prv 64", ret);
	print_value("public key", &PUB_KEY_64, sizeof(PUB_KEY_64));

	// get public key sector 53
	ret = g3api_get_public_key(53, KEY_SECTOR, &PUB_KEY_33, sizeof(PUB_KEY_33));
	print_result("get public key ecc prv key 33", ret);
	print_value("public key", &PUB_KEY_33, sizeof(PUB_KEY_33));
	
	// session ins external pub key & get public key temporary public key
	set_buff_from_hexstr(&PUB_KEY_64, "7CC2F04BFCB22ACD94A230EAA57D90FD65AD7CDC16695FB3A1C4A71D7A2E7481961F49DCD5F33971FBF0320BA3CEB6F6A1CB8EA2D98AEBC24B023197EB76C625");
	ret = g3api_set_extern_public_key(&PUB_KEY_64, sizeof(ST_ECC_PUBLIC), output);
	print_result_value("external public key", ret, output, sizeof(ST_DATA_32));

	ret = g3api_get_public_key(0, TEMP_PUBLIC_KEY, &PUB_KEY_64, sizeof(PUB_KEY_64));
	print_result_value("get temporary public key 64", ret, &PUB_KEY_64, sizeof(PUB_KEY_64));

	ret = g3api_get_public_key(0, TEMP_PUBLIC_KEY, &PUB_KEY_33, sizeof(PUB_KEY_33));
	print_result_value("get temporary public key 33", ret, &PUB_KEY_33, sizeof(PUB_KEY_33));

	// g3api sha256
	ret = g3api_sha256(Initialize, NULL, 0, NULL);
	print_result("sha256 init", ret);

	set_buff_from_hexstr(msg, "11223344");
	ret = g3api_sha256(Update, msg, sizeof(msg), NULL);
	print_result("sha256 init", ret);

	ret = g3api_sha256(Finalize, NULL, 0, output);
	print_result_value("sha256 final", ret,output, sizeof(ST_DATA_32));
}
void general_tls()
{
	ST_KEY_VALUE recv_key;
	ST_KEY_VALUE write_key;

	const unsigned char passwd2[] = { 0x11, 0x22, 0x33, 0x44 };
	int ret = 0;

	ST_ECC_PUBLIC Qb;
	ST_ECC_PUBLIC Qchip;
	
	byte pre_m_secret[32];
	byte tls_key_block[128];
	ST_ECDH_IV ecdh_iv;

	ST_ECDH_RANDOM ecdh_random;
	set_buff_from_hexstr(&ecdh_random.server, "2A67C2B6A9505B4019ED11348F72D462F7F9843EE911F8A87DDCE675B1B0C0AE");
	set_buff_from_hexstr(&ecdh_random.client, "DEBA9F24A361B65C3DFE11750A394359D3A2A81AA8331F712C413AA97C402EAD");

	ST_TLS_INTER_HEADER_WITHOUT_SIZE tls_header;
	set_buff_from_hexstr(&tls_header.hi_be_sequence, "38934393");
	set_buff_from_hexstr(&tls_header.lo_be_sequence, "93923980");
	set_buff_from_hexstr(&tls_header.content_type, "01");
	set_buff_from_hexstr(&tls_header.tls_be_ver, "0303");

	ST_IV tls_iv;
	ST_DATA_16 header_random;
	set_buff_from_hexstr(&header_random, "00000000000000000000000000000000");

	byte msg[32];
	set_buff_from_hexstr(msg, "A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0A0");
	
	byte msg_dec[32];
	int msg_dec_size = 32;

	ST_DATA_32 msg_hand;
	ST_TLS_HAND_HANDSHAKE_DIGEST handshake_digest;

	byte crypto[1024];
	memset(crypto, 0, sizeof(crypto));
	int crypto_size = 1024;

	byte crypto_dec[32];
	byte server_write_key[16];

	// write setup area sector 18
	set_buff_from_hexstr(&write_key, "2E540000000000003E540000000000000E540000000000000E54000000000000");
	ret = g3api_write_key_value(18, SETUP_AREA, PLAIN_TEXT, &write_key, sizeof(ST_KEY_VALUE));
	print_result("write key", ret);

	// write key area sector 56 ( ecc_prv_key )
	set_buff_from_hexstr(&write_key, "8F0511C5F59C131D60BB96A12C07AB0D3E4D75D1CEE4FD747DF41D41696AA2A3");
	ret = g3api_write_key_value(56, KEY_AREA, PLAIN_TEXT, &write_key, sizeof(ST_KEY_VALUE));
	print_result("write key", ret);

	// write key area sector 57 ( ecc_pub_key_1 )
	set_buff_from_hexstr(&write_key, "7CC2F04BFCB22ACD94A230EAA57D90FD65AD7CDC16695FB3A1C4A71D7A2E7481");
	ret = g3api_write_key_value(57, KEY_AREA, PLAIN_TEXT, &write_key, sizeof(ST_KEY_VALUE));
	print_result("write key", ret);

	// write key area sector 58 ( ecc_pub_key_2 )
	set_buff_from_hexstr(&write_key, "961F49DCD5F33971FbF0320BA3CEB6F6A1CB8EA2D98AEBC24B023197EB76C625");
	ret = g3api_write_key_value(58, KEY_AREA, PLAIN_TEXT, &write_key, sizeof(ST_KEY_VALUE));
	print_result("write key", ret);

	
	// NORMAL ECDH
	ret = g3api_get_public_key(56, KEY_SECTOR, &Qb, sizeof(Qb));
	print_result_value("get public key", ret, &Qb, sizeof(Qb));

	ret = g3api_ecdh(NORMAL_ECDH, &Qb, sizeof(Qb), NULL, &Qchip, pre_m_secret, sizeof(pre_m_secret));
	print_result("NORMAL_ECDH", ret);
	print_value("Qchip", &Qchip, sizeof(Qchip));
	print_value("pre_m_secret", pre_m_secret, sizeof(pre_m_secret));

	// GEN_TLS_BLOCK
	ret = g3api_ecdh(GEN_TLS_BLOCK, &Qb, sizeof(Qb), &ecdh_random, &Qchip, tls_key_block, sizeof(tls_key_block));
	print_result("GEN_TLS_BLOCK", ret);
	print_value("Qchip", &Qchip, sizeof(Qchip));
	print_value("TLS_KEY_BLOCK", tls_key_block, sizeof(tls_key_block));

	// SET_TLS_SESSION_KEY
	ret = g3api_ecdh(SET_TLS_SESSION_KEY, &Qb, sizeof(Qb), &ecdh_random, &Qchip, &ecdh_iv, sizeof(ecdh_iv));
	print_result("SET_TLS_SESSION_KEY", ret);
	print_value("Qchip", &Qchip, sizeof(Qchip));
	print_value("ECDH_IV", &ecdh_iv, sizeof(ecdh_iv));

	// TLS MAC and Encrypt instruction
	memcpy(&tls_iv, &ecdh_iv.client_iv, sizeof(tls_iv));
	ret = g3api_tls_mac_encrypt(&tls_header, &tls_iv, &header_random, msg, sizeof(msg), crypto, &crypto_size);
	print_result_value("TLS MAC and Encrypt", ret, crypto, sizeof(crypto));

	
	// TLS Decrypt and Verify 
	/*memcpy(&tls_iv, &ecdh_iv.server_iv, sizeof(tls_iv));
	memcpy(server_write_key,)
	ret = g3api_tls_decrypt_verify(&tls_header, &tls_iv, crypto_dec, sizeof(crypto_dec), &header_random, msg_dec, &msg_dec_size);
	print_result_value("TLS Decrypt and Verify", ret, msg_dec, sizeof(msg_dec));*/


	// TLS Get Handshake Digest
	set_buff_from_hexstr(&msg_hand, "40CDAB386406A441D593171B343E735AA2274833884EBC3E0FD8054EF76D1C5B");
	ret = g3api_tls_get_handshake_digest(HSM_CLIENT, &msg_hand, &handshake_digest);
	print_result_value("TLS_CLIENT_HANDSHAKE", ret, &handshake_digest, sizeof(handshake_digest));
	memset(&handshake_digest, 0, sizeof(handshake_digest));

	ret = g3api_tls_get_handshake_digest(HSM_SERVER, &msg_hand, &handshake_digest);
	print_result_value("TLS_SERVER_HANDSHAKE", ret, &handshake_digest, sizeof(handshake_digest));
	memset(&handshake_digest, 0, sizeof(handshake_digest));
}
void test_scenario_scenariol(){

}
void test_scenario_sample()
{

	printf("ST_ECIES :%d \n", sizeof(ST_ECIES));
	print_value("msg_org", msg_org, sizeof(msg_org));


	int ret = 0;
	unsigned char chal[256] ={0,};
	int chal_size = 32;
	
	
	ret = g3api_get_challenge(32 , chal , &chal_size);
	print_result("g3api_get_challenge", ret);
	print_value("chal",chal,chal_size);
	
	
	
	
	
	
	ret = g3api_verify_passwd(3 , passwd , sizeof(passwd));
	print_result("g3api_verify_passwd", ret);


	
	
#if 1	
	
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

	/*
	pubkey  8C46B8B8640CC67C558B60514CF4CE5186766234338666B1D0ADDDEFB70EB2BADBE00B2F9677873F9EA41CA47E061A8D389488F66F7E29750D26C58536E1015F
	encin 1B0A295E77C2088610F4AB2CC0BA17B21400000CB3E32FC912C2A027AAFBFAA79329D4437F18BB4FE88E89D511D3B3D87FB6F025A5DBACD597FA2E20B27C48D90F0F0F0F0F0F0F0F0F0F0F0F0F0F0F0F
	
	keyblock AB3D098837C6D362BD8A6779EECA537DF6F44489377D0E0346A4F7AAB3E8259821F0903EBEF2B9A6CD9073D26377233E55D6A99F143B01E9EB4442F4800A4790E2B3DD168DCF0BD87F96DDE8A0660B9559E207D2862F96254D50B37F8370CA2A47222475DBFF6DC816BECE71F464C1C58B31CBDCA0E4C5B4316E1C737FD68EAC
	pubout 623CB27B2A45B9A613C00D165EDBE082931F0DC446298FE27FED4B311212A375429E5BFC656E3B07559663F20ACAB716163EA6DDBF25757B9C246257B25A9FF2

	*/
	ret = g3api_ecdh(GEN_TLS_BLOCK , outer_pub_key , sizeof(outer_pub_key) , &st_ecdh_random , &Q_chip , &st_ecdh_key_block , sizeof(ST_ECDH_KEY_BLOCK));
	print_result("g3api_ecdh", ret);
	print_value("st_ecdh_key_block",&st_ecdh_key_block,sizeof(ST_ECDH_KEY_BLOCK));
	print_value("Q_chip",&Q_chip,sizeof(ST_ECC_PUBLIC));
	
	
	
	ST_ECDH_IV st_ecdh_iv = { 0, };
	memcpy(&st_ecdh_random, server_ecdh_random, sizeof(server_ecdh_random));
	
	ret = g3api_ecdh(SET_TLS_SESSION_KEY, outer_pub_key, sizeof(outer_pub_key), &st_ecdh_random, &Q_chip, &st_ecdh_iv, sizeof(ST_ECDH_IV));
	print_result("g3api_ecdh", ret);
	print_value("st_ecdh_iv",&st_ecdh_iv,sizeof(ST_ECDH_IV));
	print_value("Q_chip",&Q_chip,sizeof(ST_ECC_PUBLIC));

	ST_TLS_INTER_HEADER_WITHOUT_SIZE st_tls_inter_header_without_size;


	ret = g3api_make_tls_inter_header_without_size(0, APPLICATION_DATA, TLS_1_2, &st_tls_inter_header_without_size);
	print_result("g3api_make_tls_inter_header_without_size", ret);
	print_value("st_tls_inter_header_without_size", &st_tls_inter_header_without_size, sizeof(ST_TLS_INTER_HEADER_WITHOUT_SIZE));

	


	ST_IV client_iv = {0,};
	ST_DATA_16
	 head_rand = {0,};
	
	memcpy(&client_iv,st_ecdh_key_block.client_iv,sizeof(ST_IV));
	out_size = 1028;
	
#if 0	
	ret = g3api_tls_mac_encrypt(&st_tls_inter_header_without_size, &client_iv, &head_rand, msg_org, sizeof(msg_org), outbuff, &out_size);
	print_result("g3api_tls_mac_encrypt", ret);
	print_value("outbuff",outbuff,out_size);
#endif
	
	
	//ST_IV server_iv = {0,};
	//memcpy(&server_iv,st_ecdh_key_block.server_iv,sizeof(ST_IV));
	unsigned char outbuff2[1024] ={0,};
	int out_size2 = 1024;
	
	
	ret = g3api_tls_decrypt_verify(&st_tls_inter_header_without_size, (ST_IV*)st_ecdh_iv.server_iv, 
		server_cipher,
		sizeof(server_cipher),
		&head_rand, outbuff2, &out_size2);
	print_result("g3api_tls_decrypt_verify", ret);
	print_value("head_rand", &head_rand, sizeof(ST_DATA_16));
	print_value("outbuff", outbuff2, out_size2);
#endif
	
	/*ret = g3api_certification(6, TO_KEY_SECTOR, cert, sizeof(cert));
	print_result("g3api_certification", ret);*/

	
}



void test_scenario_sample2()
{

	initialize();

	//g3api_reset();
	//general_read_write();
	//general_diversify();
	general_enc_dec();
	//general_password();
	//general_session();
	//general_sign_verify();
	//general_certificate();
	//general_etc();
	//general_tls();

	//ret = g3api_get_challenge(32, rcv_buffer, &rcv_buffer_size);
	//print_result("g3api_get_challenge", ret);


#if 0

	ST_SIGN_ECDSA st_sign_ecdsa = { 0, };;


	int pos_pub_dynamic = 0;

	ST_IV st_iv;
	memcpy(&st_iv, iv, sizeof(ST_IV));
	unsigned char outbuff[1028] = { 0, };
	int out_size = 1028;
	out_size = 256;

	ST_ECIES st_ecies = { 0, };

	ST_ECC_PUBLIC st_ecc_pub;

	ST_ECC_PUBLIC Q_chip = { 0, };
	ST_ECDH_KEY_BLOCK st_ecdh_key_block = { 0, };
	ST_ECDH_RANDOM st_ecdh_random = { 0, };

	/*
	pubkey  8C46B8B8640CC67C558B60514CF4CE5186766234338666B1D0ADDDEFB70EB2BADBE00B2F9677873F9EA41CA47E061A8D389488F66F7E29750D26C58536E1015F
	encin 1B0A295E77C2088610F4AB2CC0BA17B21400000CB3E32FC912C2A027AAFBFAA79329D4437F18BB4FE88E89D511D3B3D87FB6F025A5DBACD597FA2E20B27C48D90F0F0F0F0F0F0F0F0F0F0F0F0F0F0F0F

	keyblock AB3D098837C6D362BD8A6779EECA537DF6F44489377D0E0346A4F7AAB3E8259821F0903EBEF2B9A6CD9073D26377233E55D6A99F143B01E9EB4442F4800A4790E2B3DD168DCF0BD87F96DDE8A0660B9559E207D2862F96254D50B37F8370CA2A47222475DBFF6DC816BECE71F464C1C58B31CBDCA0E4C5B4316E1C737FD68EAC
	pubout 623CB27B2A45B9A613C00D165EDBE082931F0DC446298FE27FED4B311212A375429E5BFC656E3B07559663F20ACAB716163EA6DDBF25757B9C246257B25A9FF2

	*neo_api_set_sc_random_new client_random (size:32):
	7BF59D5B2A0A5A597F2A612DA2990C594A91A78440675647E32DC9FC99D64C47

	*neo_api_set_sc_random_new server_random (size:32):
	933A1A2F50088DF603AA9DC88B4AF8B1C575A447744A1065963FBC81489F9B8A

	
	inter_header
	00000000000000001603030040

	clac_enc_out 
	3A74F2761AB7F009AC61484536F29A23F05DC9BF6E1044C03A5B796739E0FF5141838F76CB5C68BD82789868203923C06FC6A9CE8DE54C2278205B8F75DCE374F51AA60BC67C3E8EE649C283716E3044


	*client_write_MAC_secret (size:32):
	AB3D098837C6D362BD8A6779EECA537DF6F44489377D0E0346A4F7AAB3E82598

	*server_write_MAC_secret (size:32):
	21F0903EBEF2B9A6CD9073D26377233E55D6A99F143B01E9EB4442F4800A4790

	*client_write_key (size:16):
	E2B3DD168DCF0BD87F96DDE8A0660B95

	*server_write_key (size:16):
	59E207D2862F96254D50B37F8370CA2A

	*client_write_IV (size:16):
	47222475DBFF6DC816BECE71F464C1C5

	*server_write_IV (size:16):
	8B31CBDCA0E4C5B4316E1C737FD68EAC

	*/
	const unsigned char pubkey[] = { 0x8c, 0x46, 0xb8, 0xb8, 0x64, 0x0c, 0xc6, 0x7c, 0x55, 0x8b, 0x60, 0x51, 0x4c, 0xf4, 0xce, 0x51, 0x86, 0x76, 0x62, 0x34, 0x33, 0x86, 0x66, 0xb1, 0xd0, 0xad, 0xdd, 0xef, 0xb7, 0x0e, 0xb2, 0xba, 0xdb, 0xe0, 0x0b, 0x2f, 0x96, 0x77, 0x87, 0x3f, 0x9e, 0xa4, 0x1c, 0xa4, 0x7e, 0x06, 0x1a, 0x8d, 0x38, 0x94, 0x88, 0xf6, 0x6f, 0x7e, 0x29, 0x75, 0x0d, 0x26, 0xc5, 0x85, 0x36, 0xe1, 0x01, 0x5f, };
	//const unsigned char encin[] = { 0x1B, 0x0A, 0x29, 0x5E, 0x77, 0xC2, 0x08, 0x86, 0x10, 0xF4, 0xAB, 0x2C, 0xC0, 0xBA, 0x17, 0xB2, 0x14, 0x00, 0x00, 0x0C, 0xB3, 0xE3, 0x2F, 0xC9, 0x12, 0xC2, 0xA0, 0x27, 0xAA, 0xFB, 0xFA, 0xA7, 0x93, 0x29, 0xD4, 0x43, 0x7F, 0x18, 0xBB, 0x4F, 0xE8, 0x8E, 0x89, 0xD5, 0x11, 0xD3, 0xB3, 0xD8, 0x7F, 0xB6, 0xF0, 0x25, 0xA5, 0xDB, 0xAC, 0xD5, 0x97, 0xFA, 0x2E, 0x20, 0xB2, 0x7C, 0x48, 0xD9, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, };
	const unsigned char iv_random[] = { 0x1B, 0x0A, 0x29, 0x5E, 0x77, 0xC2, 0x08, 0x86, 0x10, 0xF4, 0xAB, 0x2C, 0xC0, 0xBA, 0x17, 0xB2, };
	const unsigned char plain_msg[] = { 0x14, 0x00, 0x00, 0x0C, 0xB3, 0xE3, 0x2F, 0xC9, 0x12, 0xC2, 0xA0, 0x27, 0xAA, 0xFB, 0xFA, 0xA7, };
	const unsigned char result_keyblock[] = { 0xAB, 0x3D, 0x09, 0x88, 0x37, 0xC6, 0xD3, 0x62, 0xBD, 0x8A, 0x67, 0x79, 0xEE, 0xCA, 0x53, 0x7D, 0xF6, 0xF4, 0x44, 0x89, 0x37, 0x7D, 0x0E, 0x03, 0x46, 0xA4, 0xF7, 0xAA, 0xB3, 0xE8, 0x25, 0x98, 0x21, 0xF0, 0x90, 0x3E, 0xBE, 0xF2, 0xB9, 0xA6, 0xCD, 0x90, 0x73, 0xD2, 0x63, 0x77, 0x23, 0x3E, 0x55, 0xD6, 0xA9, 0x9F, 0x14, 0x3B, 0x01, 0xE9, 0xEB, 0x44, 0x42, 0xF4, 0x80, 0x0A, 0x47, 0x90, 0xE2, 0xB3, 0xDD, 0x16, 0x8D, 0xCF, 0x0B, 0xD8, 0x7F, 0x96, 0xDD, 0xE8, 0xA0, 0x66, 0x0B, 0x95, 0x59, 0xE2, 0x07, 0xD2, 0x86, 0x2F, 0x96, 0x25, 0x4D, 0x50, 0xB3, 0x7F, 0x83, 0x70, 0xCA, 0x2A, 0x47, 0x22, 0x24, 0x75, 0xDB, 0xFF, 0x6D, 0xC8, 0x16, 0xBE, 0xCE, 0x71, 0xF4, 0x64, 0xC1, 0xC5, 0x8B, 0x31, 0xCB, 0xDC, 0xA0, 0xE4, 0xC5, 0xB4, 0x31, 0x6E, 0x1C, 0x73, 0x7F, 0xD6, 0x8E, 0xAC, };
	const unsigned char result_qchip[] = { 0x62, 0x3C, 0xB2, 0x7B, 0x2A, 0x45, 0xB9, 0xA6, 0x13, 0xC0, 0x0D, 0x16, 0x5E, 0xDB, 0xE0, 0x82, 0x93, 0x1F, 0x0D, 0xC4, 0x46, 0x29, 0x8F, 0xE2, 0x7F, 0xED, 0x4B, 0x31, 0x12, 0x12, 0xA3, 0x75, 0x42, 0x9E, 0x5B, 0xFC, 0x65, 0x6E, 0x3B, 0x07, 0x55, 0x96, 0x63, 0xF2, 0x0A, 0xCA, 0xB7, 0x16, 0x16, 0x3E, 0xA6, 0xDD, 0xBF, 0x25, 0x75, 0x7B, 0x9C, 0x24, 0x62, 0x57, 0xB2, 0x5A, 0x9F, 0xF2, };
	const unsigned char client_random[] = { 0x7B, 0xF5, 0x9D, 0x5B, 0x2A, 0x0A, 0x5A, 0x59, 0x7F, 0x2A, 0x61, 0x2D, 0xA2, 0x99, 0x0C, 0x59, 0x4A, 0x91, 0xA7, 0x84, 0x40, 0x67, 0x56, 0x47, 0xE3, 0x2D, 0xC9, 0xFC, 0x99, 0xD6, 0x4C, 0x47, };
	const unsigned char server_random[] = { 0x93, 0x3A, 0x1A, 0x2F, 0x50, 0x08, 0x8D, 0xF6, 0x03, 0xAA, 0x9D, 0xC8, 0x8B, 0x4A, 0xF8, 0xB1, 0xC5, 0x75, 0xA4, 0x47, 0x74, 0x4A, 0x10, 0x65, 0x96, 0x3F, 0xBC, 0x81, 0x48, 0x9F, 0x9B, 0x8A, };
	const unsigned char inner_header[] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x16, 0x03, 0x03, 0x00, 0x40, };
	const unsigned char calc_enc_out[] = { 0x3A, 0x74, 0xF2, 0x76, 0x1A, 0xB7, 0xF0, 0x09, 0xAC, 0x61, 0x48, 0x45, 0x36, 0xF2, 0x9A, 0x23, 0xF0, 0x5D, 0xC9, 0xBF, 0x6E, 0x10, 0x44, 0xC0, 0x3A, 0x5B, 0x79, 0x67, 0x39, 0xE0, 0xFF, 0x51, 0x41, 0x83, 0x8F, 0x76, 0xCB, 0x5C, 0x68, 0xBD, 0x82, 0x78, 0x98, 0x68, 0x20, 0x39, 0x23, 0xC0, 0x6F, 0xC6, 0xA9, 0xCE, 0x8D, 0xE5, 0x4C, 0x22, 0x78, 0x20, 0x5B, 0x8F, 0x75, 0xDC, 0xE3, 0x74, 0xF5, 0x1A, 0xA6, 0x0B, 0xC6, 0x7C, 0x3E, 0x8E, 0xE6, 0x49, 0xC2, 0x83, 0x71, 0x6E, 0x30, 0x44, };


	memcpy(st_ecdh_random.client, client_random, sizeof(client_random));
	memcpy(st_ecdh_random.server, server_random, sizeof(server_random));


	ret = g3api_ecdh(GEN_TLS_BLOCK, pubkey, sizeof(pubkey), &st_ecdh_random, &Q_chip, &st_ecdh_key_block, sizeof(ST_ECDH_KEY_BLOCK));
	print_result("g3api_ecdh", ret);
	print_value("st_ecdh_key_block", &st_ecdh_key_block, sizeof(ST_ECDH_KEY_BLOCK));
	print_value("result_keyblock", result_keyblock, sizeof(result_keyblock));
	print_value("Q_chip", &Q_chip, sizeof(ST_ECC_PUBLIC));
	print_value("result_qchip", result_qchip, sizeof(result_qchip));



	ST_ECDH_IV st_ecdh_iv = { 0, };
	//memcpy(&st_ecdh_random, server_ecdh_random, sizeof(server_ecdh_random));

	ret = g3api_ecdh(SET_TLS_SESSION_KEY, pubkey, sizeof(pubkey), &st_ecdh_random, &Q_chip, &st_ecdh_iv, sizeof(ST_ECDH_IV));
	print_result("g3api_ecdh", ret);
	print_value("st_ecdh_iv", &st_ecdh_iv, sizeof(ST_ECDH_IV));
	print_value("Q_chip", &Q_chip, sizeof(ST_ECC_PUBLIC));

	


	ST_TLS_INTER_HEADER_WITHOUT_SIZE st_tls_inter_header_without_size;


	ret = g3api_make_tls_inter_header_without_size(0, APPLICATION_DATA, TLS_1_2, &st_tls_inter_header_without_size);
	print_result("g3api_make_tls_inter_header_without_size", ret);
	print_value("st_tls_inter_header_without_size", &st_tls_inter_header_without_size, sizeof(ST_TLS_INTER_HEADER_WITHOUT_SIZE));




	ST_IV client_iv = { 0, };
	ST_DATA_16
		head_rand = { 0, };

	memcpy(&client_iv, st_ecdh_key_block.client_iv, sizeof(ST_IV));
	out_size = 1028;
	memcpy(&head_rand, iv_random, 16);


#if 1	
	ret = g3api_tls_mac_encrypt((ST_TLS_INTER_HEADER_WITHOUT_SIZE*)&inner_header, &client_iv, &head_rand, 
		plain_msg, 
		sizeof(plain_msg) , outbuff, &out_size);
	print_result("g3api_tls_mac_encrypt", ret);
	print_value("outbuff", outbuff, out_size);
	print_value("calc_enc_out", calc_enc_out, sizeof(calc_enc_out));
#endif

	return;


	//ST_IV server_iv = {0,};
	//memcpy(&server_iv,st_ecdh_key_block.server_iv,sizeof(ST_IV));
	unsigned char outbuff2[1024] = { 0, };
	int out_size2 = 1024;


	ret = g3api_tls_decrypt_verify(&st_tls_inter_header_without_size, (ST_IV*)st_ecdh_iv.server_iv,
		server_cipher,
		sizeof(server_cipher),
		&head_rand, outbuff2, &out_size2);
	print_result("g3api_tls_decrypt_verify", ret);
	print_value("head_rand", &head_rand, sizeof(ST_DATA_16));
	print_value("outbuff", outbuff2, out_size2);
	
	
#endif

	/*ret = g3api_certification(6, TO_KEY_SECTOR, cert, sizeof(cert));
	print_result("g3api_certification", ret);*/


}


void test_scenario_sample3()
{
	int ret;


	ret = g3api_verify_passwd(3, passwd, sizeof(passwd));
	print_result("g3api_verify_passwd", ret);




#if 1	

	ST_SIGN_ECDSA st_sign_ecdsa = { 0, };;


	int pos_pub_dynamic = 0;

	ST_IV st_iv;
	memcpy(&st_iv, iv, sizeof(ST_IV));
	unsigned char outbuff[1028] = { 0, };
	int out_size = 1028;
	out_size = 256;

	ST_ECIES st_ecies = { 0, };

	ST_ECC_PUBLIC st_ecc_pub;

	ST_ECC_PUBLIC Q_chip = { 0, };
	ST_ECDH_KEY_BLOCK st_ecdh_key_block = { 0, };
	ST_ECDH_RANDOM st_ecdh_random = { 0, };

	/*
	pubkey  04DA7ECC77CD42D6BE0494C14E19A717D1B6B3FF741E04989AB9A588B076452A4615EFFDDD1BC2F54585DC145501638898F5C21D29638D8CC2ECAC183ADB1CBD
	decin 793E20AA7C3C55EA64969DCF34B0245860A7A6380C05D344EF2C948D07A6159890BD3CEB8BB7735F2D4B922803277E9DB53C6ABB302AB9AB55D5F4956CF678429C678C6B8BECC7BD2FD415FAE53EEF79

	keyblock 148D9ECE79D4BF4EED7CDC390AB927416D36D5DFCCA72A87446FEED29C04451B70CE436905AE380A172795CDC230CCB4B7710BBF60F3DAC705092D0999388CD3340FD6EBB9B7EA0757088CA4409E88053405F33730CA33102DD859647787C6890E68B761D63405C6D4E1DBA151FBEE090B0573B5B8C7565A44D14D84BB28C4E1
	pubout 623CB27B2A45B9A613C00D165EDBE082931F0DC446298FE27FED4B311212A375429E5BFC656E3B07559663F20ACAB716163EA6DDBF25757B9C246257B25A9FF2

	*neo_api_set_sc_random_new client_random (size:32):
	69946189312E7D85D76C884DFD0ADF9D741A8813DB7E4F1E659DA66FD7D00C2E

	*neo_api_set_sc_random_new server_random (size:32):
	A4EDC45BA632BF87466CE2438E28FE1C168A87C945B9BEE680B503853548DD86

	inter_header
	00000000000000001603030040

	calc_dec_out
	E2C426E7F1778C6FC595F54E9FEFDA711400000C9228E3FD2EB411AE47F10F1E346E36223433CA1DA09C517FF2FBCEBEE7D241CF25C7A81955596AAFF56B48150F0F0F0F0F0F0F0F0F0F0F0F0F0F0F0F


	*client_write_MAC_secret (size:32):
	148D9ECE79D4BF4EED7CDC390AB927416D36D5DFCCA72A87446FEED29C04451B

	*server_write_MAC_secret (size:32):
	70CE436905AE380A172795CDC230CCB4B7710BBF60F3DAC705092D0999388CD3

	*client_write_key (size:16):
	340FD6EBB9B7EA0757088CA4409E8805

	*server_write_key (size:16):
	3405F33730CA33102DD859647787C689

	*client_write_IV (size:16):
	0E68B761D63405C6D4E1DBA151FBEE09

	*server_write_IV (size:16):
	0B0573B5B8C7565A44D14D84BB28C4E1


	*/
	
	const unsigned char pubkey[] = { 0x04, 0xDA, 0x7E, 0xCC, 0x77, 0xCD, 0x42, 0xD6, 0xBE, 0x04, 0x94, 0xC1, 0x4E, 0x19, 0xA7, 0x17, 0xD1, 0xB6, 0xB3, 0xFF, 0x74, 0x1E, 0x04, 0x98, 0x9A, 0xB9, 0xA5, 0x88, 0xB0, 0x76, 0x45, 0x2A, 0x46, 0x15, 0xEF, 0xFD, 0xDD, 0x1B, 0xC2, 0xF5, 0x45, 0x85, 0xDC, 0x14, 0x55, 0x01, 0x63, 0x88, 0x98, 0xF5, 0xC2, 0x1D, 0x29, 0x63, 0x8D, 0x8C, 0xC2, 0xEC, 0xAC, 0x18, 0x3A, 0xDB, 0x1C, 0xBD, };
	//const unsigned char encin[] = { 0x1B, 0x0A, 0x29, 0x5E, 0x77, 0xC2, 0x08, 0x86, 0x10, 0xF4, 0xAB, 0x2C, 0xC0, 0xBA, 0x17, 0xB2, 0x14, 0x00, 0x00, 0x0C, 0xB3, 0xE3, 0x2F, 0xC9, 0x12, 0xC2, 0xA0, 0x27, 0xAA, 0xFB, 0xFA, 0xA7, 0x93, 0x29, 0xD4, 0x43, 0x7F, 0x18, 0xBB, 0x4F, 0xE8, 0x8E, 0x89, 0xD5, 0x11, 0xD3, 0xB3, 0xD8, 0x7F, 0xB6, 0xF0, 0x25, 0xA5, 0xDB, 0xAC, 0xD5, 0x97, 0xFA, 0x2E, 0x20, 0xB2, 0x7C, 0x48, 0xD9, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, };
	//const unsigned char iv_random[] = { 0x1B, 0x0A, 0x29, 0x5E, 0x77, 0xC2, 0x08, 0x86, 0x10, 0xF4, 0xAB, 0x2C, 0xC0, 0xBA, 0x17, 0xB2, };
	//const unsigned char plain_msg[] = { 0x14, 0x00, 0x00, 0x0C, 0xB3, 0xE3, 0x2F, 0xC9, 0x12, 0xC2, 0xA0, 0x27, 0xAA, 0xFB, 0xFA, 0xA7, };
	const unsigned char decin[] = { 0x79, 0x3E, 0x20, 0xAA, 0x7C, 0x3C, 0x55, 0xEA, 0x64, 0x96, 0x9D, 0xCF, 0x34, 0xB0, 0x24, 0x58, 0x60, 0xA7, 0xA6, 0x38, 0x0C, 0x05, 0xD3, 0x44, 0xEF, 0x2C, 0x94, 0x8D, 0x07, 0xA6, 0x15, 0x98, 0x90, 0xBD, 0x3C, 0xEB, 0x8B, 0xB7, 0x73, 0x5F, 0x2D, 0x4B, 0x92, 0x28, 0x03, 0x27, 0x7E, 0x9D, 0xB5, 0x3C, 0x6A, 0xBB, 0x30, 0x2A, 0xB9, 0xAB, 0x55, 0xD5, 0xF4, 0x95, 0x6C, 0xF6, 0x78, 0x42, 0x9C, 0x67, 0x8C, 0x6B, 0x8B, 0xEC, 0xC7, 0xBD, 0x2F, 0xD4, 0x15, 0xFA, 0xE5, 0x3E, 0xEF, 0x79, };

	const unsigned char result_keyblock[] = { 0x14, 0x8D, 0x9E, 0xCE, 0x79, 0xD4, 0xBF, 0x4E, 0xED, 0x7C, 0xDC, 0x39, 0x0A, 0xB9, 0x27, 0x41, 0x6D, 0x36, 0xD5, 0xDF, 0xCC, 0xA7, 0x2A, 0x87, 0x44, 0x6F, 0xEE, 0xD2, 0x9C, 0x04, 0x45, 0x1B, 0x70, 0xCE, 0x43, 0x69, 0x05, 0xAE, 0x38, 0x0A, 0x17, 0x27, 0x95, 0xCD, 0xC2, 0x30, 0xCC, 0xB4, 0xB7, 0x71, 0x0B, 0xBF, 0x60, 0xF3, 0xDA, 0xC7, 0x05, 0x09, 0x2D, 0x09, 0x99, 0x38, 0x8C, 0xD3, 0x34, 0x0F, 0xD6, 0xEB, 0xB9, 0xB7, 0xEA, 0x07, 0x57, 0x08, 0x8C, 0xA4, 0x40, 0x9E, 0x88, 0x05, 0x34, 0x05, 0xF3, 0x37, 0x30, 0xCA, 0x33, 0x10, 0x2D, 0xD8, 0x59, 0x64, 0x77, 0x87, 0xC6, 0x89, 0x0E, 0x68, 0xB7, 0x61, 0xD6, 0x34, 0x05, 0xC6, 0xD4, 0xE1, 0xDB, 0xA1, 0x51, 0xFB, 0xEE, 0x09, 0x0B, 0x05, 0x73, 0xB5, 0xB8, 0xC7, 0x56, 0x5A, 0x44, 0xD1, 0x4D, 0x84, 0xBB, 0x28, 0xC4, 0xE1, };


	const unsigned char result_qchip[] = { 0x62, 0x3C, 0xB2, 0x7B, 0x2A, 0x45, 0xB9, 0xA6, 0x13, 0xC0, 0x0D, 0x16, 0x5E, 0xDB, 0xE0, 0x82, 0x93, 0x1F, 0x0D, 0xC4, 0x46, 0x29, 0x8F, 0xE2, 0x7F, 0xED, 0x4B, 0x31, 0x12, 0x12, 0xA3, 0x75, 0x42, 0x9E, 0x5B, 0xFC, 0x65, 0x6E, 0x3B, 0x07, 0x55, 0x96, 0x63, 0xF2, 0x0A, 0xCA, 0xB7, 0x16, 0x16, 0x3E, 0xA6, 0xDD, 0xBF, 0x25, 0x75, 0x7B, 0x9C, 0x24, 0x62, 0x57, 0xB2, 0x5A, 0x9F, 0xF2, };

	//const unsigned char client_random[] = { 0x7B, 0xF5, 0x9D, 0x5B, 0x2A, 0x0A, 0x5A, 0x59, 0x7F, 0x2A, 0x61, 0x2D, 0xA2, 0x99, 0x0C, 0x59, 0x4A, 0x91, 0xA7, 0x84, 0x40, 0x67, 0x56, 0x47, 0xE3, 0x2D, 0xC9, 0xFC, 0x99, 0xD6, 0x4C, 0x47, };
	const unsigned char client_random[] = { 0x69, 0x94, 0x61, 0x89, 0x31, 0x2E, 0x7D, 0x85, 0xD7, 0x6C, 0x88, 0x4D, 0xFD, 0x0A, 0xDF, 0x9D, 0x74, 0x1A, 0x88, 0x13, 0xDB, 0x7E, 0x4F, 0x1E, 0x65, 0x9D, 0xA6, 0x6F, 0xD7, 0xD0, 0x0C, 0x2E, };


	//const unsigned char server_random[] = { 0x93, 0x3A, 0x1A, 0x2F, 0x50, 0x08, 0x8D, 0xF6, 0x03, 0xAA, 0x9D, 0xC8, 0x8B, 0x4A, 0xF8, 0xB1, 0xC5, 0x75, 0xA4, 0x47, 0x74, 0x4A, 0x10, 0x65, 0x96, 0x3F, 0xBC, 0x81, 0x48, 0x9F, 0x9B, 0x8A, };
	const unsigned char server_random[] = { 0xA4, 0xED, 0xC4, 0x5B, 0xA6, 0x32, 0xBF, 0x87, 0x46, 0x6C, 0xE2, 0x43, 0x8E, 0x28, 0xFE, 0x1C, 0x16, 0x8A, 0x87, 0xC9, 0x45, 0xB9, 0xBE, 0xE6, 0x80, 0xB5, 0x03, 0x85, 0x35, 0x48, 0xDD, 0x86, };

	const unsigned char inner_header[] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x16, 0x03, 0x03, 0x00, 0x40, };

	//const unsigned char calc_enc_out[] = { 0x3A, 0x74, 0xF2, 0x76, 0x1A, 0xB7, 0xF0, 0x09, 0xAC, 0x61, 0x48, 0x45, 0x36, 0xF2, 0x9A, 0x23, 0xF0, 0x5D, 0xC9, 0xBF, 0x6E, 0x10, 0x44, 0xC0, 0x3A, 0x5B, 0x79, 0x67, 0x39, 0xE0, 0xFF, 0x51, 0x41, 0x83, 0x8F, 0x76, 0xCB, 0x5C, 0x68, 0xBD, 0x82, 0x78, 0x98, 0x68, 0x20, 0x39, 0x23, 0xC0, 0x6F, 0xC6, 0xA9, 0xCE, 0x8D, 0xE5, 0x4C, 0x22, 0x78, 0x20, 0x5B, 0x8F, 0x75, 0xDC, 0xE3, 0x74, 0xF5, 0x1A, 0xA6, 0x0B, 0xC6, 0x7C, 0x3E, 0x8E, 0xE6, 0x49, 0xC2, 0x83, 0x71, 0x6E, 0x30, 0x44, };
	const unsigned char calc_dec_out[] = { 0xE2, 0xC4, 0x26, 0xE7, 0xF1, 0x77, 0x8C, 0x6F, 0xC5, 0x95, 0xF5, 0x4E, 0x9F, 0xEF, 0xDA, 0x71, 0x14, 0x00, 0x00, 0x0C, 0x92, 0x28, 0xE3, 0xFD, 0x2E, 0xB4, 0x11, 0xAE, 0x47, 0xF1, 0x0F, 0x1E, 0x34, 0x6E, 0x36, 0x22, 0x34, 0x33, 0xCA, 0x1D, 0xA0, 0x9C, 0x51, 0x7F, 0xF2, 0xFB, 0xCE, 0xBE, 0xE7, 0xD2, 0x41, 0xCF, 0x25, 0xC7, 0xA8, 0x19, 0x55, 0x59, 0x6A, 0xAF, 0xF5, 0x6B, 0x48, 0x15, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, };

	memcpy(st_ecdh_random.client, client_random, sizeof(client_random));
	memcpy(st_ecdh_random.server, server_random, sizeof(server_random));


	ret = g3api_ecdh(GEN_TLS_BLOCK, pubkey, sizeof(pubkey), &st_ecdh_random, &Q_chip, &st_ecdh_key_block, sizeof(ST_ECDH_KEY_BLOCK));
	print_result("g3api_ecdh", ret);
	print_value("st_ecdh_key_block", &st_ecdh_key_block, sizeof(ST_ECDH_KEY_BLOCK));
	print_value("result_keyblock", result_keyblock, sizeof(result_keyblock));
	print_value("Q_chip", &Q_chip, sizeof(ST_ECC_PUBLIC));
	print_value("result_qchip", result_qchip, sizeof(result_qchip));



	ST_ECDH_IV st_ecdh_iv = { 0, };
	//memcpy(&st_ecdh_random, server_ecdh_random, sizeof(server_ecdh_random));

	ret = g3api_ecdh(SET_TLS_SESSION_KEY, pubkey, sizeof(pubkey), &st_ecdh_random, &Q_chip, &st_ecdh_iv, sizeof(ST_ECDH_IV));
	print_result("g3api_ecdh", ret);
	print_value("st_ecdh_iv", &st_ecdh_iv, sizeof(ST_ECDH_IV));
	print_value("Q_chip", &Q_chip, sizeof(ST_ECC_PUBLIC));




	ST_TLS_INTER_HEADER_WITHOUT_SIZE st_tls_inter_header_without_size;


	ret = g3api_make_tls_inter_header_without_size(0, APPLICATION_DATA, TLS_1_2, &st_tls_inter_header_without_size);
	print_result("g3api_make_tls_inter_header_without_size", ret);
	print_value("st_tls_inter_header_without_size", &st_tls_inter_header_without_size, sizeof(ST_TLS_INTER_HEADER_WITHOUT_SIZE));




	ST_IV client_iv = { 0, };
	ST_DATA_16
		head_rand = { 0, };

	memcpy(&client_iv, st_ecdh_key_block.client_iv, sizeof(ST_IV));
	
	




	//ST_IV server_iv = {0,};
	//memcpy(&server_iv,st_ecdh_key_block.server_iv,sizeof(ST_IV));
	unsigned char outbuff2[1024] = { 0, };
	int out_size2 = 1024;


	ret = g3api_tls_decrypt_verify((ST_TLS_INTER_HEADER_WITHOUT_SIZE*)&inner_header, (ST_IV*)st_ecdh_iv.server_iv,
		decin,
		sizeof(decin),
		&head_rand, outbuff2, &out_size2);
	print_result("g3api_tls_decrypt_verify", ret);
	print_value("head_rand", &head_rand, sizeof(ST_DATA_16));
	print_value("outbuff", outbuff2, out_size2);
	print_value("calc_dec_out", calc_dec_out, sizeof(calc_dec_out));

	ST_DATA_32 sh_msg;
	ST_TLS_HAND_HANDSHAKE_DIGEST digest;
	g3api_tls_get_handshake_digest(HSM_CLIENT, &sh_msg, &digest);
	print_value("sh_msg", &sh_msg, sizeof(sh_msg));
	print_value("digest", &digest, sizeof(digest));

#endif

	/*ret = g3api_certification(6, TO_KEY_SECTOR, cert, sizeof(cert));
	print_result("g3api_certification", ret);*/


}
void test_scenario_sample_ref()
{

	printf("ST_ECIES :%d \n", sizeof(ST_ECIES));
	print_value("msg_org", msg_org, sizeof(msg_org));
	//START API_SAMPLE

	int ret = 0;
	unsigned char chal[32] ={0,};
	int chal_size = 32;
	
	
	ret = g3api_get_challenge(32 , chal , &chal_size);
	print_result("g3api_get_challenge", ret);
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
	
	
	
	ret = g3api_certification(6 , TO_TEMP , cert , sizeof(cert));
	print_result("g3api_certification", ret);
	
	
	
	ST_ECC_PUBLIC Q_chip ={0,};
	ST_ECDH_KEY_BLOCK st_ecdh_key_block = {0,};
	ST_ECDH_RANDOM st_ecdh_random ={0,};
	
	
	ret = g3api_ecdh(GEN_TLS_BLOCK , outer_pub_key , sizeof(outer_pub_key) , &st_ecdh_random , &Q_chip , &st_ecdh_key_block , sizeof(ST_ECDH_KEY_BLOCK));
	print_result("g3api_ecdh", ret);
	print_value("st_ecdh_key_block",&st_ecdh_key_block,sizeof(ST_ECDH_KEY_BLOCK));
	print_value("Q_chip",&Q_chip,sizeof(ST_ECC_PUBLIC));
	
	
	
	ST_ECDH_IV st_ecdh_iv = { 0, };
	
	
	ret = g3api_ecdh(SET_TLS_SESSION_KEY , outer_pub_key , sizeof(outer_pub_key) , &st_ecdh_random , &Q_chip , &st_ecdh_iv , sizeof(ST_ECDH_KEY_BLOCK));
	print_result("g3api_ecdh", ret);
	print_value("st_ecdh_iv",&st_ecdh_iv,sizeof(ST_ECDH_IV));
	print_value("Q_chip",&Q_chip,sizeof(ST_ECC_PUBLIC));
	
	
	
	ST_TLS_INTER_HEADER_WITHOUT_SIZE st_tls_inter_header_without_size;
	
	
	ret = g3api_make_tls_inter_header_without_size(0 , APPLICATION_DATA , TLS_1_2 , &st_tls_inter_header_without_size);
	print_result("g3api_make_tls_inter_header_without_size", ret);
	print_value("st_tls_inter_header_without_size",&st_tls_inter_header_without_size,sizeof(ST_TLS_INTER_HEADER_WITHOUT_SIZE));
	
	
	
	ST_IV client_iv = {0,};
	ST_DATA_16
	 head_rand = {0,};
	
	memcpy(&client_iv,st_ecdh_key_block.client_iv,sizeof(ST_IV));
	out_size = 1028;
	
	
	
	
	ret = g3api_tls_mac_encrypt(&st_tls_inter_header_without_size , &client_iv , &head_rand , msg_org , sizeof(msg_org) , outbuff , &out_size);
	print_result("g3api_tls_mac_encrypt", ret);
	print_value("outbuff",outbuff,out_size);
	
	
	
	ST_IV server_iv = {0,};
	memcpy(&server_iv,st_ecdh_key_block.server_iv,sizeof(ST_IV));
	unsigned char outbuff2[256] ={0,};
	int out_size2 = 256;
	
	
	ret = g3api_tls_decrypt_verify(&st_tls_inter_header_without_size , &server_iv , outbuff , out_size , &head_rand , outbuff2 , &out_size2);
	print_result("g3api_tls_decrypt_verify", ret);
	
	
	
	//END API_SAMPLE
}