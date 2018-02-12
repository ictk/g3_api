// console_g3_api.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

//#include "stdafx.h"
//#include "CtrlBASE.h"
#define NULL 0

#include "CSerialRS232.h"
#include "neoCoLib.h"
#include "neoDebug.h"
#include "g3_api.h"
//#include<windows.h>



//#pragma comment(lib,"libBASE.lib")

using namespace  neocolib;
//
//void sleep(int msec){
//#ifdef _WIN32
//	::Sleep(msec);
//#else
//	usleep(msec * 1000);  /* sleep for 100 milliSeconds */
//#endif
//
//}


void test_load();
#pragma pack(push, 1)   


extern "C" int send_n_recv(const unsigned char*snd, int snd_size, unsigned char*recv, int* recv_size, void*etcparam);

int init_sample(void *param);
void wake_up_and_convert_mode();
void end_sample();

extern "C"  int receiv(unsigned char *buff, int length, void* etc){
	return 0;
}

void print_result(const char * title,int ret)
{
	printf("%s ret:0x%x \n", title, ret);
}
void print_value(const char * title, void *buff,int size){
	printf("%s %s %d \n", title, NCL::BytetoHexStr(buff, size).c_str(), size);
}
#if 0
int test_byload(){
	unsigned char* recvbuff = (unsigned char*)malloc(1024);

	int recvbuff_size = 1024;
	typedef const char * (*PFG3API_GET_LIB_VERSION)();
	typedef void(*PFG3API_SET_USER_SEND_RECV_PF)(PFSENDRECV psendrecv, void * etcparam);
	typedef int(*PFG3API_TEST7)(const unsigned char * in, int in_size);

	HMODULE hmodule = LoadLibrary(L"g3_api_library.dll");
	PFG3API_GET_LIB_VERSION pfg3api_get_lib_version = (PFG3API_GET_LIB_VERSION)GetProcAddress(hmodule, "g3api_get_lib_version");
	PFG3API_SET_USER_SEND_RECV_PF pfg3api_set_user_send_recv_pf = (PFG3API_SET_USER_SEND_RECV_PF)GetProcAddress(hmodule, "g3api_set_user_send_recv_pf");
	PFG3API_TEST7 pfg3api_test7 = (PFG3API_TEST7)GetProcAddress(hmodule, "g3api_test7");
	
	const char *pchar = pfg3api_get_lib_version();

	pfg3api_set_user_send_recv_pf(send_n_recv, NULL);
	pfg3api_test7(recvbuff, recvbuff_size);

	printf("%s\n", pchar);


	return 0;
}
#endif

