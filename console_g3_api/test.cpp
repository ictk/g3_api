#include<windows.h>
#include<stdio.h>
typedef int(*PFSENDRECV) (const unsigned char*, int, unsigned char*, int*, void*etcparam);
extern "C" int send_n_recv(const unsigned char*snd, int snd_size, unsigned char*recv, int* recv_size, void*etcparam);

void test_load()
{
	HMODULE hmodule = LoadLibrary(L"D:\\PROJECT\\GIANT_3\\SRC\\ctypes_test\\ctypes_test.dll");

}
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