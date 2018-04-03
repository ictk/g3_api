#include<windows.h>
#include<stdio.h>
#include <openssl/hmac.h>
#include <g3_api.h>



extern "C" int CALLTYPE send_n_recv(const unsigned char*snd, int snd_size, unsigned char*recv, int* recv_size, void*etcparam);
void print_value(const char * title, const void *buff, int size);


#ifndef min
#define min(a,b)            (((a) < (b)) ? (a) : (b))
#endif



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
void test_hmac()
{
	unsigned char key[] = {0x09, 0xA8, 0xD1, 0xAB, 0xDE, 0x2C, 0xCA, 0xC2, 0x1C, 0x3D, 0x82, 0xB4, 0xD3, 0x84, 0xBA, 0x45, };
	unsigned char msg[] = { 0x52, 0xAD, 0x1D, 0x1D, 0x34, 0xC3, 0xCD, 0x12, 0x90, 0x60, 0x9F, 0x2A, 0x51, 0xC7, 0x01, 0x8A, 0x27, 0xF9, 0xDC, 0xEC, 0x22, 0xE1, 0x27, 0x48, 0x31, 0xE5, 0x64, 0xF8, 0x8B, 0x95, 0x40, 0xED, };
	unsigned char calc_crc[] = { 0x66, 0x15, 0x38, 0xFC, 0xCE, 0xEB, 0x60, 0x3E, 0x28, 0x40, 0x86, 0x9A, 0xF5, 0xBF, 0x63, 0x91, 0x62, 0x98, 0x50, 0x64, 0x22, 0x2F, 0xF0, 0x8B, 0x5E, 0x2A, 0xA3, 0x60, 0x6A, 0xD4, 0xF5, 0xD0, };
	
	unsigned char outbuff[128];
	unsigned int outlen = 128;
	HMAC(EVP_sha256(),
		key, sizeof(key),
		msg, sizeof(msg),
		outbuff, &outlen);

#if 0
	HMAC_CTX ctx;
	const EVP_MD  *md = EVP_sha256();

	HMAC_CTX_init(&ctx);

	HMAC_Init(&ctx, key, sizeof(key), md);
	HMAC_Update(&ctx, msg, sizeof(msg));
	unsigned char outbuff[128];
	unsigned int outlen = 128;
	HMAC_Final(&ctx, outbuff, &outlen);

	HMAC_CTX_cleanup(&ctx);
	HMAC_cleanup(&ctx);

#endif // 0

}


#if 1



#define uint8_t unsigned char
#define uint32_t unsigned int


#define LibUtilMemCpy memcpy
#define LibUtilMemAlloc malloc
#define LibUtilMemFree free

#define MAX_PRF_LABSEED 128 /* Maximum label + seed len */
#define BUFFER_E -132
#define WC_SHA256 2
#define P_HASH_MAX_SIZE  32
#define WC_SHA256_DIGEST_SIZE P_HASH_MAX_SIZE
#define CRYPTO_SHA256_HASH_LEN	32


#define CRYPTO_ERROR_NONE					0x00000000
#define CRYPTO_ERROR_INVALID_ARGS			0xFFFF0001
#define CRYPTO_ERROR_KEYGEN_FAIL			0xFFFF0002
#define CRYPTO_ERROR_EXPORT_FAIL			0xFFFF0003
#define CRYPTO_ERROR_IMPORT_FAIL			0xFFFF0004
#define CRYPTO_ERROR_MEMORY					0xFFFF0005
#define CRYPTO_ERROR_BUFFER_SHORT			0xFFFF0006
#define CRYPTO_ERROR_SIGN_FAIL				0xFFFF0007
#define CRYPTO_ERROR_RANDOM_FAIL			0xFFFF0008
#define CRYPTO_ERROR_VERIFY_FAIL			0xFFFF0009
#define CRYPTO_ERROR_VERIFY_ERROR			0xFFFF000A
#define CRYPTO_ERROR_INVALID_LENGTH			0xFFFF000B
#define CRYPTO_ERROR_INVALID_MODE			0xFFFF000C
#define CRYPTO_ERROR_NOT_SUPPORT			0xFFFF000D
#define CRYPTO_ERROR_GEN_PUB_KEY_FAIL		0xFFFF000E
#define CRYPTO_ERROR_GET_PUB_KEY_FAIL		0xFFFF000F
#define CRYPTO_ERROR_GET_COMP_PUB_KEY_FAIL	0xFFFF0010
#define CRYPTO_ERROR_DEVICE					0xFFFF0011
#define CRYPTO_ERROR_UNKNOWN				0xFFFFFFFF

