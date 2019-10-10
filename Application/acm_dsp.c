#include "math.h"

#include "UserDefs.h"
#include "UserMath.h"
#include "complex.h"
#include "control.h"

#include "acm_dsp.h"

#define SIMULATION 1

volatile struct Dsp_Data DspData;

struct IIRFILTER_2ND U3PhRe, U3PhIm;
struct PI_CONTROLLER PI_U3PhCl;

/*IRQB 370us*/
void SIPR_B(void);
void ACCL_B(void);
void UFCO_B(void);
void PPG3_B(void);

/*IRQC 200us*/
void BCHO_C(void);
void SFPA_C(void);
void DUVP_C(void);
void DOVP_C(void);
void ERFL_C(void);
void OROP_C(void);
void PABO_C(void);
void PROT_C(void);
void SRTO_C(void);
void HWSS_C(void);

/*T2 1ms*/
void HSTI_T2(void);
void FPGI_T2(void);
void MEMS_T2(void);
void ACCL_T2(void);
void ACLS_T2(void);
void OVPT_T2(void);
void OROP_T2(void);
void POCP_T2(void);
void AICS_T2(void);
void HWTS_T2(void);
void HWSS_T2(void);
void FPGO_T2(void);
void DIAG_T2(void);
void HSTO_T2(void);

/*T3 100ms*/
void SFSU_T3(void);
void DIAG_T3(void);
void DCUI_T3(void);
void HSTP_T3(void);
void HWSS_T3(void);

/**/
void DdCmp(void);

