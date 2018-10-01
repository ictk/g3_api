#include "neoCoLib.h"
#include "neoDebug.h"
#include <g3_api.h>
//#include <openssl/hmac.h>
#include "util.h"

void print_result_value(const char * title, int ret, const void *buff, int size);
void set_buff_from_hexstr(void *pbuff, const char *hexstr);


void clear()
{
	ST_KEY_VALUE recv_key;
	ST_KEY_VALUE write_key;
	byte rcv_buffer[1024];
	int rcv_buffer_size = 1024;

	int ret = 0;

	const unsigned char passwd[] = { 0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };


	// get Root_AC
	ret = g3api_verify_passwd(3, passwd, sizeof(passwd));
	print_result("g3api_verify_passwd", ret);

	// write setup area sector 2
	set_buff_from_hexstr(&write_key, "0054000000000000005400000000000000540000000000000054000000000000");
	ret = g3api_write_key_value(2, SETUP_AREA, PLAIN_TEXT, &write_key, sizeof(ST_KEY_VALUE));
	print_result("write setup area sector 2 root free", ret);
	
	// write setup area sector 4 ~ 33
	set_buff_from_hexstr(&write_key, "9054000000000000905400000000000090540000000000009054000000000000");
	for (int i = 4; i < 34; i++)
	{
		ret = g3api_write_key_value(i, SETUP_AREA, PLAIN_TEXT, &write_key, sizeof(ST_KEY_VALUE));
		printf("write setup area sector %d data, data, data, data    ret : %d\n", i,ret);
	}

	// write zeros in key area sector 0 ~ 119
	set_buff_from_hexstr(&write_key, "0000000000000000000000000000000000000000000000000000000000000000");
	for (int i = 0; i < 120; i++)
	{
		ret = g3api_write_key_value(i, KEY_AREA, PLAIN_TEXT, &write_key, sizeof(ST_KEY_VALUE));
		printf("write key area sector %d  ret : %d\n", i, ret);
	}

#if 0
	// write zeros in data0 area sector 0 ~ 164
	set_buff_from_hexstr(&write_key, "0000000000000000000000000000000000000000000000000000000000000000");
	for (int i = 0; i < 165; i++)
	{
		ret = g3api_write_key_value(i, DATA_AREA_0, PLAIN_TEXT, &write_key, sizeof(ST_KEY_VALUE));
		printf("write data0 area sector %d  ret : %d\n", i, ret);
	}

	// write zeros in key data1 sector 0 ~ 164
	set_buff_from_hexstr(&write_key, "0000000000000000000000000000000000000000000000000000000000000000");
	for (int i = 0; i < 165; i++)
	{
		ret = g3api_write_key_value(i, DATA_AREA_1, PLAIN_TEXT, &write_key, sizeof(ST_KEY_VALUE));
		printf("write data1 area sector %d  ret : %d\n", i, ret);
	}
#endif

	// write setup area sector 4 ~ 33
	set_buff_from_hexstr(&write_key, "0054000000000000005400000000000000540000000000000054000000000000");
	for (int i = 4; i < 34; i++)
	{
		ret = g3api_write_key_value(i, SETUP_AREA, PLAIN_TEXT, &write_key, sizeof(ST_KEY_VALUE));
		printf("write setup area sector %d void, void, void, void    ret : %d\n", i, ret);
	}

}
void write_cert(){

}
void tls_setup()
{
	ST_KEY_VALUE recv_key;
	ST_KEY_VALUE write_key;
	byte rcv_buffer[1024];
	int rcv_buffer_size = 1024;

	int ret = 0;

	const unsigned char passwd[] = { 0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };

	// get Root_AC
	ret = g3api_verify_passwd(3, passwd, sizeof(passwd));
	print_result("g3api_verify_passwd", ret);

	// write setup area sector 4
	set_buff_from_hexstr(&write_key, "0000000000000000305401030103010300540000000000008E54010301030000");
	ret = g3api_write_key_value(4, SETUP_AREA, PLAIN_TEXT, &write_key, sizeof(ST_KEY_VALUE));
	print_result("write setup area sector 4 rfu, pub manage,, password ", ret);

	// write setup area sector 5
	set_buff_from_hexstr(&write_key, "2E000103010301031E000103010301033E000103010300000054000000000000");
	ret = g3api_write_key_value(5, SETUP_AREA, PLAIN_TEXT, &write_key, sizeof(ST_KEY_VALUE));
	print_result("write setup area sector 5 prv key,puf, pub ca, ", ret);

	// write setup area sector 6
	set_buff_from_hexstr(&write_key, "3E0001030103000000540000000000002E000103010301034E00010301030103");
	ret = g3api_write_key_value(6, SETUP_AREA, PLAIN_TEXT, &write_key, sizeof(ST_KEY_VALUE));
	print_result("write setup area sector 6 device pub key,, device prv key, aes128 key ", ret);

	// write setup area sector 7
	set_buff_from_hexstr(&write_key, "7E00010301030103000000000000000000000000000000000000000000000000");
	ret = g3api_write_key_value(7, SETUP_AREA, PLAIN_TEXT, &write_key, sizeof(ST_KEY_VALUE));
	print_result("write setup area sector 7 sha256 key, rfu, rfu, rfu ", ret);

	// write key area sector 1
	set_buff_from_hexstr(&write_key, "72CF56F5BF877DCF5823691682E9824C0B9742D1E0B41D288B478ECEF5218BAA");
	ret = g3api_write_key_value(1, KEY_AREA, PLAIN_TEXT, &write_key, sizeof(ST_KEY_VALUE));
	print_result("write key area sector 1 pub manage_1 ", ret);

	// write key area sector 2
	set_buff_from_hexstr(&write_key, "1C484CBB848E449A6A5BCD4A686ECE676201073FD61241302BEB185C38E6E4BB");
	ret = g3api_write_key_value(2, KEY_AREA, PLAIN_TEXT, &write_key, sizeof(ST_KEY_VALUE));
	print_result("write key area sector 2 pub manage_2 ", ret);

	// write key area sector 3
	set_buff_from_hexstr(&write_key, "1005050530313233343536370000000000000000000000000000000000000000");
	ret = g3api_write_key_value(3, KEY_AREA, PLAIN_TEXT, &write_key, sizeof(ST_KEY_VALUE));
	print_result("write key area sector 3 password ", ret);

	// write key area sector 4
	set_buff_from_hexstr(&write_key, "91F33CD73198E5CFD964C26B08FB3AB26A855F32B0435A2D0BA693EFBBA186ED");
	ret = g3api_write_key_value(4, KEY_AREA, PLAIN_TEXT, &write_key, sizeof(ST_KEY_VALUE));
	print_result("write key area sector 4 prv key ", ret);

	// write key area sector 6
	set_buff_from_hexstr(&write_key, "D57CBAB7682AE97681C72FAB34AF2873CDBB49E442F85EFEA4DE55C51ED093EE");
	ret = g3api_write_key_value(6, KEY_AREA, PLAIN_TEXT, &write_key, sizeof(ST_KEY_VALUE));
	print_result("write key area sector 6 pub ca_1 ", ret);

	// write key area sector 7
	set_buff_from_hexstr(&write_key, "7E1AD8C3E4025E80F9C4F866B26000D5C8E31C838070D9C0A18FF75AA0EC9B4B");
	ret = g3api_write_key_value(7, KEY_AREA, PLAIN_TEXT, &write_key, sizeof(ST_KEY_VALUE));
	print_result("write key area sector 7 pub ca_2 ", ret);

	// write key area sector 8
	set_buff_from_hexstr(&write_key, "4A5B42C20E614F27DB01E7AC348BE234F9CB0E79BA3C08C7415A22F8C9EA7A3D");
	ret = g3api_write_key_value(8, KEY_AREA, PLAIN_TEXT, &write_key, sizeof(ST_KEY_VALUE));
	print_result("write key area sector 8 device pub key_1 ", ret);

	// write key area sector 9
	set_buff_from_hexstr(&write_key, "24B9E008B8C7F37C775BA611C09236A7315C50BB1F5D1A64C8548CFCF5BDF90F");
	ret = g3api_write_key_value(9, KEY_AREA, PLAIN_TEXT, &write_key, sizeof(ST_KEY_VALUE));
	print_result("write key area sector 9 device pub key_2 ", ret);

	// write key area sector 10
	set_buff_from_hexstr(&write_key, "B4083C7036419F8CB7BA8368313F83F07DEFF63EDC87AEB9C03E8EA211F29A2B");
	ret = g3api_write_key_value(10, KEY_AREA, PLAIN_TEXT, &write_key, sizeof(ST_KEY_VALUE));
	print_result("write key area sector 10 device prv key ", ret);

	// write key area sector 11
	set_buff_from_hexstr(&write_key, "91F33CD73198E5CFD964C26B08FB3AB26A855F32B0435A2D0BA693EFBBA186ED");
	ret = g3api_write_key_value(11, KEY_AREA, PLAIN_TEXT, &write_key, sizeof(ST_KEY_VALUE));
	print_result("write key area sector 11 aes128 key ", ret);

	// write key area sector 12
	set_buff_from_hexstr(&write_key, "91F33CD73198E5CFD964C26B08FB3AB26A855F32B0435A2D0BA693EFBBA186ED");
	ret = g3api_write_key_value(12, KEY_AREA, PLAIN_TEXT, &write_key, sizeof(ST_KEY_VALUE));
	print_result("write key area sector 12 sha256 key ", ret);




	// write data1 area sector 0 
	set_buff_from_hexstr(&write_key, "0000000000000000000000000000000000000000000000000000000000000000");
	ret = g3api_write_key_value(0, DATA_AREA_0, PLAIN_TEXT, &write_key, sizeof(ST_KEY_VALUE));
	print_result("write data0 area sector 0 cert header data ", ret);

	// write data1 area sector 0 
	set_buff_from_hexstr(&write_key, "00016801010D7F01000000000000000000000000000000000000000000000000");
	ret = g3api_write_key_value(0, DATA_AREA_1, PLAIN_TEXT, &write_key, sizeof(ST_KEY_VALUE));
	print_result("write data1 area sector 0 cert header data ", ret);







	// write data1 area sector 1 
	set_buff_from_hexstr(&write_key, "308201643082010A020900E73825936DDE665A300A06082A8648CE3D04030230");
	ret = g3api_write_key_value(1, DATA_AREA_1, PLAIN_TEXT, &write_key, sizeof(ST_KEY_VALUE));
	print_result("write data1 area sector 1 ca cert to user data1 ", ret);

	// write data1 area sector 2 
	set_buff_from_hexstr(&write_key, "3A310B3009060355040613024B52310D300B060355040A0C044943544B311C30");
	ret = g3api_write_key_value(2, DATA_AREA_1, PLAIN_TEXT, &write_key, sizeof(ST_KEY_VALUE));
	print_result("write data1 area sector 2 ca cert to user data1 ", ret);

	// write data1 area sector 3 
	set_buff_from_hexstr(&write_key, "1A06035504030C134943544B2053656C66205369676E6564204341301E170D31");
	ret = g3api_write_key_value(3, DATA_AREA_1, PLAIN_TEXT, &write_key, sizeof(ST_KEY_VALUE));
	print_result("write data1 area sector 3 ca cert to user data1 ", ret);

	// write data1 area sector 4 
	set_buff_from_hexstr(&write_key, "37313131373037353334345A170D3237313131353037353334345A303A310B30");
	ret = g3api_write_key_value(4, DATA_AREA_1, PLAIN_TEXT, &write_key, sizeof(ST_KEY_VALUE));
	print_result("write data1 area sector 4 ca cert to user data1 ", ret);

	// write data1 area sector 5 
	set_buff_from_hexstr(&write_key, "09060355040613024B52310D300B060355040A0C044943544B311C301A060355");
	ret = g3api_write_key_value(5, DATA_AREA_1, PLAIN_TEXT, &write_key, sizeof(ST_KEY_VALUE));
	print_result("write data1 area sector 5 ca cert to user data1 ", ret);

	// write data1 area sector 6 
	set_buff_from_hexstr(&write_key, "04030C134943544B2053656C66205369676E65642043413059301306072A8648");
	ret = g3api_write_key_value(6, DATA_AREA_1, PLAIN_TEXT, &write_key, sizeof(ST_KEY_VALUE));
	print_result("write data1 area sector 6 ca cert to user data1 ", ret);

	// write data1 area sector 7 
	set_buff_from_hexstr(&write_key, "CE3D020106082A8648CE3D03010703420004D57CBAB7682AE97681C72FAB34AF");
	ret = g3api_write_key_value(7, DATA_AREA_1, PLAIN_TEXT, &write_key, sizeof(ST_KEY_VALUE));
	print_result("write data1 area sector 7 ca cert to user data1 ", ret);

	// write data1 area sector 8 
	set_buff_from_hexstr(&write_key, "2873CDBB49E442F85EFEA4DE55C51ED093EE7E1AD8C3E4025E80F9C4F866B260");
	ret = g3api_write_key_value(8, DATA_AREA_1, PLAIN_TEXT, &write_key, sizeof(ST_KEY_VALUE));
	print_result("write data1 area sector 8 ca cert to user data1 ", ret);

	// write data1 area sector 9 
	set_buff_from_hexstr(&write_key, "00D5C8E31C838070D9C0A18FF75AA0EC9B4B300A06082A8648CE3D0403020348");
	ret = g3api_write_key_value(9, DATA_AREA_1, PLAIN_TEXT, &write_key, sizeof(ST_KEY_VALUE));
	print_result("write data1 area sector 9 ca cert to user data1 ", ret);

	// write data1 area sector 10 
	set_buff_from_hexstr(&write_key, "00304502204D36CE61516691750219285EDF5E852E6D4E44A200267580D4A6FB");
	ret = g3api_write_key_value(10, DATA_AREA_1, PLAIN_TEXT, &write_key, sizeof(ST_KEY_VALUE));
	print_result("write data1 area sector 10 ca cert to user data1 ", ret);

	// write data1 area sector 11 
	set_buff_from_hexstr(&write_key, "40D5238FA3022100C25463689E4B089C97F906B19B18C247849241EEDBD99924");
	ret = g3api_write_key_value(11, DATA_AREA_1, PLAIN_TEXT, &write_key, sizeof(ST_KEY_VALUE));
	print_result("write data1 area sector 11 ca cert to user data1 ", ret);

	// write data1 area sector 12 
	set_buff_from_hexstr(&write_key, "E2C65C7A7D6130C9171717171717171717171717171717171717171717171717");
	ret = g3api_write_key_value(12, DATA_AREA_1, PLAIN_TEXT, &write_key, sizeof(ST_KEY_VALUE));
	print_result("write data1 area sector 12 ca cert to user data1 ", ret);



	// write data1 area sector 13 
	set_buff_from_hexstr(&write_key, "3082017B30820121020900D8FBEDBE2F245C61300A06082A8648CE3D04030230");
	ret = g3api_write_key_value(13, DATA_AREA_1, PLAIN_TEXT, &write_key, sizeof(ST_KEY_VALUE));
	print_result("write data1 area sector 13 device cert to user data1 ", ret);

	// write data1 area sector 14 
	set_buff_from_hexstr(&write_key, "3A310B3009060355040613024B52310D300B060355040A0C044943544B311C30");
	ret = g3api_write_key_value(14, DATA_AREA_1, PLAIN_TEXT, &write_key, sizeof(ST_KEY_VALUE));
	print_result("write data1 area sector 14 device cert to user data1 ", ret);

	// write data1 area sector 15 
	set_buff_from_hexstr(&write_key, "1A06035504030C134943544B2053656C66205369676E6564204341301E170D31");
	ret = g3api_write_key_value(15, DATA_AREA_1, PLAIN_TEXT, &write_key, sizeof(ST_KEY_VALUE));
	print_result("write data1 area sector 15 device cert to user data1 ", ret);

	// write data1 area sector 16 
	set_buff_from_hexstr(&write_key, "37313132303031343932315A170D3237313131383031343932315A3051310B30");
	ret = g3api_write_key_value(16, DATA_AREA_1, PLAIN_TEXT, &write_key, sizeof(ST_KEY_VALUE));
	print_result("write data1 area sector 16 device cert to user data1 ", ret);

	// write data1 area sector 17 
	set_buff_from_hexstr(&write_key, "09060355040613024B52310D300B060355040A0C044943544B31193017060355");
	ret = g3api_write_key_value(17, DATA_AREA_1, PLAIN_TEXT, &write_key, sizeof(ST_KEY_VALUE));
	print_result("write data1 area sector 17 device cert to user data1 ", ret);

	// write data1 area sector 18 
	set_buff_from_hexstr(&write_key, "040B0C106963746B2053534C2050726F6A6563743118301606035504030C0F65");
	ret = g3api_write_key_value(18, DATA_AREA_1, PLAIN_TEXT, &write_key, sizeof(ST_KEY_VALUE));
	print_result("write data1 area sector 18 device cert to user data1 ", ret);

	// write data1 area sector 19 
	set_buff_from_hexstr(&write_key, "63632077737368696E20636572743059301306072A8648CE3D020106082A8648");
	ret = g3api_write_key_value(19, DATA_AREA_1, PLAIN_TEXT, &write_key, sizeof(ST_KEY_VALUE));
	print_result("write data1 area sector 19 device cert to user data1 ", ret);

	// write data1 area sector 20 
	set_buff_from_hexstr(&write_key, "CE3D030107034200044A5B42C20E614F27DB01E7AC348BE234F9CB0E79BA3C08");
	ret = g3api_write_key_value(20, DATA_AREA_1, PLAIN_TEXT, &write_key, sizeof(ST_KEY_VALUE));
	print_result("write data1 area sector 20 device cert to user data1 ", ret);

	// write data1 area sector 21 
	set_buff_from_hexstr(&write_key, "C7415A22F8C9EA7A3D24B9E008B8C7F37C775BA611C09236A7315C50BB1F5D1A");
	ret = g3api_write_key_value(21, DATA_AREA_1, PLAIN_TEXT, &write_key, sizeof(ST_KEY_VALUE));
	print_result("write data1 area sector 21 device cert to user data1 ", ret);

	// write data1 area sector 22 
	set_buff_from_hexstr(&write_key, "64C8548CFCF5BDF90F300A06082A8648CE3D0403020348003045022041811E6F");
	ret = g3api_write_key_value(22, DATA_AREA_1, PLAIN_TEXT, &write_key, sizeof(ST_KEY_VALUE));
	print_result("write data1 area sector 22 device cert to user data1 ", ret);

	// write data1 area sector 23 
	set_buff_from_hexstr(&write_key, "8102E1A1FD3C47DD45BA4B7E42E8A6090BCED37D91F937BB38EB74FD022100DA");
	ret = g3api_write_key_value(23, DATA_AREA_1, PLAIN_TEXT, &write_key, sizeof(ST_KEY_VALUE));
	print_result("write data1 area sector 23 device cert to user data1 ", ret);

	// write data1 area sector 24 
	set_buff_from_hexstr(&write_key, "D0D2A74B4AD771873A4C5CB61635162465EA59D25325BDA3AC04994653B8C300");
	ret = g3api_write_key_value(24, DATA_AREA_1, PLAIN_TEXT, &write_key, sizeof(ST_KEY_VALUE));
	print_result("write data1 area sector 24 device cert to user data1 ", ret);


	// write setup area root sector(2)
	set_buff_from_hexstr(&write_key, "0E000301030100000E5403010301000000540000000000000000000000000000");
	ret = g3api_write_key_value(2, SETUP_AREA, PLAIN_TEXT, &write_key, sizeof(ST_KEY_VALUE));
	print_result("write setup area sector 2 root, data_0, data_1, rfu ", ret);


}