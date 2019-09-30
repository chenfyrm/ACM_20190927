/*
 * Module.c
 *
 *  Created on: 2019-9-30
 *      Author: 700363
 */
#include "math.h"

#include "UserDefs.h"
#include "UserMath.h"

#include "complex.h"
#include "control.h"

#include "Module.h"

/**/
void SIPR_B(struct SIPRDA *p) {
	/*
	 * clark变换
	 * */
	p->XI_PhAB = PH3TOCPLX(p->XI_PhA, p->XI_PhB, p->XI_PhC);

	LowPass(&p->XI_PhReFix, p->XI_PhAB.re,
			p->XT_3PhSmpRnd * p->PN_IPhFixMcu_Flt / 2.0);
	LowPass(&p->XI_PhImFix, p->XI_PhAB.im,
			p->XT_3PhSmpRnd * p->PN_IPhFixMcu_Flt / 2.0);

	cfloat32 XS_3Ph;
	XS_3Ph = CPLXSCA(CPLXMULT(p->WU_3PhAB, CPLXCONJ(p->XI_PhAB)),
			1.5);
	p->XP_3Ph = XS_3Ph.re;
	p->XQ_3Ph = XS_3Ph.im;

	/*park变换*/
	p->XI_PhDQ = CPLXMULT(p->XI_PhAB,
			POL2CPLX(1.0, -p->WX_Theta));
	/**/
	p->XI_PhAct = p->XI_PhDQ.re;
	p->XI_PhRct = p->XI_PhDQ.im;

	p->WX_Theta += 2.0 * PI * p->WF_3Ph * p->XT_3PhSmpRnd;
	p->WX_Theta = fmod(p->WX_Theta, 2 * PI);

	/*
	 *
	 * */
//	p->XT_U3Ph = 50.0;

	/**/
	LowPass(&p->XU_3PhSqu, p->XU_3Ph * p->XU_3Ph,
			p->XT_3PhSmpRnd * p->PN_U3PhRms_Flt);
	p->XU_3PhRms = sqrt(p->XU_3PhSqu);

	/*********************************************
	 *
	 *
	 *******************************************/
	//	static TYPE_IIRFILTER_2ND U3PhRe, U3PhIm;
	/*IIR Notch Filter*/
	p->U3PhRe.In = 2.0 * p->XU_3Ph
			* cos(p->WX_Theta + p->PD_ThetaFiOs);
	AdaptIIRNotchFilter(&p->U3PhRe, 2.0 * PI2 * Max(p->WF_3Ph, 1.0),
			p->PT_3PhSmp);

	p->U3PhIm.In = 2.0 * p->XU_3Ph
			* sin(p->WX_Theta + p->PD_ThetaFiOs);
	AdaptIIRNotchFilter(&p->U3PhIm, 2.0 * PI2 * Max(p->WF_3Ph, 1.0),
			p->PT_3PhSmp);

	/**/
	p->XU_3PhRe = p->U3PhRe.Out;
	p->XU_3PhIm = p->U3PhIm.Out;

	p->XU_3PhAbs = sqrt(
			p->XU_3PhRe * p->XU_3PhRe + p->XU_3PhIm * p->XU_3PhIm);

//	p->XU_DcLk1Dy = p->XU_DcLk1;

	/**/
	LowPass(&p->XU_DcLk1Flt, p->XU_DcLk1,
			p->XT_3PhSmpRnd * p->PN_UDcLk1_Flt);
	LowPass(&p->WU_3PhAbs_Flt, p->WU_3PhAbs,
			p->XT_3PhSmpRnd * p->PN_URef_Flt);
	LowPass(&p->XI_PhAct_Flt, p->XI_PhAct,
			p->XT_3PhSmpRnd * p->PN_IPhActRct_Flt);
	LowPass(&p->XI_PhRct_Flt, p->XI_PhRct,
			p->XT_3PhSmpRnd * p->PN_IPhActRct_Flt);
	LowPass(&p->XI_PhAct_Flt2, p->XI_PhAct,
			p->XT_3PhSmpRnd * p->PN_IPhActRctMcu_Flt);
	LowPass(&p->XI_PhRct_Flt2, p->XI_PhRct,
			p->XT_3PhSmpRnd * p->PN_IPhActRctMcu_Flt);
	LowPass(&p->XI_PhAbs_Flt, p->XI_PhAbs,
			p->XT_3PhSmpRnd * p->PN_IPhAbs_Flt);
	LowPass(&p->XP_3Ph_Flt, p->XP_3Ph,
			p->XT_3PhSmpRnd * p->PN_PQ3PhMcu_Flt);
	LowPass(&p->XQ_3Ph_Flt, p->XQ_3Ph,
			p->XT_3PhSmpRnd * p->PN_PQ3PhMcu_Flt);
	CplxLowPass(&p->XI_PhDQ_Flt, p->XI_PhDQ,
			p->XT_3PhSmpRnd * p->PN_IPhDQ_Flt);

}

/*
 *
 * */