/**/
void DspInit(void) {

	if (SIMULATION) {
	} else {
		Uint16 i;
		for (i = 0; i < sizeof(DspData); i++) {
			*((Uint16*) &DspData + i) = 0;
		}
	}

	DspData.PN_IPhFixMcu_Flt = 4.0; //rad/s
	DspData.PN_U3PhRms_Flt = 5.0; //5
	DspData.PN_UDcLk_Flt = 100.0;
	DspData.PN_URef_Flt = 600.0;
	DspData.PN_IPhActRct_Flt = 2000.0;
	DspData.PN_IPhActRctMcu_Flt = 20.0;
	DspData.PN_IPhAbs_Flt = 60.0;
	DspData.PN_PQ3PhMcu_Flt = 60.0;
	DspData.PN_IPhDQ_Flt = 18.0;
	DspData.PN_IPhRms_Flt = 30.0;
	DspData.PN_URefIPhClTrs_Flt = 20.0;

	DspData.PU_PhClTrsMax = 75.0; //	75
	DspData.PI_PhClTrsAbsLim = 600.0; //	600

	if (SIMULATION) {
		DspData.PD_ThetaFiOs = PI / 3.0 - PI / 180.0;

	} else {
		DspData.PD_ThetaFiOs = PI / 3.0 - 4.5 / 180.0 * PI; //同步相位补偿,1.047 线电压落后相电压60deg,死区时间造成电压相位滞后
	}
	DspData.PZ_3PhFiNdRe = 0.078; //	0,078 滤波电感电阻
	DspData.PZ_3PhFiNdIm = 0.207; //	0,207滤波电感电抗
	DspData.PZ_3PhFiCaIm = -5.47; //	-5,47 滤波电容电抗折算到一次侧
	DspData.PZ_3PhTfRe = 0.0; //	0
	DspData.PZ_3PhTfIm = 0.0; //	0

	/*直流振荡抑制*/
	DspData.L_UDcLkStbEn = TRUE; //	TRUE
	DspData.PN_UDcLkStbSliSmt = 2200.0; //
	DspData.PN_UDcLkStbHevSmt = 13.5; //
	DspData.PU_DcLkStbMaxMin = 100.0; //
	DspData.PX_KpUDcLkStb = 150.0; //需调试
	DspData.PX_KpUDcLkVoStbFb = 0.00002;

	/**/
	//	data->PARADP_PX_3PhClRtMax = 1 - 0.00000025 * (MWT_REAL) (data->PARTDP_PT_PoaOnMin * data->PARADP_PX_T3PhSmpNvt) ;
	//	data->PARADP_PX_3PhClRtHgh = 1 - 0.00000050 * (MWT_REAL) (data->PARTDP_PT_PoaOnMin * data->PARADP_PX_T3PhSmpNvt) ;
	//	data->PARADP_PX_3PhClRtLow = 0.00000050 * (MWT_REAL) (data->PARTDP_PT_PoaOnMin * data->PARADP_PX_T3PhSmpNvt) ;
	//	data->PARADP_PX_3PhClRtMin = 0.00000025 * (MWT_REAL) (data->PARTDP_PT_PoaOnMin * data->PARADP_PX_T3PhSmpNvt) ;
	//	data->PARADP_PT_PoaOfMin = 2 * data->PARTDP_PT_PrDdPoa + data->PARTDP_PT_PoaOnMin ;
	DspData.PX_3PhClRtHgh = 0.94;
	DspData.PX_3PhClRtLow = 0.06;

	DspData.PF_IRQBMax = 150000000.0 / 8.0;
	DspData.PF_3PhSg = 1350.0;
	DspData.L_3PhRndEn = FALSE; //TRUE
	DspData.PX_3PhRndMax = 0.0345; //0.0345

	DspData.L_EnIPhClRms = FALSE;

	if (SIMULATION) {
	} else {
		Uint16 i;
		for (i = 0; i < sizeof(U3PhRe); i++) {
			*((Uint16*) &U3PhRe + i) = 0;
		}
		for (i = 0; i < sizeof(U3PhIm); i++) {
			*((Uint16*) &U3PhIm + i) = 0;
		}
	}

	DspData.XX_PwmPdVv = floor(1.0 / 1350.0 / 2.0 * DspData.PF_IRQBMax);
	DspData.XT_Tsc = DspData.XX_PwmPdVv / DspData.PF_IRQBMax; //开关频率1350Hz，波峰波谷双采样
	DspData.XX_DutyA = 0.5;
	DspData.XX_DutyB = 0.5;
	DspData.XX_DutyC = 0.5;
	DspData.XX_Mode = 0;

	//-------------------//
	//
	//
	//----------------------//
	/*CvOpSaSq 4ms*/
	DspData.PU_3PhIdlCmp = 10.0;
	DspData.PU_3PhActCmp = 30.0;

	/*CvOpSoSq 4ms*/

	/*CvOpSa*/
	DspData.L_PrlAcm = TRUE;

	/*UF3PhCmp 4ms*/
	DspData.L_EnUF3PhCmp = TRUE;	//TRUE
	DspData.PI_UF3PhCmpActHiLo = 4000.0;
	DspData.PF_UF3PhCmpActHiLo = -10.0;
	DspData.PI_UF3PhCmpRctHiLo = 4000.0;
	DspData.PU_UF3PhCmpRctHiLo = -100.0;

	/*IPhClGenOvLd 4ms*/

	/*IPhClPsTrs 4ms*/
	DspData.PX_IPhClTrsKpAct = 0.005;
	DspData.PX_IPhClTrsKpRct = 0.03;
	DspData.PX_IPhClTrsKpAbs = 0.0;

	/*F3PhRef 4ms*/

	/*U3PhRef*/
	DspData.PF_U3PhRef2 = 6.0;
	DspData.PF_U3PhRef3 = 50.0;
	DspData.PU_U3PhRef1 = 0.0; //0Hz
	DspData.PU_U3PhRef2 = 0.0;  //6Hz
	DspData.PU_U3PhRef3 = 380.0 * SQRT2bySQRT3;  //50Hz 相电压峰值
	DspData.PU_U3PhRef4 = 380.0 * SQRT2bySQRT3; //100Hz
	DspData.L_ExtU3PhRef = FALSE;
	DspData.PX_ExtU3PhRefRmp = 200.0;
	DspData.L_EnRmpU3PhRef = FALSE;
	DspData.PX_U3PhRefRmp1 = 200.0;
	DspData.PX_U3PhRefRmp2 = 50.0;
	DspData.PX_U3PhRefRmpSel = 0.9;

	/*U3PhCl 4ms*/
	DspData.L_En3PhCl = TRUE; //TRUE
	DspData.L_EnU3PhOpLoCl = FALSE;
	DspData.PX_KpU3PhCl = 0.8;
	DspData.PT_U3PhCl = 50.0; //ms
	DspData.PU_3PhClMax = 75.0;
	DspData.PU_3PhClMin = -50.0;
	DspData.PU_3PhClRefMax = 395.0 * SQRT2bySQRT3;
	DspData.PU_3PhClRefMin = 0.0;
	DspData.PX_TrfRtPr3Ph = 1.684;

	/*TFrefRmp 16ms*/
	DspData.PX_FRefRmpUpSlaveAcm = 100.0;
	if (SIMULATION) {
		DspData.PX_FRefRmpUp = 400.0;
		DspData.PX_FRefRmpDo1 = 400.0;
		DspData.PX_FRefRmpDo2 = 400.0;
		DspData.PX_FRefRmpDo3 = 400.0;
	} else {
		DspData.PX_FRefRmpUp = 40.0;
		DspData.PX_FRefRmpDo1 = 40.0;
		DspData.PX_FRefRmpDo2 = 40.0;
		DspData.PX_FRefRmpDo3 = 40.0;
	}

	DspData.PF_FRefRmpDo12 = 4.0;
	DspData.PF_FRefRmpDo23 = 30.0;

	/*FrefUDcLk 16ms*/
	DspData.PF_UDcLkMin = 50.0;	//	50
	DspData.PU_DcLkFRefMin = 1000.0;	//	1000
	DspData.PU_DcLkFRefLow = 1000.;	//	1000
	DspData.PX_FRefRmpUDcLkUp = 1000.0;	//	40
	DspData.PX_FRefRmpUDcLkDo = 1000.0;	//	40
	DspData.PT_FRefUDcLk = 100;	//100ms

	/*FrefRmp 16ms*/
	DspData.PF_3PhNom = 50.0;
	DspData.PF_3PhMin = 3.0;

	/*F3PhSz 16ms*/
	DspData.PX_KpF3PhSzCl = 0.5;	//0.5
	DspData.PT_F3PhSzCl = 160.0; //800ms
	DspData.PF_UF3PhSzClMaxMin = 50.0;
	DspData.PT_UF3PhSzRmp = 1000.0; //ms

	/*U3PhSz 16ms*/
	DspData.PU_UF3PhSzClAdd = 0.0; //同步幅值补偿
	DspData.PU_UF3PhSzClMaxMin = 100.0;

	/*UF3PhSz 16ms*/
	DspData.PF_UF3PhSzRdy = 0.3;
	DspData.PU_UF3PhSzRdy = 20.0 * SQRT2bySQRT3;

	if (SIMULATION) {
		DspData.PT_UF3PhSzRdy = 250.0; //250ms
		DspData.PT_UF3PhSzFl = 500.0; //5000ms

	} else {
		DspData.PT_UF3PhSzRdy = 10000.0; //250ms
		DspData.PT_UF3PhSzFl = 5000.0; //5000ms
	}

	/**/
	if (SIMULATION) {
	} else {
		Uint16 i;
		for (i = 0; i < sizeof(PI_U3PhCl); i++) {
			*((Uint16*) &PI_U3PhCl + i) = 0;
		}
	}
}

