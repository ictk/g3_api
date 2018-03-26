
typedef int (*PF_INIT_SAMPLE)(void *param);
typedef int(*PF_WAKE_UP_AND_CONVERT_MODE)();
typedef void(*PF_END_SAMPLE)();


typedef struct _tagSAMPLE_FUNCTIONS{
	PF_INIT_SAMPLE init_sample;
	PF_WAKE_UP_AND_CONVERT_MODE wake_up_and_convert_mode;
	PF_END_SAMPLE end_sample;

}SAMPLE_FUNCTIONS, *LPSAMPLE_FUNCTIONS;