int main(int argc, char* argv[])
{
	int ret = 0;
	//test_load();
	//return 0;
	//return test_byload();
	
	
	NEO_START;

	NEO_TITLE(main);
	if (argc < 2){
		printf("\n1st argument must be serial port name\n");
		return -1;
	}
	printf("\nserila port name : (%s) \n",argv[1]);

	if (init_sample(argv[1])){
		return -1;

	}
	wake_up_and_convert_mode();

	
	//return 0;


//	g3api_set_etc_param(serreial);
	ST_SIGN_ECDSA sign;
	ST_ECC_PUBLIC pubkey;
	
	VECBYTE vecbyte;


	unsigned char recvbuff[1024];
	
	int recvbuff_size = 1024;
#if 0
	CSerialBASE * serreial = new CSerialRS232(argv[1]);
	g3api_set_user_send_recv_pf(send_n_recv, serreial);

	//g3api_set_etc_param(serreial);
	VECBYTE vecbyte = NCL::HexStr2Byte("FE0000000000");





	vecbyte = NCL::HexStr2Byte("FF0000000000");
	recvbuff_size = 1024;
	g3api_raw_snd_recv(&vecbyte[0], vecbyte.size(), recvbuff, &recvbuff_size);
	printf("ret:0x%x recv %s %d \n", ret, NCL::BytetoHexStr(recvbuff, recvbuff_size).c_str(), recvbuff_size);

	vecbyte = NCL::HexStr2Byte("FE0000000000");
	recvbuff_size = 1024;
	g3api_raw_snd_recv(&vecbyte[0], vecbyte.size(), recvbuff, &recvbuff_size);
	printf("ret:0x%x recv %s %d \n", ret, NCL::BytetoHexStr(recvbuff, recvbuff_size).c_str(), recvbuff_size);
	
#endif

	
	recvbuff_size = 1024;

	ret = g3api_get_chellange(32, recvbuff, &recvbuff_size);


	printf("ret:0x%x recv %s %d \n", ret  ,NCL::BytetoHexStr(recvbuff, recvbuff_size).c_str(), recvbuff_size);
	

#if 0	
		
	

	recvbuff_size = 1024;
	ret = g3api_read_key_value(1, AREA_TYPE::KEY_AREA, RW_TYPE::PLAIN_TEXT, recvbuff, &recvbuff_size);
	printf("ret:0x%x recv %s %d \n", ret, NCL::BytetoHexStr(recvbuff, recvbuff_size).c_str(), recvbuff_size);

	ret = g3api_write_key_value(1, AREA_TYPE::KEY_AREA, RW_TYPE::PLAIN_TEXT, recvbuff, recvbuff_size);
	printf("ret:0x%x recv %s %d \n", ret, NCL::BytetoHexStr(recvbuff, recvbuff_size).c_str(), recvbuff_size);
	
	
	
	vecbyte = NCL::HexStr2Byte("72CF56F5BF877DCF5823691682E9824C0B9742D1E0B41D288B478ECEF5218BAA");
	ret = g3api_write_key_value(0, AREA_TYPE::DATA_AREA_0, RW_TYPE::PLAIN_TEXT, V2A(vecbyte), vecbyte.size());
	printf("ret:0x%x recv %s %d \n", ret, NCL::BytetoHexStr(recvbuff, recvbuff_size).c_str(), recvbuff_size);

	ret = g3api_read_key_value(0, AREA_TYPE::DATA_AREA_0, RW_TYPE::PLAIN_TEXT, recvbuff, &recvbuff_size);
	printf("ret:0x%x recv %s %d \n", ret, NCL::BytetoHexStr(recvbuff, recvbuff_size).c_str(), recvbuff_size);


	recvbuff_size = 1024;
	ret = g3api_read_key_value(0, AREA_TYPE::SETUP_AREA, RW_TYPE::PLAIN_TEXT, recvbuff, &recvbuff_size);
	printf("ret:0x%x recv %s %d \n", ret, NCL::BytetoHexStr(recvbuff, recvbuff_size).c_str(), recvbuff_size);

	//return 0;
	vecbyte = NCL::HexStr2Byte("72CF56F5BF877DCF5823691682E9824C0B9742D1E0B41D288B478ECEF5218BAA");
	
	ret = g3api_sign(4, SIGN_OPTION::SIGN_ECDSA, V2A(vecbyte), vecbyte.size(), &sign, sizeof(ST_SIGN_ECDSA));
	printf("ret:0x%x recv %s %d \n", ret, NCL::BytetoHexStr(&sign, sizeof(sign)).c_str(), recvbuff_size);

	ret = g3api_verify(1, VERIFY_OPTION::VERYFY_ECDSA,V2A(vecbyte), vecbyte.size(), &sign, sizeof(ST_SIGN_ECDSA));
	printf("ret:0x%x recv %s %d \n", ret, NCL::BytetoHexStr(&sign, sizeof(sign)).c_str(), recvbuff_size);

	ST_IV st_iv;
	recvbuff_size = 1024;
	
	ret = g3api_encryption(8, BLOCK_MODE::BL_CBC, V2A(vecbyte), vecbyte.size(), &st_iv, recvbuff, &recvbuff_size);
	printf("ret:0x%x recv %s %d \n", ret, NCL::BytetoHexStr(recvbuff, recvbuff_size).c_str(), recvbuff_size);
	printf("ret:0x%x recv %s %d \n", ret, NCL::BytetoHexStr(&st_iv, sizeof(st_iv)).c_str(), sizeof(st_iv));

	//
	vecbyte.resize(recvbuff_size);
	memcpy(V2A(vecbyte), recvbuff, recvbuff_size);
	recvbuff_size = 1024;
	ret = g3api_decryption(8, BLOCK_MODE::BL_CBC, &st_iv, V2A(vecbyte), vecbyte.size(), recvbuff, &recvbuff_size);
	printf("ret:0x%x recv %s %d \n", ret, NCL::BytetoHexStr(recvbuff, recvbuff_size).c_str(), recvbuff_size);

	ST_ECC_PUBLIC qb;
	ST_ECC_PUBLIC_COMPRESS qbcompress;
	ST_ECC_PUBLIC qchip;
	ST_ECC_PUBLIC ecdh_value;
	vecbyte = NCL::HexStr2Byte("8817A576A8B2076707057136A362A87B96F9A21F3DBF6864B3A7C06705C984FDA36EA822738FA1E49E2A1E4493EA681A87CA02B13B8963080EA171070FEC3AF2");

	
	memcpy(&qb, V2A(vecbyte), sizeof(ST_ECC_PUBLIC));
	
	ret = g3api_ecdh(4, &qb, sizeof(ST_ECC_PUBLIC), &qchip, &ecdh_value);
	printf("qchip ret:0x%x recv %s %d \n", ret, NCL::BytetoHexStr(&qchip, sizeof(ST_ECC_PUBLIC)).c_str(), sizeof(ST_ECC_PUBLIC));
	printf("ecdh_value ret:0x%x recv %s %d \n", ret, NCL::BytetoHexStr(&ecdh_value, sizeof(ST_ECC_PUBLIC)).c_str(), sizeof(ST_ECC_PUBLIC));
	
	vecbyte = NCL::HexStr2Byte("018817A576A8B2076707057136A362A87B96F9A21F3DBF6864B3A7C06705C984F");
	memcpy(&qbcompress, V2A(vecbyte), sizeof(ST_ECC_PUBLIC_COMPRESS));

	ret = g3api_ecdh(4, &qbcompress, sizeof(ST_ECC_PUBLIC_COMPRESS), &qchip, &ecdh_value);
	printf("qchip ret:0x%x recv %s %d \n", ret, NCL::BytetoHexStr(&qchip, sizeof(ST_ECC_PUBLIC)).c_str(), sizeof(ST_ECC_PUBLIC));
	printf("ecdh_value ret:0x%x recv %s %d \n", ret, NCL::BytetoHexStr(&ecdh_value, sizeof(ST_ECC_PUBLIC)).c_str(), sizeof(ST_ECC_PUBLIC));

	
	vecbyte = NCL::HexStr2Byte("72CF56F5BF877DCF5823691682E9824C0B9742D1E0B41D288B478ECEF5218BAA");
	//ret = g3api_sign(4, SIGN_OPTION::SIGN_ECDSA, V2A(vecbyte), vecbyte.size(), &sign, sizeof(ST_SIGN_ECDSA));
	//printf("ret:0x%x recv %s %d \n", ret, NCL::BytetoHexStr(&sign, sizeof(sign)).c_str(), recvbuff_size);

	ret = g3api_verify(1, VERIFY_OPTION::VERYFY_ECDSA, V2A(vecbyte), vecbyte.size(), &sign, sizeof(ST_SIGN_ECDSA));
	printf("ret:0x%x recv %s %d \n", ret, NCL::BytetoHexStr(&sign, sizeof(sign)).c_str(), recvbuff_size);


	

	ret = g3api_get_public_key(1, PUB_TYPE::KEY_SECTOR, &pubkey, sizeof(ST_ECC_PUBLIC));
	printf("pubkey ret:0x%x recv %s %d \n", ret, NCL::BytetoHexStr(&pubkey, sizeof(ST_ECC_PUBLIC)).c_str(), sizeof(ST_ECC_PUBLIC));


	ST_ECC_PUBLIC_COMPRESS pubkey_compress;

	ret = g3api_get_public_key(1, PUB_TYPE::KEY_SECTOR, &pubkey_compress, sizeof(ST_ECC_PUBLIC_COMPRESS));
	printf("pubkey ret:0x%x recv %s %d \n", ret, NCL::BytetoHexStr(&pubkey, sizeof(ST_ECC_PUBLIC_COMPRESS)).c_str(), sizeof(ST_ECC_PUBLIC_COMPRESS));

	vecbyte = NCL::HexStr2Byte("308201D230820177A003020102020900BC136E2CBEBD7297300A06082A8648CE3D040302303A310B3009060355040613024B52310D300B060355040A0C044943544B311C301A06035504030C134943544B2053656C66205369676E6564204341301E170D3137313231393037303131385A170D3232313231383037303131385A3046310B3009060355040613024B52310D300B060355040A0C044943544B31153013060355040B0C0C6963746B2050726F6A6563743111300F06035504030C0865636320636572743059301306072A8648CE3D020106082A8648CE3D0301070342000409D6749DC55C0EF4360E75819DBD5DBBDD825D39A0B5978A11855E169B3E16497A04F9D4CFCBE2E8B8EB531F6C809CC1EAE6AB23422027800DDCD5855E94B3AEA35A305830090603551D1304023000301F0603551D230418301680141E6D2491359BC123F8A0F2E27C8506C6C319B04B301D0603551D0E04160414900FC9D49F3979D8E78D3EF1BB182445764D7E1C300B0603551D0F0404030205E0300A06082A8648CE3D0403020349003046022100A36339D4DDB27089D65F91A400C271A15A56AB8909980EDC38E4CBC3F66C107F022100AB99345693DC4D1DC9815FA88615DE4ACB6A4D724137192EB546DA4D6AD9C332");
	ret = g3api_certification(6, CERTIFICATION_WRITE_MODE::TO_TEMP, V2A(vecbyte), vecbyte.size());
	printf("g3api_certification ret:0x%x recv %s %d \n", ret, NCL::BytetoHexStr(&pubkey, sizeof(ST_ECC_PUBLIC_COMPRESS)).c_str(), sizeof(ST_ECC_PUBLIC_COMPRESS));
#endif
	vecbyte = NCL::HexStr2Byte("30313233343536370000000000000000");
	ret = g3api_verify_passwd(3, V2A(vecbyte), vecbyte.size());
	printf("g3api_verify_passwd ret:0x%x \n", ret);

	vecbyte = NCL::HexStr2Byte("308201D230820177A003020102020900BC136E2CBEBD7297300A06082A8648CE3D040302303A310B3009060355040613024B52310D300B060355040A0C044943544B311C301A06035504030C134943544B2053656C66205369676E6564204341301E170D3137313231393037303131385A170D3232313231383037303131385A3046310B3009060355040613024B52310D300B060355040A0C044943544B31153013060355040B0C0C6963746B2050726F6A6563743111300F06035504030C0865636320636572743059301306072A8648CE3D020106082A8648CE3D0301070342000409D6749DC55C0EF4360E75819DBD5DBBDD825D39A0B5978A11855E169B3E16497A04F9D4CFCBE2E8B8EB531F6C809CC1EAE6AB23422027800DDCD5855E94B3AEA35A305830090603551D1304023000301F0603551D230418301680141E6D2491359BC123F8A0F2E27C8506C6C319B04B301D0603551D0E04160414900FC9D49F3979D8E78D3EF1BB182445764D7E1C300B0603551D0F0404030205E0300A06082A8648CE3D040302");
	int pub_pos = 227;
	return 0;

#if 0
	ret = g3api_issue_certification(1, pub_pos, ISSUE_CERT_AREA_TYPE::ISCRT_DATA_AREA_0, 0, 19, V2A(vecbyte), vecbyte.size());
	printf("g3api_issue_certification ret:0x%x \n", ret);
#endif
	
	recvbuff_size = 1024;
	vecbyte = NCL::HexStr2Byte("0123456789ABCDEF");
	ret = g3api_test(V2A(vecbyte), vecbyte.size());
	ret = g3api_test2(recvbuff, &recvbuff_size);
	ret = g3api_test3( &pubkey);
	print_result("g3api_test", ret);
	print_value("vecbyte", V2A(vecbyte), vecbyte.size());
	print_value("recvbuff", recvbuff, recvbuff_size);
	print_value("pubkey", &pubkey, sizeof(pubkey));

	

	
	//unsigned char buff[1024] = {0,};
	//int sndsize = serreial->Write(&vecbyte[0], vecbyte.size());
	//printf("sndsize :%d\n",sndsize);
	//int count = 0;
	//NCL::Sleep(100);
	//


	//int ressize = serreial->Read(buff,1024);
	//printf("ressize :%d\n", ressize);
	//
	end_sample();
	

	/*string recv = NCL::BytetoHexStr(buff, ressize);
	printf("%s\n",recv.c_str());
*/
	const char *pchar = g3api_get_lib_version();
	
	
	printf("%s", pchar);
	return 0;
}