/*
 * start/stop operation
 * B_EnCv  B_En2qc
 * A_CvOp A_2qcOp
 * 200us
 *
 * */
void SRTO_C(void) {

	if (DspData.C_CvOpSaDsp) {
		DspData.B_EnCv = TRUE;
	} else {
		DspData.B_EnCv = FALSE;
	}

//	if (EnCv) {
//		DspData.A_CvOp = TRUE;
//	} else {
//		DspData.A_CvOp = FALSE;
//	}
}

//复数运算
void SIPR_B(void) {

	/*
	 * clark变换
	 * */
	DspData.XI_PhAB = PH3TOCPLX(DspData.XI_PhA, DspData.XI_PhB, DspData.XI_PhC);
	LowPass(&DspData.XI_PhReFix, DspData.XI_PhAB.re,
			DspData.XT_Tsc * DspData.PN_IPhFixMcu_Flt / 2.0);
	LowPass(&DspData.XI_PhImFix, DspData.XI_PhAB.im,
			DspData.XT_Tsc * DspData.PN_IPhFixMcu_Flt / 2.0);

	cfloat32 XS_3Ph;
	XS_3Ph = CPLXSCA(CPLXMULT(DspData.WU_3PhAB, CPLXCONJ(DspData.XI_PhAB)),
			1.5);
	DspData.XP_3Ph = XS_3Ph.re;
	DspData.XQ_3Ph = XS_3Ph.im;

	/*park变换*/
	DspData.XI_PhDQ = CPLXMULT(DspData.XI_PhAB,
			POL2CPLX(1.0, -DspData.WX_Theta));
	/**/
	DspData.XI_PhAct = DspData.XI_PhDQ.re;
	DspData.XI_PhRct = DspData.XI_PhDQ.im;

	/*********************************************
	 *
	 *
	 *******************************************/
	/*IIR Notch Filter*/
	U3PhRe.In = 2.0 * DspData.XU_PhABLk
			* cos(DspData.WX_Theta + DspData.PD_ThetaFiOs);
	AdaptIIRNotchFilter(&U3PhRe, 2.0 * PI2 * Max(DspData.WF_3PhDsp, 1.0),
			DspData.XT_Tsc);

	U3PhIm.In = 2.0 * DspData.XU_PhABLk
			* sin(DspData.WX_Theta + DspData.PD_ThetaFiOs);
	AdaptIIRNotchFilter(&U3PhIm, 2.0 * PI2 * Max(DspData.WF_3PhDsp, 1.0),
			DspData.XT_Tsc);

	DspData.XU_3PhRe = U3PhRe.Out;
	DspData.XU_3PhIm = U3PhIm.Out;

	DspData.WX_Theta += 2.0 * PI * DspData.WF_3PhDsp * DspData.XT_Tsc;
	DspData.WX_Theta = fmod(DspData.WX_Theta, 2 * PI);

	/*XF_U3Ph*/

	/**/
	DspData.XU_3PhAbs = sqrt(
			DspData.XU_3PhRe * DspData.XU_3PhRe
					+ DspData.XU_3PhIm * DspData.XU_3PhIm);
	/**/
	LowPass(&DspData.XU_3PhSqu, DspData.XU_PhABLk * DspData.XU_PhABLk,
			DspData.XT_Tsc * DspData.PN_U3PhRms_Flt);
	DspData.XU_3PhRms = sqrt(DspData.XU_3PhSqu);

	/**/
	LowPass(&DspData.XU_DcLkFlt, DspData.XU_DcLk,
			DspData.XT_Tsc * DspData.PN_UDcLk_Flt);
	LowPass(&DspData.WU_3PhAbs_Flt, DspData.WU_3PhAbs,
			DspData.XT_Tsc * DspData.PN_URef_Flt);
	LowPass(&DspData.XI_PhAct_Flt, DspData.XI_PhAct,
			DspData.XT_Tsc * DspData.PN_IPhActRct_Flt);
	LowPass(&DspData.XI_PhRct_Flt, DspData.XI_PhRct,
			DspData.XT_Tsc * DspData.PN_IPhActRct_Flt);
	LowPass(&DspData.XI_PhAct_Flt2, DspData.XI_PhAct,
			DspData.XT_Tsc * DspData.PN_IPhActRctMcu_Flt);
	LowPass(&DspData.XI_PhRct_Flt2, DspData.XI_PhRct,
			DspData.XT_Tsc * DspData.PN_IPhActRctMcu_Flt);
	LowPass(&DspData.XI_PhAbs_Flt, DspData.XI_PhAbs,
			DspData.XT_Tsc * DspData.PN_IPhAbs_Flt);
	LowPass(&DspData.XP_3Ph_Flt, DspData.XP_3Ph,
			DspData.XT_Tsc * DspData.PN_PQ3PhMcu_Flt);
	LowPass(&DspData.XQ_3Ph_Flt, DspData.XQ_3Ph,
			DspData.XT_Tsc * DspData.PN_PQ3PhMcu_Flt);
	CplxLowPass(&DspData.XI_PhDQ_Flt, DspData.XI_PhDQ,
			DspData.XT_Tsc * DspData.PN_IPhDQ_Flt);
}