void ACCL_B(struct ACCLDA *p) {

	float32 a, b, c;
	a = Min(p->PI_PhClTrsAbsLim - p->XI_PhAbs, 0.0) * p->XX_IPhClTrsKpAbs;
	b = Min(p->WI_PhAct - p->XI_PhAct_Flt, 0.0) * p->XX_IPhClTrsKpAct;
	c = Min(p->WI_PhRct - p->XI_PhRct_Flt, 0.0) * p->XX_IPhClTrsKpRct;

	/**/
	p->WU_IPhClTrs = Max(-p->PU_PhClTrsMax, a + b + c);

	/**/
	if (p->WU_IPhClTrs < 0) {
		p->S_IPhClTrsAv = 1;
	} else {
		p->S_IPhClTrsAv = 0;
	}

	/**/
	LowPass(&p->WU_IPhClTrs_Flt, p->WU_IPhClTrs,
			p->XT_3PhSmpRnd * p->PN_URefIPhClTrs_Flt);

}


//void UFCO_B(void) {
//
//	DspData.WU_3PhSec = POL2CPLX(McuData.WU_3PhDsp, 0.0); //静止坐标系按1次侧，同步频率按WF_3PhDsp  DQ
//
//	DspParam.PZ_3PhFiNd = FRAC2CPLX(DspParam.PZ_3PhFiNdRe,
//			DspParam.PZ_3PhFiNdIm / 50.0 * McuData.WF_3PhDsp);
//	DspParam.PZ_3PhFiCa = FRAC2CPLX(0.0,
//			DspParam.PZ_3PhFiCaIm / 50.0 * McuData.WF_3PhDsp);
//	DspParam.PZ_3PhTf = FRAC2CPLX(DspParam.PZ_3PhTfRe,
//			DspParam.PZ_3PhTfIm / 50.0 * McuData.WF_3PhDsp);
//
//	cfloat32 Z1, Z2;
//	Z1 = CPLXDIV(DspParam.PZ_3PhFiCa,
//			CPLXADD(DspParam.PZ_3PhFiCa, DspParam.PZ_3PhTf));
//	Z2 = CPLXADD(DspParam.PZ_3PhFiNd, CPLXMULT(DspParam.PZ_3PhTf, Z1));
//
//	/**/
//	DspData.WU_3PhPm = CPLXADD(CPLXMULT(DspData.WU_3PhSec, Z1),
//			CPLXMULT(DspData.XI_PhDQ_Flt, Z2));
//	//B_EnBuiTs
//	//		DspData.WU_3PhPm = DspData.WU_3PhSec;	//DQ
//	/*
//	 * ipark变换
//	 * */
//	DspData.WU_3PhPmAB = CPLXMULT(DspData.WU_3PhPm,
//			POL2CPLX(1.0, DspData.WX_Theta)); //ipark
//	/*
//	 * 电流直流分量控制
//	 * WU_IPhDcClRe WU_IPhDcClIm
//	 * */
//
//	/**/
//	CPLX2POL(&DspData.WU_Ref_Abs, &DspData.WX_ThetaCv, DspData.WU_3PhPmAB);
//
//	/******************************************************************
//	 * 直流母线电压振荡抑制
//	 *
//	 *
//	 *
//	 *
//	 *****************************************************************/
//	LowPass(&DspData.XU_DcLkStbFltSli, DspData.XU_DcLk,
//			DspData.XT_Tsc * DspParam.PN_UDcLkStbSliSmt);
//	LowPass(&DspData.XU_DcLkStbFltHev, DspData.XU_DcLk,
//			DspData.XT_Tsc * DspParam.PN_UDcLkStbHevSmt);
//	DspData.WU_DcLkStb = Limit(
//			DspParam.PX_KpUDcLkStb
//					* (pow(DspData.XU_DcLkStbFltSli / DspData.XU_DcLkStbFltHev,
//							2.0) - 1.0), -DspParam.PU_DcLkStbMaxMin,
//			DspParam.PU_DcLkStbMaxMin);
//
//	/**/
//	DspData.WU_Ref_Abs = DspData.WU_Ref_Abs + DspData.WU_IPhClTrs
//			+ DspData.WU_DcLkStb;
//	DspData.WU_Ref_Abs = Max(0.0, DspData.WU_Ref_Abs);
//
//	DspData.XX_MRef = DspData.WU_Ref_Abs / Max(1.0, DspData.XU_DcLk);
//	if (DspData.A_CvOp && (DspData.XX_MRef > ONEbySQRT3)) {
//		DspData.S_3PhOvMd = 1;
//	} else {
//		DspData.S_3PhOvMd = 0;
//	}
//
//	DspData.WU_OvMd = DspData.XU_DcLk * Min(0.6057 - DspData.XX_MRef, 0); //<0
//	//
//	DspData.WU_3PhAbsOvMd = DspData.XU_DcLk * OvMd(DspData.XX_MRef);
//	if (DspData.B_LimAct) {
//		DspData.WU_IPhClRmsRed = DspData.WU_IPhClRms - DspData.WU_3PhAbsOvMd;
//	} else {
//		DspData.WU_IPhClRmsRed = 0;
//	}
//	DspData.WU_3PhAbs = DspData.WU_3PhAbsOvMd + DspData.WU_IPhClRmsRed;
//	DspData.WU_3PhAB = POL2CPLX(DspData.WU_3PhAbs, DspData.WX_ThetaCv);
//
//	//
//	SVPWM(&DspData.XX_CrU, &DspData.XX_CrV, &DspData.XX_CrW,
//			CPLXSCA(DspData.WU_3PhAB, 1.0 / DspData.XU_DcLk));
//
//	DspData.XX_Mode = !DspData.XX_Mode;
//	//	DdCmp();
//
//}


