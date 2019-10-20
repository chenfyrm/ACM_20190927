/*
 * acm_dsp.c
 *
 *  Created on: 2019-9-30
 *      Author: 700363
 */
#include "math.h"

#include "UserDefs.h"
#include "UserMath.h"
#include "complex.h"
#include "control.h"

#include "acm_dsp.h"

volatile struct Dsp_Data DspData;

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

/*
 *
 *
 *
 * */
static cfloat32 XZ_3PhFiNd = {0,0};
static cfloat32 XZ_3PhFiCa = {0,0};
static cfloat32 XZ_3PhTf = {0,0};

void DspInit(void) {

	/*
	 *
	 * */
	DspData.XU_DcLk = 0.0;
	DspData.XI_PhA = 0.0;
	DspData.XI_PhB = 0.0;
	DspData.XI_PhC = 0.0;
	DspData.XU_PhABLk = 0.0;
	DspData.XU_Bt = 0.0;
	DspData.XI_Bt = 0.0;
	DspData.XI_BtCg = 0.0;

	DspData.XU_3PhRe = 0.0;
	DspData.XU_3PhIm = 0.0;
	DspData.XU_3PhAbs = 0.0;
	DspData.XU_3PhRms = 0.0;
	DspData.XI_PhAbs = 0.0;
	DspData.XI_PhAct = 0.0;
	DspData.XI_PhRct = 0.0;
	DspData.XP_3Ph = 0.0;
	DspData.XQ_3Ph = 0.0;
	DspData.WX_Theta = 0.0;
	DspData.XT_U3Ph = 0.0;
	DspData.XU_BtFlt = 0.0;
	DspData.XI_BtFlt = 0.0;
	DspData.XI_BtCgFlt = 0.0;
	DspData.XI_BtCg2Flt = 0.0;
	DspData.XU_DcLk1Flt = 0.0;
	DspData.WU_3PhAbs_Flt = 0.0;
	DspData.XI_PhAct_Flt = 0.0;
	DspData.XI_PhRct_Flt = 0.0;
	DspData.XI_PhAct_Flt2 = 0.0;
	DspData.XI_PhRct_Flt2 = 0.0;
	DspData.XI_PhAbs_Flt = 0.0;
	DspData.XP_3Ph_Flt = 0.0;
	DspData.XQ_3Ph_Flt = 0.0;

	DspData.S_IPhClTrsAv = 0;
	DspData.WU_IPhClTrs = 0.0;
	DspData.WU_IPhClTrs_Flt = 0.0;
	DspData.B_LimAct = 0;
	DspData.WU_IPhClRms = 0.0;
	DspData.XI_Ph1Rms = 0.0;
	DspData.XI_Ph2Rms = 0.0;
	DspData.XI_Ph3Rms = 0.0;
	DspData.XI_Ph1Rms_Flt = 0.0;
	DspData.XI_Ph2Rms_Flt = 0.0;
	DspData.XI_Ph3Rms_Flt = 0.0;

	DspData.S_3PhOvMd = 0;
	DspData.S_UDcLkLow = 0;
	DspData.WX_ThetaCv = 0.0;
	DspData.XU_DcLkStbFltSli = 0.0;
	DspData.XU_DcLkStbFltHev = 0.0;
	DspData.WU_DcLkStb = 0.0;
	DspData.WU_Ref_Abs = 0.0;
	DspData.XX_MRef = 0.0;
	DspData.WU_OvMd = 0.0;
	DspData.WU_3PhAbsOvMd = 0.0;
	DspData.WU_IPhClRmsRed = 0.0;
	DspData.WU_3PhAbs = 0.0;
	DspData.XX_CrU = 0.0;
	DspData.XX_CrV = 0.0;
	DspData.XX_CrW = 0.0;

	DspData.XT_Tsc = 0.001; //开关频率1350Hz，波峰波谷双采样
	DspData.XX_DutyA = 0;
	DspData.XX_DutyB = 0;
	DspData.XX_DutyC = 0;
	DspData.XX_Mode = 0;

	DspData.B_EnCv = 0;
	DspData.S_Opto = 0;
	DspData.A_CvOp = 0;

	/*
	 *
	 * */
	DspData.XX_FRefRmpUp = 0.0;
	DspData.XX_FRefRmpDo = 0.0;

	DspData.A_FNom = 0;
	DspData.WF_3PhRmp = 0.0;

	DspData.XU_DcLkFlt2 = 0.0;
	DspData.WF_3PhUDcLk = 0.0;

	DspData.WF_IPhCl = 0.0;

	DspData.WF_3PhU3PhRef = 0.0;
	DspData.WF_3PhDsp = 0.0;

	DspData.WU_3PhU3PhRef = 0.0;
	DspData.WU_3PhRmp = 0.0;

	DspData.WU_3PhClIn = 0.0;
	DspData.WU_U3PhClOut = 0.0;
	DspData.WU_3PhDsp = 0.0;

	DspData.WF_UF3PhSzErr = 0.0;
	DspData.WF_UF3PhSz = 0.0;

	DspData.WU_UF3PhSzErr = 0.0;
	DspData.WU_UF3PhSz = 0.0;

	DspData.A_AuSz = 0;
	DspData.B_RqAuSzPrBc = 0.0;

	DspData.WF_UF3PhCmp = 0.0;
	DspData.WU_UF3PhCmp = 0.0;

	DspData.WI_PhActDsp = 0.0;
	DspData.WI_PhRctDsp = 0.0;
	DspData.XX_IPhClTrsKpActDsp = 0.0;
	DspData.XX_IPhClTrsKpRctDsp = 0.0;
	DspData.XX_IPhClTrsKpAbsDsp = 0.0;


	/*
	 *
	 *
	 * */
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

	DspData.PD_ThetaFiOs = PI / 3.0 - PI / 180.0;

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

	/*ppg3*/
	DspData.PX_3PhClRtHgh = 0.94;
	DspData.PX_3PhClRtLow = 0.06;

	DspData.PF_IRQBMax = 150000000.0 / 8.0;
	DspData.PF_3PhSg = 1350.0;
	DspData.L_3PhRndEn = FALSE; //TRUE
	DspData.PX_3PhRndMax = 0.0345; //0.0345

	DspData.L_EnIPhClRms = FALSE;

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
	DspData.L_EnUF3PhCmp = FALSE;	//TRUE
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
	DspData.L_EnRmpU3PhRef = FALSE;

	/*U3PhCl 4ms*/
	DspData.PX_KpU3PhCl = 0.8;
	DspData.PT_U3PhCl = 50.0; //ms
	DspData.PU_3PhClMax = 75.0;
	DspData.PU_3PhClMin = -50.0;
	DspData.PU_3PhClRefMax = 395.0 * SQRT2bySQRT3;
	DspData.PU_3PhClRefMin = 0.0;
	DspData.PX_TrfRtPr3Ph = 1.684;

	/*TFrefRmp 16ms*/
	DspData.PX_FRefRmpUp = 400.0;
	DspData.PX_FRefRmpDo1 = 400.0;
	DspData.PX_FRefRmpDo2 = 400.0;
	DspData.PX_FRefRmpDo3 = 400.0;
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
	DspData.PF_3PhNom = 50.3;
	DspData.PF_3PhMin = 3.0;

	/*F3PhSz 16ms*/
	DspData.PX_KpF3PhSzCl = 0.5;	//0.5
	DspData.PT_F3PhSzCl = 800.0; //800ms
	DspData.PF_UF3PhSzClMaxMin = 50.0;
	DspData.PT_UF3PhSzRmp = 1000.0; //ms

	/*U3PhSz 16ms*/
	DspData.PU_UF3PhSzClAdd = 0.0; //同步幅值补偿
	DspData.PU_UF3PhSzClMaxMin = 100.0;
	DspData.PT_U3PhSzCl = 200.0;

	/*UF3PhSz 16ms*/
	DspData.PF_UF3PhSzRdy = 0.3;
	DspData.PU_UF3PhSzRdy = 20.0 * SQRT2bySQRT3;
	DspData.PT_UF3PhSzRdy = 250.0; //250ms
	DspData.PT_UF3PhSzFl = 500.0; //5000ms

	/*
	 *
	 * */
	XZ_3PhFiNd = FRAC2CPLX(DspData.PZ_3PhFiNdRe,
			DspData.PZ_3PhFiNdIm / 50.0 * DspData.PF_3PhNom);
	XZ_3PhFiCa = FRAC2CPLX(0.0,
			DspData.PZ_3PhFiCaIm / 50.0 * DspData.PF_3PhNom);
	XZ_3PhTf = FRAC2CPLX(DspData.PZ_3PhTfRe,
			DspData.PZ_3PhTfIm / 50.0 * DspData.PF_3PhNom);
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

	if (DspData.S_Opto) {
		DspData.A_CvOp = TRUE;
	} else {
		DspData.A_CvOp = FALSE;
	}
}