//电流瞬态保护，降电压幅值
void ACCL_B(void) {

	float32 a, b, c;

	a = Min(DspData.PI_PhClTrsAbsLim - DspData.XI_PhAbs, 0.0)
			* DspData.XX_IPhClTrsKpAbsDsp;
	b = Min(DspData.WI_PhActDsp - DspData.XI_PhAct_Flt, 0.0)
			* DspData.XX_IPhClTrsKpActDsp;
	c = Min(DspData.WI_PhRctDsp - DspData.XI_PhRct_Flt, 0.0)
			* DspData.XX_IPhClTrsKpRctDsp;

	/**/
	DspData.WU_IPhClTrs = Max(-DspData.PU_PhClTrsMax, a + b + c);
	/**/
	if (DspData.WU_IPhClTrs < 0) {
		DspData.S_IPhClTrsAv = 1;
	} else {
		DspData.S_IPhClTrsAv = 0;
	}
	/**/
	LowPass(&DspData.WU_IPhClTrs_Flt, DspData.WU_IPhClTrs,
			DspData.XT_Tsc * DspData.PN_URefIPhClTrs_Flt);
}

//电压频率控制
void UFCO_B(void) {

	DspData.WU_3PhSec = POL2CPLX(DspData.WU_3PhDsp, 0.0); //静止坐标系按1次侧，同步频率按WF_3PhDsp  DQ

	DspData.PZ_3PhFiNd = FRAC2CPLX(DspData.PZ_3PhFiNdRe,
			DspData.PZ_3PhFiNdIm / 50.0 * DspData.WF_3PhDsp);
	DspData.PZ_3PhFiCa = FRAC2CPLX(0.0,
			DspData.PZ_3PhFiCaIm / 50.0 * DspData.WF_3PhDsp);
	DspData.PZ_3PhTf = FRAC2CPLX(DspData.PZ_3PhTfRe,
			DspData.PZ_3PhTfIm / 50.0 * DspData.WF_3PhDsp);

	cfloat32 Z1, Z2;
	Z1 = CPLXDIV(DspData.PZ_3PhFiCa,
			CPLXADD(DspData.PZ_3PhFiCa, DspData.PZ_3PhTf));
	Z2 = CPLXADD(DspData.PZ_3PhFiNd, CPLXMULT(DspData.PZ_3PhTf, Z1));

	/**/
	DspData.WU_3PhPm = CPLXADD(CPLXMULT(DspData.WU_3PhSec, Z1),
			CPLXMULT(DspData.XI_PhDQ_Flt, Z2));
	//B_EnBuiTs
	//		DspData.WU_3PhPm = DspData.WU_3PhSec;	//DQ
	/*
	 * ipark变换
	 * */
	DspData.WU_3PhPmAB = CPLXMULT(DspData.WU_3PhPm,
			POL2CPLX(1.0, DspData.WX_Theta)); //ipark
	/*
	 * 电流直流分量控制
	 * WU_IPhDcClRe WU_IPhDcClIm
	 * */

	/**/
	CPLX2POL(&DspData.WU_Ref_Abs, &DspData.WX_ThetaCv, DspData.WU_3PhPmAB);

	/******************************************************************
	 * 直流母线电压振荡抑制
	 *
	 *
	 *
	 *
	 *****************************************************************/
	LowPass(&DspData.XU_DcLkStbFltSli, DspData.XU_DcLk,
			DspData.XT_Tsc * DspData.PN_UDcLkStbSliSmt);
	LowPass(&DspData.XU_DcLkStbFltHev, DspData.XU_DcLk,
			DspData.XT_Tsc * DspData.PN_UDcLkStbHevSmt);
	DspData.WU_DcLkStb = Limit(
			DspData.PX_KpUDcLkStb
					* (pow(DspData.XU_DcLkStbFltSli / DspData.XU_DcLkStbFltHev,
							2.0) - 1.0), -DspData.PU_DcLkStbMaxMin,
			DspData.PU_DcLkStbMaxMin);

	/**/
	DspData.WU_Ref_Abs = DspData.WU_Ref_Abs + DspData.WU_IPhClTrs
			+ DspData.WU_DcLkStb;
	DspData.WU_Ref_Abs = Max(0.0, DspData.WU_Ref_Abs);

	DspData.XX_MRef = DspData.WU_Ref_Abs / Max(1.0, DspData.XU_DcLk);
	if (DspData.A_CvOp && (DspData.XX_MRef > ONEbySQRT3)) {
		DspData.S_3PhOvMd = 1;
	} else {
		DspData.S_3PhOvMd = 0;
	}

	DspData.WU_OvMd = DspData.XU_DcLk * Min(0.6057 - DspData.XX_MRef, 0); //<0
	//
	DspData.WU_3PhAbsOvMd = DspData.XU_DcLk * OvMd(DspData.XX_MRef);

	DspData.WU_IPhClRmsRed = 0;

	DspData.WU_3PhAbs = DspData.WU_3PhAbsOvMd + DspData.WU_IPhClRmsRed;
	DspData.WU_3PhAB = POL2CPLX(DspData.WU_3PhAbs, DspData.WX_ThetaCv);

	//
	SVPWM(&DspData.XX_CrU, &DspData.XX_CrV, &DspData.XX_CrW,
			DspData.WU_3PhAB.re / DspData.XU_DcLk,
			DspData.WU_3PhAB.im / DspData.XU_DcLk);

	DspData.XX_Mode = !DspData.XX_Mode;

	//-----------------------//
	//	DdCmp();
	//
	//-----------------------//

}

