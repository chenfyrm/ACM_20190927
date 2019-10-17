/*
 * ACMapp.c
 *
 *  Created on: 2019-9-30
 *      Author: 700363
 */
#include"acm_dsp.h"
#include"ACMapp.h"


void main(void)
{
	 DspInit();

	SRTO_C();
	SIPR_B();
	ACCL_B();
	UFCO_B();
	PPG3_B();

	static Uint16 Cnt_4ms = 0;
	static Uint16 Cnt_16ms = 0;

	if(Cnt_4ms>10){
	    IPhClGenOvLd();
	    F3PhRef();
	    U3PhRef();
	    U3PhCl();
	    UF3PhCmp();
	    IPhClPsTrs();

	    Cnt_4ms = 0;
	}
	if(Cnt_16ms>43)
	{
	    TFrefRmp();
	    FrefRmp();
	    FrefUDcLk();
	    F3PhSz();
	    U3PhSz();
	    UF3PhSz();

	    Cnt_16ms = 0;
	}

	while(1);
}