/*
 *
 *
 * 复数运算
 *
 * */
static float32 XU_3PhSqu = 0.0;
static cfloat32 XS_3Ph = { 0, 0 };
static cfloat32 XI_PhAB = { 0, 0 };
static cfloat32 WU_3PhAB = {0,0};
static cfloat32 XI_PhDQ = { 0, 0 };
static cfloat32 XI_PhDQ_Flt = { 0, 0 };
static struct IIRFILTER_2ND U3PhRe = IIRFILTER_2ND_DEFAULTS;
static struct IIRFILTER_2ND U3PhIm = IIRFILTER_2ND_DEFAULTS;

void SIPR_B(void) {

	/*
	 * clark变换
	 * */
	XI_PhAB = PH3TOCPLX(DspData.XI_PhA, DspData.XI_PhB, DspData.XI_PhC);

	XS_3Ph = CPLXSCA(CPLXMULT(WU_3PhAB, CPLXCONJ(XI_PhAB)), 1.5);
	DspData.XP_3Ph = XS_3Ph.re;
	DspData.XQ_3Ph = XS_3Ph.im;

	/*park变换*/
	XI_PhDQ = CPLXMULT(XI_PhAB, POL2CPLX(1.0, -DspData.WX_Theta));
	/**/
	DspData.XI_PhAct = XI_PhDQ.re;
	DspData.XI_PhRct = XI_PhDQ.im;

	/*********************************************
	 *
	 *
	 *******************************************/
	/*IIR Notch Filter*/
	if (DspData.A_CvOp) {
		U3PhRe.In = 2.0 * DspData.XU_PhABLk * cos(DspData.WX_Theta);
		U3PhIm.In = 2.0 * DspData.XU_PhABLk * sin(DspData.WX_Theta);
	} else {
		U3PhRe.In = 0.0;
		U3PhIm.In = 0.0;
	}
	AdaptIIRNotchFilter(&U3PhRe, 2.0 * PI2 * Max(DspData.WF_3PhDsp, 1.0),
			DspData.XT_Tsc);
	AdaptIIRNotchFilter(&U3PhIm, 2.0 * PI2 * Max(DspData.WF_3PhDsp, 1.0),
			DspData.XT_Tsc);

	DspData.XU_3PhRe = U3PhRe.Out;
	DspData.XU_3PhIm = U3PhIm.Out;

	DspData.WX_Theta += 2.0 * PI * DspData.WF_3PhDsp * DspData.XT_Tsc;
	DspData.WX_Theta = fmod(DspData.WX_Theta, 2 * PI);

	/*XF_U3Ph*/
	if (!DspData.A_CvOp) {

	} else {

	}

	/**/
	DspData.XU_3PhAbs = sqrt(
			DspData.XU_3PhRe * DspData.XU_3PhRe
					+ DspData.XU_3PhIm * DspData.XU_3PhIm);
	/**/
	LowPass(&XU_3PhSqu, DspData.XU_PhABLk * DspData.XU_PhABLk,
			DspData.XT_Tsc * DspData.PN_U3PhRms_Flt);
	DspData.XU_3PhRms = sqrt(XU_3PhSqu);

	/**/
	LowPass(&DspData.XU_DcLk1Flt, DspData.XU_DcLk,
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
	CplxLowPass(&XI_PhDQ_Flt, XI_PhDQ, DspData.XT_Tsc * DspData.PN_IPhDQ_Flt);
}

/*
 * 电流瞬态保护，降电压幅值
 * */
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

/*
 * DSP中1ms任务
 *
 * 稳态电流限幅
 * */
static float32 XI_Ph1Squ = 0.0;
static float32 XI_Ph2Squ= 0.0;
static float32 XI_Ph3Squ= 0.0;
static Uint16 XX_CntPh1Rms=0;
static Uint16 XX_CntPh2Rms=0;
static Uint16 XX_CntPh3Rms=0;

void ACCL_T2(void) {
	RmsClc(&DspData.XI_Ph1Rms, DspData.XI_PhA, 50, &XI_Ph1Squ,
			&XX_CntPh1Rms);
	RmsClc(&DspData.XI_Ph2Rms, DspData.XI_PhB, 50, &XI_Ph2Squ,
			&XX_CntPh2Rms);
	RmsClc(&DspData.XI_Ph3Rms, DspData.XI_PhC, 50, &XI_Ph3Squ,
			&XX_CntPh3Rms);

	LowPass(&DspData.XI_Ph1Rms_Flt, DspData.XI_Ph1Rms,
			0.001 * DspData.PN_IPhRms_Flt);
	LowPass(&DspData.XI_Ph2Rms_Flt, DspData.XI_Ph2Rms,
			0.001 * DspData.PN_IPhRms_Flt);
	LowPass(&DspData.XI_Ph3Rms_Flt, DspData.XI_Ph3Rms,
			0.001 * DspData.PN_IPhRms_Flt);

	if (DspData.L_EnIPhClRms) //功能未开启
	{

	} else {
		DspData.WU_IPhClRms = 0.0;
		DspData.B_LimAct = 0;
	}
}

/*
 * 电压频率控制
 * */

static cfloat32 WU_3PhSec = {0,0};
static cfloat32 WU_3PhPm = {0,0};
static cfloat32 WU_3PhPmAB = {0,0};


void UFCO_B(void) {

	WU_3PhSec = POL2CPLX(DspData.WU_3PhDsp, -DspData.PD_ThetaFiOs); //静止坐标系按1次侧，同步频率按WF_3PhDsp  DQ

	cfloat32 Z1, Z2;
	Z1 = CPLXDIV(XZ_3PhFiCa,
			CPLXADD(XZ_3PhFiCa, XZ_3PhTf));
	Z2 = CPLXADD(XZ_3PhFiNd, CPLXMULT(XZ_3PhTf, Z1));

	/**/
	WU_3PhPm = CPLXADD(CPLXMULT(WU_3PhSec, Z1),
			CPLXMULT(XI_PhDQ_Flt, Z2));
	//B_EnBuiTs
//	DspData.WU_3PhPm = DspData.WU_3PhSec;	//DQ

	/*
	 * ipark变换
	 *
	 * */
	WU_3PhPmAB = CPLXMULT(WU_3PhPm,
			POL2CPLX(1.0, DspData.WX_Theta)); //ipark
	/*
	 * 电流直流分量控制
	 * WU_IPhDcClRe WU_IPhDcClIm
	 * */

	/**/
	CPLX2POL(&DspData.WU_Ref_Abs, &DspData.WX_ThetaCv, WU_3PhPmAB);

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
	WU_3PhAB = POL2CPLX(DspData.WU_3PhAbs, DspData.WX_ThetaCv);

	//
	SVPWM(&DspData.XX_CrU, &DspData.XX_CrV, &DspData.XX_CrW,
			WU_3PhAB.re / DspData.XU_DcLk,
			WU_3PhAB.im / DspData.XU_DcLk);

	DspData.XX_Mode = !DspData.XX_Mode;

	//-----------------------//
	//	DdCmp();
	//
	//-----------------------//

}

/*
 *
 *
 * */
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
//		DspData.XT_Tsc = 0.5 / DspData.PF_3PhSg; //开关频率1350Hz，波峰波谷双采样
		DspData.XT_Tsc = 0.00037; //开关频率1350Hz，波峰波谷双采样
	} else {

	}

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
		DspData.XX_Mode = 0;
		DspData.XX_DutyA = 0;
		DspData.XX_DutyB = 0;
		DspData.XX_DutyC = 0;
	} else {

	}
}