void PPG3_B(void) {

	/***************/
	if (Max(DspData.XX_CrU, Max(DspData.XX_CrV, DspData.XX_CrW))
			> DspData.PX_3PhClRtHgh) {
		DspData.S_UDcLkLow = 1;
	} else {
		DspData.S_UDcLkLow = 0;
	}

	/*
	 * 随机开关频率降噪
	 *
	 * */
	if (!DspData.L_3PhRndEn) {
		DspData.XT_Tsc = 0.5 / DspData.PF_3PhSg; //开关频率1350Hz，波峰波谷双采样
	} else {

	}
	/**/
	DspData.XX_PwmPdVv = DspData.XT_Tsc * DspData.PF_IRQBMax + 0.5;

	/*
	 * 最小脉宽限制
	 * */
	DspData.XX_DutyA = Limit(DspData.XX_CrU, DspData.PX_3PhClRtLow,
			DspData.PX_3PhClRtHgh);
	DspData.XX_DutyB = Limit(DspData.XX_CrV, DspData.PX_3PhClRtLow,
			DspData.PX_3PhClRtHgh);
	DspData.XX_DutyC = Limit(DspData.XX_CrW, DspData.PX_3PhClRtLow,
			DspData.PX_3PhClRtHgh);

	if (!DspData.A_CvOp) {
		DspData.XX_Mode = 2;
		DspData.XX_DutyA = 0.5;
		DspData.XX_DutyB = 0.5;
		DspData.XX_DutyC = 0.5;
	} else {

	}
}

/*
 * 死区补偿
 * */
void DdCmp(void) {
	/*
	 * 电流小于零时从上管续流，下管为可控管，电压增加
	 * 电流大于零时从下管续流，上管为可控管，电压减小
	 * ***************/
	if (DspData.XX_Mode) {
		float32 coff;
		if (DspData.XI_PhA <= 0) {

			if (fabs(DspData.XI_PhA) < 10.0)
				coff = 0.0;
			else if (fabs(DspData.XI_PhA) < 50.0)
				coff = (fabs(DspData.XI_PhA) - 10.0) / 40.0;
			else
				coff = 1.0;

			DspData.XX_CrU -= 0.00001 / DspData.XT_Tsc * coff;
		}
		if (DspData.XI_PhB <= 0) {

			if (fabs(DspData.XI_PhB) < 10.0)
				coff = 0.0;
			else if (fabs(DspData.XI_PhB) < 50.0)
				coff = (fabs(DspData.XI_PhB) - 10.0) / 40.0;
			else
				coff = 1.0;

			DspData.XX_CrV -= 0.00001 / DspData.XT_Tsc * coff;
		}
		if (DspData.XI_PhC <= 0) {

			if (fabs(DspData.XI_PhC) < 10.0)
				coff = 0.0;
			else if (fabs(DspData.XI_PhC) < 50.0)
				coff = (fabs(DspData.XI_PhC) - 10.0) / 40.0;
			else
				coff = 1.0;

			DspData.XX_CrW -= 0.00001 / DspData.XT_Tsc * coff;
		}

	} else {
		float32 coff;
		if (DspData.XI_PhA >= 0) {

			if (fabs(DspData.XI_PhA) < 10.0)
				coff = 0.0;
			else if (fabs(DspData.XI_PhA) < 50.0)
				coff = (fabs(DspData.XI_PhA) - 10.0) / 40.0;
			else
				coff = 1.0;

			DspData.XX_CrU += 0.00001 / DspData.XT_Tsc * coff;
		}
		if (DspData.XI_PhB >= 0) {

			if (fabs(DspData.XI_PhB) < 10.0)
				coff = 0.0;
			else if (fabs(DspData.XI_PhB) < 50.0)
				coff = (fabs(DspData.XI_PhB) - 10.0) / 40.0;
			else
				coff = 1.0;

			DspData.XX_CrV += 0.00001 / DspData.XT_Tsc * coff;
		}
		if (DspData.XI_PhC >= 0) {

			if (fabs(DspData.XI_PhC) < 10.0)
				coff = 0.0;
			else if (fabs(DspData.XI_PhC) < 50.0)
				coff = (fabs(DspData.XI_PhC) - 10.0) / 40.0;
			else
				coff = 1.0;

			DspData.XX_CrW += 0.00001 / DspData.XT_Tsc * coff;
		}
	}

}

