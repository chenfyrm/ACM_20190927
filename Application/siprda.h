/*
 * siprda.h
 *
 *  Created on: 2019-9-27
 *      Author: 700363
 */

#ifndef SIPRDA_H_
#define SIPRDA_H_

#ifdef __cplusplus
extern "C" {
#endif

struct	SIPRDA{
	/*input*/
	float32 XI_PhA;
	float32 XI_PhB;
	float32 XI_PhC;
	float32	XU_PhABLk;

	float32	WU_3PhAB;

	/*output*/
	cfloat32 XI_PhAB;
	cfloat32 XI_PhDQ;
	cfloat32 XI_PhDQ_Flt;
	float32 XI_PhReFix;
	float32 XI_PhImFix;
	float32	XP_3Ph;
	float32 XP_3Ph_Flt;
	float32 XQ_3Ph;
	float32 XQ_3Ph_Flt;
	float32 XI_PhAct;
	float32	XI_PhAct_Flt;
	float32	XI_PhAct_Flt2;
	float32	XI_PhRct;
	float32	XI_PhRct_Flt;
	float32	XI_PhRct_Flt2;
	float32	XU_3PhRe;
	float32	XU_3PhIm;
	float32	XU_3PhAbs;

	float32	XU_3PhRms;
	float32	WX_Theta;
	float32	XF_U3Ph;
	float32 XU_DcLkFlt;

	float32 WU_3PhAbs_Flt;
	float32 XI_PhAbs_Flt;

	/*state*/


	/*parameter*/
	float32	PN_IPhFixMcu_Flt;
	float32 PD_ThetaFiOs;
	float32 PN_UDcLk_Flt;
	float32 PN_URef_Flt;
	float32 PN_IPhActRct_Flt;
	float32 PN_IPhActRct_Flt;
	float32 PN_IPhActRctMcu_Flt;
	float32 PN_IPhAbs_Flt;
	float32 PN_PQ3PhMcu_Flt;
	float32 PN_PQ3PhMcu_Flt;
	float32 PN_IPhDQ_Flt;




	/*reserved*/


};

void SIPR_B(SIPRDA *p,float32 Tsc);

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif /* SIPRDA_H_ */
