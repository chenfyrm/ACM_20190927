/*
 * Module.h
 *
 *  Created on: 2019-9-30
 *      Author: 700363
 */

#ifndef MODULE_H_
#define MODULE_H_

#ifdef __cplusplus
extern "C" {
#endif

/*SIPRDA
 *
 *
 *
 *
 * */
struct	SIPRDA{
	/*input*/
	float32 XU_DcLk1;

	float32 XU_3Ph;

	float32 XI_PhA;
	float32 XI_PhB;
	float32 XI_PhC;

	float32	XU_Bt_Rw;
	float32 XI_Bt_Rw;
	float32 XI_BtCg_Rw;

	float32 XT_3PhSmpRnd;//3Ph inverter sample period time
	cfloat32 WU_3PhAB;//
	float32 WF_3Ph;//
	float32 WU_3PhAbs;

	Uint16	A_CvOp:1;//

	/*output*/
	float32 XU_DcLk1Flt;//
	float32 XU_DcLk2Flt;

	float32	XU_3PhRms;
	float32	XU_3PhAbs;
	float32	XU_3PhRe;
	float32	XU_3PhIm;
	float32 XT_U3Ph;//period time of 3Ph output load voltage

	float32 XI_PhAbs_Flt;
	float32	XI_PhAct_Flt2;
	float32	XI_PhRct_Flt2;
	float32 XI_PhReFix;
	float32 XI_PhImFix;

	float32 XP_3Ph_Flt;

	float32 XU_BtFlt;
	float32 XI_BtFlt;
	float32 XI_BtCg2Flt;

	/*state*/
	float32 WX_Theta;

	/*temp*/
	cfloat32 XI_PhAB;
	cfloat32 XI_PhDQ;
	cfloat32 XI_PhDQ_Flt;
	float32	XP_3Ph;
	float32 XQ_3Ph;
	float32 XQ_3Ph_Flt;
	float32	XI_PhAbs;
	float32 XI_PhAct;
	float32	XI_PhAct_Flt;
	float32	XI_PhRct;
	float32	XI_PhRct_Flt;
	float32	XF_U3Ph;
	float32 WU_3PhAbs_Flt;

	Uint16 B_IphA;
	Uint16 B_IphB;
	Uint16 B_IphC;

	/*parameter*/
	float32	PT_3PhSmp;
	float32	PN_IPhFixMcu_Flt;
	float32 PD_ThetaFiOs;
	float32 PN_UDcLk_Flt;
	float32 PN_URef_Flt;
	float32 PN_IPhActRct_Flt;
	float32 PN_IPhActRctMcu_Flt;
	float32 PN_IPhAbs_Flt;
	float32 PN_PQ3PhMcu_Flt;
	float32 PN_IPhDQ_Flt;

	/*reserved*/
	float32 XI_DfIn;
	float32 XI_Rct1_Rw;
	float32 XI_Rct2_Rw;
	float32 XI_Rct3_Rw;

	float32 XU_PhInRms;
	float32 XI_PhInRms;
	float32 XI_DfInFlt;
	float32 XI_Rct1_Rms;
	float32 XI_Rct2_Rms;
	float32 XI_Rct3_Rms;
	float32 XP_2qc;

};

extern struct SIPRDA sipr;
extern void SIPR_B(struct SIPRDA *p);


/*ACCLDA
 *
 *
 *
 *
 * */
//struct	{
//	/*input*/
//	/*output*/
//	/*state*/
//	/*temp*/
//	/*parameter*/
//	/*reserved*/
//};

struct	ACCLDA{
	/*input*/
	float32	XI_PhAbs;
	float32	XI_PhAct_Flt;
	float32	XI_PhRct_Flt;

	float32 XX_IPhClTrsKpAbs;
	float32	WI_PhAct;
	float32 XX_IPhClTrsKpAct;
	float32	WI_PhRct;
	float32	XX_IPhClTrsKpRct;

	float32	XT_3PhSmpRnd;

	/*output*/
	float32 WU_IPhClTrs;
	float32	WU_IPhClTrs_Flt;

	Uint16	S_IPhClTrsAv:1;

	/*state*/

	/*temp*/

	/*parameter*/
	float32	PU_PhClTrsMax;
	float32	PI_PhClTrsAbsLim;
	float32	PN_URefIPhClTrs_Flt;

	/*reserved*/

};

extern struct ACCLDA accl;
extern void ACCL_B(struct ACCLDA *p);


/*BACCDA
 *
 *
 *
 *
 * */
//struct	BACCDA{
//	/*input*/
//	/*output*/
//	/*state*/
//	/*temp*/
//	/*parameter*/
//	/*reserved*/
//};

#ifdef __cplusplus
}
#endif

#endif /* MODULE_H_ */