/*
 * DSP中1ms任务
 * */
//稳态电流保护
void ACCL_T2(void) {
	RmsClc(&DspData.XI_Ph1Rms, DspData.XI_PhA, 50, &DspData.XI_Ph1Squ,
			&DspData.XX_CntPh1Rms);
	RmsClc(&DspData.XI_Ph2Rms, DspData.XI_PhB, 50, &DspData.XI_Ph2Squ,
			&DspData.XX_CntPh2Rms);
	RmsClc(&DspData.XI_Ph3Rms, DspData.XI_PhC, 50, &DspData.XI_Ph3Squ,
			&DspData.XX_CntPh3Rms);

	LowPass(&DspData.XI_Ph1Rms_Flt, DspData.XI_Ph1Rms,
			0.001 * DspData.PN_IPhRms_Flt);
	LowPass(&DspData.XI_Ph2Rms_Flt, DspData.XI_Ph2Rms,
			0.001 * DspData.PN_IPhRms_Flt);
	LowPass(&DspData.XI_Ph3Rms_Flt, DspData.XI_Ph3Rms,
			0.001 * DspData.PN_IPhRms_Flt);

	DspData.WU_IPhClRms = 0.0;
	DspData.B_LimAct = 0;

	if (DspData.L_EnIPhClRms) //功能未开启
	{

	}
}

/****************************************************
 *MCU程序
 *
 *****************************************************/

void TFrefRmp(void);
void FrefRmp(void);

void FrefUDcLk(void);

void IPhClGenOvLd(void);

void F3PhRef(void);
void U3PhRef(void);

void U3PhCl(void);

void F3PhSz(void);
void U3PhSz(void);
void UF3PhSz(void);

void UF3PhCmp(void);

void IPhClPsTrs(void);

/*16ms*/
void TFrefRmp(void) {
	if (DspData.WF_3PhDsp < DspData.PF_3PhMin)
		DspData.XX_FRefRmpUp = 1000.0;
	else
		DspData.XX_FRefRmpUp = DspData.PX_FRefRmpUp;
	/**/
	if (DspData.WF_3PhDsp < DspData.PF_FRefRmpDo12)
		DspData.XX_FRefRmpDo = DspData.PX_FRefRmpDo1;
	else if (DspData.WF_3PhDsp < DspData.PF_FRefRmpDo23)
		DspData.XX_FRefRmpDo = DspData.PX_FRefRmpDo2;
	else
		DspData.XX_FRefRmpDo = DspData.PX_FRefRmpDo3;
}

/*
 * MCU中16ms任务
 * */
void FrefRmp(void) {
	if (DspData.A_CvOp) {
		RAMP2(&DspData.WF_3PhRmp, DspData.PF_3PhNom,
				DspData.XX_FRefRmpUp * 0.016, -DspData.XX_FRefRmpDo * 0.016,
				0.0, FALSE, FALSE);

	} else {
		RAMP2(&DspData.WF_3PhRmp, DspData.PF_3PhMin,
				DspData.XX_FRefRmpUp * 0.016, -DspData.XX_FRefRmpDo * 0.016,
				0.0, FALSE, FALSE);
	}

	DspData.A_FNom = (DspData.WF_3PhRmp == DspData.PF_3PhNom);
}

/*16ms*/
void FrefUDcLk(void) {
	LowPass(&DspData.XU_DcLkFlt2, DspData.XU_DcLkFlt,
			16.0 / DspData.PT_FRefUDcLk);
	float32 v01;
	v01 = FKG4(DspData.XU_DcLkFlt2, 0.0, DspData.PF_3PhMin,
			DspData.PU_DcLkFRefMin, DspData.PF_3PhMin, DspData.PU_DcLkFRefLow,
			DspData.PF_3PhNom, 10000.0, DspData.PF_3PhNom);
	RAMP2(&DspData.WF_3PhUDcLk, v01, DspData.PX_FRefRmpUDcLkUp * 0.016,
			DspData.PX_FRefRmpUDcLkDo * 0.016, 0.0, FALSE, FALSE);
}

