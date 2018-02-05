// console_g3_api.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
//#include "CtrlBASE.h"
#include "CSerialRS232.h"
#include "neoCoLib.h"

#include "g3_api.h"



#pragma comment(lib,"libBASE.lib")

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


extern "C" int send_n_recv(const unsigned char*snd, int snd_size, unsigned char*recv, int* recv_size, void*etcparam){
	CSerialBASE * serreial = (CSerialBASE *)etcparam;
	
	int sndsize = serreial->Write(snd, snd_size);
	printf("SND: %s (%d)\n", NCL::BytetoHexStr(snd, snd_size).c_str(), sndsize);
	unsigned char buff[1024] = { 0, };
	unsigned char first_byte = 0;
	int ressize = 0;
	VECBYTE vec_recv_byte;
	int time_count = 0;
	while (true)
	{
		NCL::Sleep(100);
		ressize = serreial->Read(&first_byte, 1);
		printf("ressize :%d\n", ressize);
		if (ressize == 1) break;
		if (time_count > 10){
			printf("ressize :%d\n", ressize);
		}
		if (time_count * 10 > 1000){
			printf("TIME OUT!!!!!!!!!!!!");
			return -1;
		}
		
		time_count++;
	} 
	vec_recv_byte.push_back(first_byte);

	while (true){
		ressize = serreial->Read(buff, sizeof(buff));
		printf("ressize :%d\n", ressize);
		if (ressize == 0) break;
		NCL::AppendVector(vec_recv_byte, buff, ressize);
		NCL::Sleep(10);
	}

	printf("total ressize :%d\n", vec_recv_byte.size());
	if (recv && vec_recv_byte.size() <= *recv_size ){
		memcpy(recv, V2A(vec_recv_byte), vec_recv_byte.size());
		*recv_size = vec_recv_byte.size();

	}
	
	
	printf("RECV %s \n", NCL::BytetoHexStr(V2A(vec_recv_byte), vec_recv_byte.size()).c_str());



	return 0;
}


extern "C" int send(unsigned char *buff, int length, void* etc){
	return 0;
}
extern "C"  int receiv(unsigned char *buff, int length, void* etc){
	return 0;
}
int _tmain(int argc, _TCHAR* argv[])
{
	int ret = 0;
	CSerialBASE * serreial = new CSerialRS232("\\\\.\\COM10");
//	g3api_set_etc_param(serreial);
	
	serreial->open();


	unsigned char recvbuff[1024];
	
	int recvbuff_size = 1024;
	g3api_set_user_send_recv_pf(send_n_recv, serreial);

	//g3api_set_etc_param(serreial);
	VECBYTE vecbyte = NCL::HexStr2Byte("FE0000000000");
#if 0
	g3api_raw_snd_recv(&vecbyte[0], vecbyte.size(), recvbuff, &recvbuff_size);
	recvbuff_size = 1024;

	vecbyte = NCL::HexStr2Byte("FF0000000000");
	g3api_raw_snd_recv(&vecbyte[0], vecbyte.size(), recvbuff, &recvbuff_size);
	
		
	recvbuff_size = 1024;

	ret = g3api_get_chellange(32, recvbuff, &recvbuff_size);


	printf("ret:0x%x recv %s %d \n", ret  ,NCL::BytetoHexStr(recvbuff, recvbuff_size).c_str(), recvbuff_size);

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
#endif
	vecbyte = NCL::HexStr2Byte("72CF56F5BF877DCF5823691682E9824C0B9742D1E0B41D288B478ECEF5218BAA");
	ST_SIGN_ECDSA sign;
	ret = g3api_sign(4, SIGN_OPTION::SIGN_ECDSA, V2A(vecbyte), vecbyte.size(), &sign, sizeof(ST_SIGN_ECDSA));
	printf("ret:0x%x recv %s %d \n", ret, NCL::BytetoHexStr(&sign, sizeof(sign)).c_str(), recvbuff_size);

	ret = g3api_verify(1, VERIFY_OPTION::VERYFY_ECDSA,V2A(vecbyte), vecbyte.size(), &sign, sizeof(ST_SIGN_ECDSA));
	printf("ret:0x%x recv %s %d \n", ret, NCL::BytetoHexStr(&sign, sizeof(sign)).c_str(), recvbuff_size);
	
	//unsigned char buff[1024] = {0,};
	//int sndsize = serreial->Write(&vecbyte[0], vecbyte.size());
	//printf("sndsize :%d\n",sndsize);
	//int count = 0;
	//NCL::Sleep(100);
	//


	//int ressize = serreial->Read(buff,1024);
	//printf("ressize :%d\n", ressize);
	//
	serreial->close();

	/*string recv = NCL::BytetoHexStr(buff, ressize);
	printf("%s\n",recv.c_str());
*/
	const char *pchar = g3api_get_lib_version();
	
	
	printf("%s", pchar);
	return 0;
}

