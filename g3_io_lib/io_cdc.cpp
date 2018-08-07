#define NULL 0
#include "CSerialRS232.h"
#include "neoCoLib.h"




#include "neoDebug.h"
#include "g3_api.h"
#include "g3_io_lib.h"
#include "util.h"
#include "stdio.h"
#ifndef min
#define min(a,b)    (((a) < (b)) ? (a) : (b))
#endif




extern FILE * _fp;

#pragma pack(push, 1)   
typedef struct _tagHEADER_WRITE_IEB100_PACKET{
	unsigned char  rom_inst;
	unsigned long  body_size_big_end;//dummy+res_size+rom_type+data_size
	unsigned long  dummy;
	unsigned char  res_size;
	//unsigned char  rom_type;
}HEADER_WRITE_IEB100_PACKET, *LPHEADER_WRITE_IEB100_PACKET;

typedef struct _tagWRITE_IEB100_PACKET{
	HEADER_WRITE_IEB100_PACKET header;
	unsigned char data[1];;
}WRITE_IEB100_PACKET, *LPWRITE_IEB100_PACKET;
#pragma pack(pop)  
typedef struct _tagINTER_PARAMS{
	

	CSerialBASE * pserreial;
	int mode;

}INTER_PARAMS, *LPINTER_PARAMS;
INTER_PARAMS _inter_params = { 0, };


extern "C" int init_sample_ieb100cdc(void *param);
extern "C" int wake_up_and_convert_mode_ieb100cdc();
extern "C" void end_sample_ieb100cdc();
extern "C" void get_functions_ieb100cdc(LPST_G3_IO_LIB_FUNCTIONS lpsamplefunction);

ST_G3_IO_LIB_FUNCTIONS  _samplefunction= {
	init_sample_ieb100cdc,
	wake_up_and_convert_mode_ieb100cdc,
	end_sample_ieb100cdc

};

void get_functions_ieb100cdc(LPST_G3_IO_LIB_FUNCTIONS lpsamplefunction)
{
	*lpsamplefunction = _samplefunction;

}


//INTER_PARAMS _inter_params = { 0, };


LPWRITE_IEB100_PACKET make_write_ieb100_packet(char rom_inst, char res_size, const void * data, int data_size, int *packet_size){

	//sizeof(WRITE_PACKET) is included crc
	int total_write_packet_size = sizeof(HEADER_WRITE_IEB100_PACKET) + data_size + 1;//included crc
	int body_size_big_end = 4 + 1 + 1 + data_size;//dummy+res_size+rom_type+data


	LPWRITE_IEB100_PACKET lp_write_packet = (LPWRITE_IEB100_PACKET)malloc(total_write_packet_size);
	memset(lp_write_packet, 0x00, total_write_packet_size);
	lp_write_packet->header.rom_inst = rom_inst;
	lp_write_packet->header.body_size_big_end = body_size_big_end;
	//	lp_write_packet->header.rom_type = rom_type;

	swap_bytes(&lp_write_packet->header.body_size_big_end, 4);
	lp_write_packet->header.res_size = res_size;

	if (data_size > 0) memcpy(lp_write_packet->data, data, data_size);
	if (packet_size) *packet_size = total_write_packet_size;

	//fprintf(_fp,"total_write_packet_size:%d \body_size_big_end:%d\n", total_write_packet_size, body_size_big_end);

	return lp_write_packet;
}