/*4ms*/
void IPhClGenOvLd(void) {
	DspData.WF_IPhCl = 0.0;
}

/*4ms*/
void F3PhRef(void) {
	DspData.WF_3PhU3PhRef = Min(DspData.WF_3PhRmp, DspData.WF_3PhUDcLk)
			+ DspData.WF_IPhCl + DspData.WF_UF3PhSz;
	DspData.WF_3PhDsp = DspData.WF_3PhU3PhRef + DspData.WF_UF3PhCmp;
}

/*4ms*/
void U3PhRef(void) {
	if (!DspData.L_ExtU3PhRef) {
		DspData.WU_3PhU3PhRef = FKG4(DspData.WF_3PhU3PhRef, 0.0,
				DspData.PU_U3PhRef1, DspData.PF_U3PhRef2, DspData.PU_U3PhRef2,
				DspData.PF_U3PhRef3, DspData.PU_U3PhRef3, 100.0,
				DspData.PU_U3PhRef4);
	} else {

	}

	if (!DspData.L_EnRmpU3PhRef) {
		DspData.WU_3PhRmp = DspData.WU_3PhU3PhRef;
	} else {

	}
}

/*4ms*/
void U3PhCl(void) {
	//二次侧，相电压，峰值
	DspData.WU_3PhClIn = DspData.WU_3PhRmp + DspData.WU_UF3PhCmp
			+ DspData.WU_UF3PhSz;
	DspData.WU_3PhClIn = Limit(DspData.WU_3PhClIn, DspData.PU_3PhClRefMin,
			DspData.PU_3PhClRefMax);

	PI_U3PhCl.Ref = DspData.WU_3PhClIn
			+ (DspData.WU_IPhClTrs_Flt + DspData.WU_OvMd
					+ DspData.WU_IPhClRmsRed) / DspData.PX_TrfRtPr3Ph;
	PI_U3PhCl.Fbk = DspData.XU_3PhAbs * ONEbySQRT3;

	if ((!DspData.B_EnU3PhCl) || DspData.B_EnU3PhOpLoCl) {
		PI_U3PhCl.i1 = 0.0;
		PI_U3PhCl.v1 = 0.0;
		PI_U3PhCl.Out = 0.0;
	} else if ((PI_U3PhCl.Ref > PI_U3PhCl.Fbk) && DspData.S_UDcLkLow) {
		PI_U3PhCl.Out = PI_U3PhCl.Out;
	} else {
		float32 ratio = DspData.WF_3PhDsp / Max(1.0, DspData.PF_3PhNom);
		PI_U3PhCl.Kp = DspData.PX_KpU3PhCl * ratio;
		PI_U3PhCl.Ki = PI_U3PhCl.Kp * 4.0 / DspData.PT_U3PhCl; //TN_TZ 控制周期的倍率，推荐大于10  PI_U3PhCl.Kp *Ts*1000/ DspData.PT_U3PhCl; 4ms/50ms
		PI_U3PhCl.Umax = DspData.PU_3PhClMax * ratio;
		PI_U3PhCl.Umin = DspData.PU_3PhClMin;
		PI_CONTROLLER(&PI_U3PhCl);
	}

	DspData.WU_U3PhClOut = PI_U3PhCl.Out;
	DspData.WU_3PhDsp = DspData.WU_3PhClIn * DspData.PX_TrfRtPr3Ph
			+ DspData.WU_U3PhClOut;
}

/*
 * 16ms
 * */
void F3PhSz(void) {

	static Uint16 v01 = 0;
	static Uint16 sr1 = 0;
	static Uint16 rs1 = 0;
	static Uint16 ftrig1 = 0;
	static Uint16 rtrig1 = 0;
	static float32 Init = 0.0;
	static Uint16 Yi = 0;

	float32 value;
	Uint16 rtrig1Q, Set;

	SR(&sr1, DspData.C_AuSz, v01);
	RS(&rs1, FTRIG(DspData.C_AuSz, &ftrig1), v01);
	rtrig1Q = RTRIG(DspData.C_AuSz, &rtrig1);

	if (rtrig1Q) {
//		value = Limit(DspData.XF_U3Ph - DspData.PF_3PhNom, -5.0, 5.0); //开始同步
		value = 5.0;
	} else {
		value = DspData.WF_UF3PhSz; //同步过程中
	}

	RAMP(&Init, 0.0, 16.0 / DspData.PT_UF3PhSzRmp, 16.0 / DspData.PT_UF3PhSzRmp,
			value, !rs1, FALSE, value);

	Set = rtrig1Q || rs1;

	DspData.WF_UF3PhSzErr = Limit(
			atan2(DspData.XU_3PhIm, Max(1.0, DspData.XU_3PhRe)), -PI / 2.0,
			PI / 2.0);

	PIREG(0.0, DspData.WF_UF3PhSzErr, DspData.PX_KpF3PhSzCl,
			16.0 / DspData.PT_F3PhSzCl, Init, Set, !sr1,
			DspData.PF_UF3PhSzClMaxMin, -DspData.PF_UF3PhSzClMaxMin,
			&DspData.WF_UF3PhSz, &Yi);

	v01 = (fabs(DspData.WF_UF3PhSz) < 0.005);
}