/*
 * 死区补偿
 * */
void DdCmp(void) {

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

/*
 * 16ms
 * */
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

/*
 * 16ms
 * */
void FrefUDcLk(void) {
	LowPass(&DspData.XU_DcLkFlt2, DspData.XU_DcLk1Flt,
			16.0 / DspData.PT_FRefUDcLk);
	float32 v01;
	v01 = FKG4(DspData.XU_DcLkFlt2, 0.0, DspData.PF_3PhMin,
			DspData.PU_DcLkFRefMin, DspData.PF_3PhMin, DspData.PU_DcLkFRefLow,
			DspData.PF_3PhNom, 10000.0, DspData.PF_3PhNom);
	RAMP2(&DspData.WF_3PhUDcLk, v01, DspData.PX_FRefRmpUDcLkUp * 0.016,
			DspData.PX_FRefRmpUDcLkDo * 0.016, 0.0, FALSE, FALSE);
}

/*
 * 4ms
 * */
void IPhClGenOvLd(void) {
	DspData.WF_IPhCl = 0.0;
}

/*
 * 4ms
 * */
void F3PhRef(void) {
	DspData.WF_3PhU3PhRef = Min(DspData.WF_3PhRmp, DspData.WF_3PhUDcLk)
			+ DspData.WF_IPhCl + DspData.WF_UF3PhSz;
	DspData.WF_3PhDsp = DspData.WF_3PhU3PhRef + DspData.WF_UF3PhCmp;
}

/*
 * 4ms
 * */
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

/*
 * 4ms
 * */
static struct PI_CONTROLLER PI_U3PhCl = PI_CONTROLLER_DEFAULTS;

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
	static float32 Yi = 0;

	float32 value;
	Uint16 rtrig1Q, Set;

	SR(&sr1, DspData.C_AuSz, v01);
	RS(&rs1, FTRIG(DspData.C_AuSz, &ftrig1), v01);
	rtrig1Q = RTRIG(DspData.C_AuSz, &rtrig1);

	if (rtrig1Q) {
//		value = Limit(DspData.XF_U3Ph - DspData.PF_3PhNom, -5.0, 5.0); //开始同步
		value = -0.5;
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
			value = DspData.WU_UF3PhSzErr/ DspData.PX_TrfRtPr3Ph; //开始同步
		} else {
			value = DspData.WU_UF3PhSz; //同步过程中
		}
	}

	RAMP(&Init, 0.0, 16.0 / DspData.PT_UF3PhSzRmp, 16.0 / DspData.PT_UF3PhSzRmp,
			value, !rs1, FALSE, value);

	INTEGR(&DspData.WU_UF3PhSz, DspData.WU_UF3PhSzErr,
			16.0 / DspData.PT_U3PhSzCl, Init, DspData.PU_UF3PhSzClMaxMin,
			-DspData.PU_UF3PhSzClMaxMin, Set, FALSE);

//	DspData.WU_UF3PhSz = 0.0;

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

/*
 * 4ms
 * */
void IPhClPsTrs(void) {
	DspData.WI_PhActDsp = 450;
	DspData.WI_PhRctDsp = 300;
}