#define CRYPTO_ERROR_T int
#define uint32_t unsigned int
#define LOGE(a_)



int PRF(uint8_t* digest, uint32_t digLen, const uint8_t* secret, uint32_t secLen,
	const uint8_t* label, uint32_t labLen, const uint8_t* seed, uint32_t seedLen);
CRYPTO_ERROR_T LibCrypto_PRF(uint8_t* digest, uint32_t digLen, const uint8_t* secret, uint32_t secLen,
	const uint8_t* label, uint32_t labLen, const uint8_t* seed, uint32_t seedLen);

void test_prf()
{
	unsigned char secret[] = { 0xA8, 0x9C, 0x8F, 0xDB, 0x82, 0xAD, 0xB2, 0x3F, 0xC6, 0x95, 0xFD, 0x0E, 0x56, 0xBE, 0x5B, 0xA1, 0x9A, 0x74, 0x1C, 0xF6, 0x32, 0x63, 0x05, 0xC6, 0x8C, 0xBF, 0x42, 0xB8, 0xBE, 0xD0, 0xFE, 0xDB, };
	unsigned char label[] = { 0x6D, 0x61, 0x73, 0x74, 0x65, 0x72, 0x20, 0x73, 0x65, 0x63, 0x72, 0x65, 0x74, };
	unsigned char seed[] = { 0x1A, 0xD0, 0x64, 0xDD, 0xF5, 0x74, 0xE9, 0xA3, 0xA0, 0x40, 0x61, 0x06, 0xFB, 0x21, 0x6E, 0xD6, 0xF7, 0x8A, 0xAF, 0x37, 0x3D, 0x0F, 0xCE, 0xC7, 0xD7, 0x40, 0xCC, 0x75, 0x6E, 0x75, 0xFD, 0xF0, 0x1C, 0x58, 0xEB, 0x63, 0x57, 0xFC, 0x47, 0xF5, 0xDE, 0x88, 0x65, 0x3D, 0xCF, 0xB3, 0x6E, 0x1B, 0x88, 0x81, 0xC0, 0x96, 0xC2, 0xBB, 0x23, 0x78, 0xF2, 0x65, 0x3C, 0x07, 0x6E, 0x15, 0xB2, 0x9C, };
	unsigned char result[] = { 0x04, 0x89, 0x26, 0x81, 0x31, 0xBB, 0xF3, 0xF5, 0x48, 0xA6, 0x98, 0x3E, 0x80, 0xAF, 0xC3, 0x23, 0xAA, 0xB5, 0x22, 0x66, 0xD2, 0x32, 0x9E, 0x39, 0xE3, 0xA8, 0x26, 0xEA, 0xFE, 0xF4, 0x60, 0x74, 0x50, 0x79, 0xB7, 0xC6, 0x3B, 0xD0, 0xBF, 0x2A, 0xB8, 0x07, 0xCF, 0x0E, 0xBD, 0x2F, 0xD3, 0x1D, };
	unsigned char calc_result[48];
	LibCrypto_PRF(calc_result, 48,
		secret, sizeof(secret),
		label, sizeof(label),
		seed, sizeof(seed));
	print_value("calc_result", calc_result, 48);
	print_value("result", result, 48);
	if (!memcmp(result, calc_result, 48)){
		printf("same result\n");
	}


}



CRYPTO_ERROR_T LibCrypto_SHA_256_HMAC
(
void * pKey, uint32_t nKeyLen,
void * pData, uint32_t nDataLen,
void * pOutHmacBuf, uint32_t nBufLen
){
	unsigned int outbuff = nBufLen;
	unsigned char *retaaa = HMAC(EVP_sha256(), 
		pKey, nKeyLen, 
		(unsigned char*)pData, nDataLen,
		(unsigned char*)pOutHmacBuf, &outbuff);
	if (outbuff != nBufLen) return -1;
	
	return 0;
}

