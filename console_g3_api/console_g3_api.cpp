// console_g3_api.cpp : �ܼ� ���� ���α׷��� ���� �������� �����մϴ�.
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
	unsigned char buff[1024] = { 0, };
	unsigned char first_byte = 0;
	int ressize = 0;
	VECBYTE vec_recv_byte;
	while (true)
	{
		ressize = serreial->Read(&first_byte, 1);
		printf("ressize :%d\n", ressize);
		if (ressize == 1) break;
		NCL::Sleep(10);
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
	
	CSerialBASE * serreial = new CSerialRS232("\\\\.\\COM10");
//	g3api_set_etc_param(serreial);
	
	serreial->open();
	VECBYTE vecbyte = NCL::HexStr2Byte("070000000D00000000240307842000005F3900");

	unsigned char recvbuff[1024];
	
	int recvbuff_size = 1024;
	g3api_set_user_send_recv_pf(send_n_recv, serreial);
	//g3api_set_etc_param(serreial);
	g3api_raw_snd_recv(&vecbyte[0], vecbyte.size(), recvbuff, &recvbuff_size);

	g3api_get_chellange(32, recvbuff,&recvbuff_size);


	printf("recv %s \n", NCL::BytetoHexStr(recvbuff, recvbuff_size).c_str());
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