extern "C"  int CALLTYPE send_n_recv(const unsigned char*snd, int snd_size, unsigned char*recv, int* recv_size, void*etcparam)
{

	LPINTER_PARAMS inter_param = (LPINTER_PARAMS)etcparam;
	CSerialBASE * serreial = inter_param->pserreial;
	LPWRITE_IEB100_PACKET lpwrite_ieb100_packet = NULL;
	unsigned char*sndbuff = (unsigned char*)snd;

	fprintf(_fp,"send_n_recv\n");
	fprintf(_fp,"PURE SND: %s (%d)\n", NCL::BytetoHexStr(snd, snd_size).c_str(), snd_size);
	if (!serreial) return -1;

	if (inter_param->mode){
		int packet_ieb100_size = 0;
		lpwrite_ieb100_packet = make_write_ieb100_packet(0x7, *recv_size, snd, snd_size, &packet_ieb100_size);


		fprintf(_fp,"SND: %s (%d)\n", NCL::BytetoHexStr(lpwrite_ieb100_packet, packet_ieb100_size).c_str(), packet_ieb100_size);
		sndbuff = (unsigned char*)lpwrite_ieb100_packet;
		snd_size = packet_ieb100_size;

	}
	
	int sndsize = serreial->Write((unsigned char*)sndbuff, snd_size);
	if (lpwrite_ieb100_packet) free(lpwrite_ieb100_packet);

	unsigned char buff[1024] = { 0, };
	unsigned char first_byte = 0;
	int ressize = 0;
	VECBYTE vec_recv_byte;
	int time_count = 0;
	int unit_delay = 100;
	while (true)
	{

		ressize = serreial->Read(&first_byte, 1);
		if (ressize == 1) break;

		if (time_count * unit_delay > 300){
			fprintf(_fp,"first unsigned char :%d\n", time_count);
		}

		if (time_count * unit_delay > 100000){
			fprintf(_fp,"TIME OUT!!!!!!!!!!!!");
			return -1;
		}
		NCL::Sleep(unit_delay);

		time_count++;
	}
	fprintf(_fp,"first ressize :%x %d\n", first_byte, ressize);
	vec_recv_byte.push_back(first_byte);

	while (true){
		ressize = serreial->Read(buff, sizeof(buff));
		if (ressize == 0) break;
		NCL::AppendVector(vec_recv_byte, buff, ressize);
		NCL::Sleep(10);
	}

	fprintf(_fp,"total ressize :%d\n", vec_recv_byte.size());
	int real_recv_size = min((unsigned char)first_byte, 255);

	fprintf(_fp, "real_recv_size : %d\n", real_recv_size);

	if (recv && real_recv_size <= *recv_size){
		memcpy(recv, V2A(vec_recv_byte), vec_recv_byte.size());
		*recv_size = real_recv_size;

	}
	


	fprintf(_fp,"RECV %s (%d) \n", NCL::BytetoHexStr(V2A(vec_recv_byte), real_recv_size).c_str(), real_recv_size);



	return 0;
}


int init_sample_ieb100cdc(void *param)
{
	char *str_param = (char *)param;
	CSerialBASE * serreial = new CSerialRS232(str_param);
	_inter_params.pserreial = serreial;
	_inter_params.mode = 0;
	g3api_set_user_send_recv_pf(send_n_recv, &_inter_params);

	if (!serreial->open()){
		fprintf(_fp,"\nport is not open\n");
		return -1;

	}
	return 0;


}
void end_sample_ieb100cdc()
{
	_inter_params.pserreial->close();
}

int wake_up_and_convert_mode_ieb100cdc()
{
	unsigned char wake_buff[] = { 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, };
	unsigned char convert_inst[] = { 0xFE, 0x00, 0x00, 0x00, 0x00, 0x00, };
	
	unsigned char recvbuff[256];
	int recvbuff_size;

	recvbuff_size = 1024;
	int ret = g3api_raw_snd_recv(wake_buff, sizeof(wake_buff), recvbuff, &recvbuff_size);
	fprintf(_fp,"ret:0x%x recv %s %d \n", ret, NCL::BytetoHexStr(recvbuff, recvbuff_size).c_str(), recvbuff_size);
	
	recvbuff_size = 1024;
	g3api_raw_snd_recv(convert_inst, sizeof(convert_inst), recvbuff, &recvbuff_size);
	fprintf(_fp,"ret:0x%x recv %s %d \n", ret, NCL::BytetoHexStr(recvbuff, recvbuff_size).c_str(), recvbuff_size);

	_inter_params.mode = 1;

	return 0;
}

void convert_up(){

}