/* compute p_hash for MD5, SHA-1, SHA-256, or SHA-384 for TLSv1 PRF */
int p_hash(uint8_t* result, uint32_t resLen, const uint8_t* secret,
	uint32_t secLen, const uint8_t* seed, uint32_t seedLen)
{
	uint32_t len = P_HASH_MAX_SIZE;
	uint32_t times;
	uint32_t lastLen;
	uint32_t lastTime;
	uint32_t i;
	uint32_t idx = 0;
	int    ret = 0;
	uint8_t* previous = (uint8_t*)LibUtilMemAlloc(P_HASH_MAX_SIZE);  /* max size */
	uint8_t* tmpprevious = (uint8_t*)LibUtilMemAlloc(P_HASH_MAX_SIZE);  /* max size */
	uint8_t* previous_seed = (uint8_t*)LibUtilMemAlloc(P_HASH_MAX_SIZE + MAX_PRF_LABSEED);  /* max size */
	uint8_t* current = (uint8_t*) LibUtilMemAlloc(P_HASH_MAX_SIZE);   /* max size */

	unsigned int tmpprevious_size = P_HASH_MAX_SIZE;
	unsigned int previous_size = P_HASH_MAX_SIZE;
	unsigned int current_size = P_HASH_MAX_SIZE;

	len = WC_SHA256_DIGEST_SIZE;

	times = resLen / len;
	lastLen = resLen % len;

	if (lastLen)
		times += 1;

	lastTime = times - 1;

		//unsigned int output_size = P_HASH_MAX_SIZE;
		//unsigned char *retaaa = HMAC(EVP_sha256(), secret, secLen, seed, seedLen, previous, &previous_size);
	ret = LibCrypto_SHA_256_HMAC((void*)secret, secLen, (void*)seed, seedLen, previous, P_HASH_MAX_SIZE);
		
		if (ret != 0) goto END;
			//print_hexdumpbin("A1", previous, P_HASH_MAX_SIZE);
	for (i = 0; i < times; i++) {

		LibUtilMemCpy(previous_seed, previous, previous_size);
		LibUtilMemCpy(previous_seed + previous_size , seed, seedLen);
				
		int intput_length = seedLen + previous_size;
		current_size = P_HASH_MAX_SIZE;
		print_value("previous_seed", previous_seed, intput_length);
		//HMAC(EVP_sha256(), secret, secLen, previous_seed, intput_length, current, &current_size);
		ret = LibCrypto_SHA_256_HMAC((void*)secret, secLen, (void*)previous_seed, intput_length, current, P_HASH_MAX_SIZE);
		print_value("current", current, current_size);
		if (ret != 0) goto END;

		if (ret != 0)
			break;
		//print_hexdumpbin("current", current, P_HASH_MAX_SIZE);
		if ((i == lastTime) && lastLen)
			LibUtilMemCpy(&result[idx], current,
			min(lastLen, P_HASH_MAX_SIZE));
		else {
			LibUtilMemCpy(&result[idx], current, len);
			idx += len;
			//output_size = P_HASH_MAX_SIZE;

			LibUtilMemCpy(tmpprevious, previous, previous_size);
			tmpprevious_size = previous_size;
			previous_size = P_HASH_MAX_SIZE;
			//HMAC(EVP_sha256(), secret, secLen, tmpprevious, tmpprevious_size, previous, &previous_size);
			ret = LibCrypto_SHA_256_HMAC((void*)secret, secLen,(void*)tmpprevious, tmpprevious_size, previous, P_HASH_MAX_SIZE);
			if (ret != 0) goto END;

		}
	}

END:
	if (previous) LibUtilMemFree(previous);
	if (tmpprevious) LibUtilMemFree(tmpprevious);
	if (previous_seed) LibUtilMemFree(previous_seed);
	if (current) LibUtilMemFree(current);
	return ret;
}