/*
 * 16ms
 * */
void U3PhSz(void) {
	DspData.WU_UF3PhSzErr = DspData.XU_3PhAbs * ONEbySQRT3
			* DspData.PX_TrfRtPr3Ph + DspData.PU_UF3PhSzClAdd
			- DspData.WU_3PhDsp;

	static float32 Init = 0.0;
	static Uint16 sr1 = 0;
	static Uint16 rs1 = 0;
	static Uint16 ftrig1 = 0;
	static Uint16 rtrig1 = 0;
	static Uint16 v01 = 0;

	float32 value;
	Uint16 rtrig1Q, Set;

	SR(&sr1, DspData.C_AuSz, v01);
	RS(&rs1, FTRIG(DspData.C_AuSz, &ftrig1), v01);
	rtrig1Q = RTRIG(DspData.C_AuSz, &rtrig1);

	Set = (!sr1) || rs1 || rtrig1Q;

	if (!sr1) {
		value = 0.0; //正在同步
	} else {
		if (rtrig1Q) {
			value = DspData.WU_UF3PhSzErr; //开始同步
		} else {
			value = DspData.WU_UF3PhSz; //同步过程中
		}
	}

	RAMP(&Init, 0.0, 16.0 / DspData.PT_UF3PhSzRmp, 16.0 / DspData.PT_UF3PhSzRmp,
			value, !rs1, FALSE, value);

	INTEGR(&DspData.WU_UF3PhSz, DspData.WU_UF3PhSzErr, 16.0 / 200.0, Init,
			DspData.PU_UF3PhSzClMaxMin, -DspData.PU_UF3PhSzClMaxMin, Set,
			FALSE);

	v01 = (fabs(DspData.WU_UF3PhSz) < 0.001);

}

/*
 * 16ms
 * */
void UF3PhSz(void) {

	static TYPE_DLYONOFF_T TON1 = DLYONOFF_DEFAULTS;
	static TYPE_DLYONOFF_T TOF1 = DLYONOFF_DEFAULTS;
	static TYPE_DLYONOFF_T TON2 = DLYONOFF_DEFAULTS;

	Uint16 logic;

	logic = DspData.C_AuSz
			&& (fabs(DspData.WF_UF3PhSzErr) <= DspData.PF_UF3PhSzRdy)
			&& (fabs(DspData.WU_UF3PhSzErr) <= DspData.PU_UF3PhSzRdy);

	DspData.A_AuSz = DLYON_T(logic, DspData.PT_UF3PhSzRdy, &TON2, 16.0);

	logic = DLYON_T(DspData.C_AuSz, DspData.PT_UF3PhSzFl, &TON1, 16.0)
			&& (!DspData.A_AuSz);
	DspData.B_RqAuSzPrBc = DLYOFF_T(logic, 140.0, &TOF1, 16.0);
}

/*
 * 4ms
 * */
void UF3PhCmp(void) {
	if (DspData.L_EnUF3PhCmp) {
		if (DspData.XI_PhAct_Flt2 < -DspData.PI_UF3PhCmpActHiLo)
			DspData.WF_UF3PhCmp = -DspData.PF_UF3PhCmpActHiLo;
		else if (DspData.XI_PhAct_Flt2 < DspData.PI_UF3PhCmpActHiLo)
			DspData.WF_UF3PhCmp = DspData.PF_UF3PhCmpActHiLo
					/ DspData.PI_UF3PhCmpActHiLo * DspData.XI_PhAct_Flt2;
		else
			DspData.WF_UF3PhCmp = DspData.PF_UF3PhCmpActHiLo;

		if (DspData.XI_PhRct_Flt2 < -DspData.PI_UF3PhCmpRctHiLo)
			DspData.WU_UF3PhCmp = -DspData.PU_UF3PhCmpRctHiLo;
		else if (DspData.XI_PhRct_Flt2 < DspData.PI_UF3PhCmpRctHiLo)
			DspData.WU_UF3PhCmp = DspData.PU_UF3PhCmpRctHiLo
					/ DspData.PI_UF3PhCmpRctHiLo * DspData.XI_PhRct_Flt2;
		else
			DspData.WU_UF3PhCmp = DspData.PU_UF3PhCmpRctHiLo;
	} else {
		DspData.WF_UF3PhCmp = 0.0;
		DspData.WU_UF3PhCmp = 0.0;
	}
}

/*4ms*/
void IPhClPsTrs(void) {
	DspData.WI_PhActDsp = 450;
	DspData.WI_PhRctDsp = 300;
}
