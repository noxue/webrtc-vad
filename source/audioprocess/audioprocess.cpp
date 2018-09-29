// audioprocess.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <stdio.h>
#include "webrtc_vad.h"
#define  FRAMELENGTH 160
#define SAMPLE_RATE 8000
void vadTest(){
	FILE *fpInputf, *fpOutput;
	fpInputf = fopen("F01S00_8k.raw", "rb");
	if (fpInputf == NULL){
		return;
	}
	fpOutput = fopen("F01S00_8k2.raw", "wb");
	VadInst*inst = WebRtcVad_Create();
	WebRtcVad_Init(inst);
	WebRtcVad_set_mode(inst, 3);

	short audioFrame[FRAMELENGTH];
	short audioFrame2[FRAMELENGTH];
	while (!feof(fpInputf))
	{
		int read_size = fread(audioFrame, sizeof(short), FRAMELENGTH, fpInputf);
		int status = WebRtcVad_Process(inst, SAMPLE_RATE, audioFrame, FRAMELENGTH);
		if (status == -1)
		{
			printf("WebRtcVad_Process is error\n");
			return;
		}
		printf("%d", status);
		if (status == 1){
		fwrite(audioFrame, sizeof(short), read_size, fpOutput);
			fflush(fpOutput);
		}
	}
	fclose(fpOutput);
	fclose(fpInputf);
	WebRtcVad_Free(inst);

}

int _tmain(int argc, _TCHAR* argv[])
{
	vadTest();
	return 0;
}