/* Wrapper to call straight thru to p_hash in TSL 1.2 cases to remove stack
use */
int PRF(uint8_t* digest, uint32_t digLen, const uint8_t* secret, uint32_t secLen,
	const uint8_t* label, uint32_t labLen, const uint8_t* seed, uint32_t seedLen	)
{
	int ret = 0;

	
	
	uint8_t labelSeed[MAX_PRF_LABSEED]; /* labLen + seedLen is real size */

	if (labLen + seedLen > MAX_PRF_LABSEED)
		return BUFFER_E;


	LibUtilMemCpy(labelSeed, label, labLen);
	LibUtilMemCpy(labelSeed + labLen, seed, seedLen);

	/* If a cipher suite wants an algorithm better than sha256, it
	* should use better. */
		
	ret = p_hash(digest, digLen, secret, secLen, labelSeed,
		labLen + seedLen);




	return ret;
}


CRYPTO_ERROR_T LibCrypto_PRF(uint8_t* digest, uint32_t digLen, const uint8_t* secret, uint32_t secLen,
	const uint8_t* label, uint32_t labLen, const uint8_t* seed, uint32_t seedLen)
{
	CRYPTO_ERROR_T ret = CRYPTO_ERROR_NONE;
	//	uint32_t len = CRYPTO_SHA256_HASH_LEN;
	uint32_t times;
	uint32_t lastLen;
	uint32_t lastTime;
	uint32_t i;
	uint32_t idx = 0;
	uint32_t previous_seed_size;
	uint8_t previous[CRYPTO_SHA256_HASH_LEN];  /* max size */
	//uint8_t tmpprevious[CRYPTO_SHA256_HASH_LEN];;  /* max size */
	uint8_t current[CRYPTO_SHA256_HASH_LEN];   /* max size */

	uint8_t labelSeed[MAX_PRF_LABSEED]; /* labLen + seedLen is real size */
	uint8_t previous_seed[CRYPTO_SHA256_HASH_LEN + MAX_PRF_LABSEED];
	int label_seed_size = labLen + seedLen;
	


	//uint8_t* labelSeed = NULL;// (uint8_t*)LibUtilMemAlloc(labLen + seedLen);


	LibUtilMemCpy(labelSeed, label, labLen);
	LibUtilMemCpy(labelSeed + labLen, seed, seedLen);


	
	
	ret = LibCrypto_SHA_256_HMAC((void*)secret, secLen, (void*)labelSeed, label_seed_size, previous, CRYPTO_SHA256_HASH_LEN);
	if (ret != 0) goto END;

	times = digLen / WC_SHA256_DIGEST_SIZE;
	lastLen = digLen % WC_SHA256_DIGEST_SIZE;
	if (lastLen)
		times += 1;

	lastTime = times - 1;
	idx = 0;

	for (i = 0; i < times; i++) {

		LibUtilMemCpy(previous_seed, previous, CRYPTO_SHA256_HASH_LEN);
		LibUtilMemCpy(previous_seed + CRYPTO_SHA256_HASH_LEN, labelSeed, label_seed_size);

		//previous_seed_size = CRYPTO_SHA256_HASH_LEN +labLen + seedLen;
		//current_size = CRYPTO_SHA256_HASH_LEN;
		//print_value("previous_seed", previous_seed, labLen + seedLen);
		ret = LibCrypto_SHA_256_HMAC((void*)secret, secLen, (void*)previous_seed, CRYPTO_SHA256_HASH_LEN + label_seed_size, current, CRYPTO_SHA256_HASH_LEN);

		if (ret != CRYPTO_ERROR_NONE) break;

		if ((i == lastTime) && lastLen)
			LibUtilMemCpy(&digest[idx], current, min(lastLen, CRYPTO_SHA256_HASH_LEN));
		else {
			LibUtilMemCpy(&digest[idx], current, WC_SHA256_DIGEST_SIZE);
			idx += WC_SHA256_DIGEST_SIZE;

//			LibUtilMemCpy(tmpprevious, previous, WC_SHA256_DIGEST_SIZE);
			ret = LibCrypto_SHA_256_HMAC((void*)secret, secLen, (void*)previous, WC_SHA256_DIGEST_SIZE, previous, CRYPTO_SHA256_HASH_LEN);
			if (ret != 0) break;

		}
	}

END:

	return ret;
}

#endif
