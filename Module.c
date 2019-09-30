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

	/*********************************************
	 *
	 *
	 *******************************************/
	//	static TYPE_IIRFILTER_2ND U3PhRe, U3PhIm;
	/*IIR Notch Filter*/
	//	U3PhRe.In = 2.0 * p->XU_PhABLk
	//			* cos(p->WX_Theta + p->PD_ThetaFiOs);
	//	AdaptIIRNotchFilter(&U3PhRe, 2.0 * PI2 * Max(p->WF_3PhDsp, 1.0),
	//			p->XT_3PhSmpRnd);
	//
	//	U3PhIm.In = 2.0 * p->XU_PhABLk
	//			* sin(p->WX_Theta + p->PD_ThetaFiOs);
	//	AdaptIIRNotchFilter(&U3PhIm, 2.0 * PI2 * Max(p->WF_3PhDsp, 1.0),
	//			p->XT_3PhSmpRnd);
	//
	//	/**/
	//	p->XU_3PhAbs_Notch = sqrt(
	//			U3PhRe.Out * U3PhRe.Out + U3PhIm.Out * U3PhIm.Out);
	/*
	 *
	 * */
//	static TYPE_SOGIOSGMA sogiosg = SOGIOSGMA_DEFAULTS;
//	sogiosg.phase = p->XU_PhABLk;
//	sogiosg.Ts = p->XT_3PhSmpRnd;
//	sogiosg.w0 = 100 * PI;
//	sogiosg.K = sqrt(0.1);
//	sogiosg.Ki = 10000;
//	SOGIOSGFLL(&sogiosg);

	cfloat32 XU_3PhAB;
	cfloat32 XU_3PhDQ;

	/**/
//	if (SIMULATION) {
//		//仿真
//		XU_3PhAB = CPLXSCA(
//				CPLXMULT(FRAC2CPLX(sogiosg.alpha, sogiosg.beta),
//						POL2CPLX(1.0, 0.0)), 1.0);
//
//	} else {
		//调试
		//		XU_3PhAB = CPLXSCA(
		//				CPLXMULT(FRAC2CPLX(sogiosg.alpha, sogiosg.beta),
		//						POL2CPLX(1.0, PI / 2.0)),
		//				1.095 * 100.0 * PI / sqrt(sogiosg.w * sogiosg.w + 1));
//		XU_3PhAB = CPLXSCA(
//				CPLXMULT(FRAC2CPLX(sogiosg.alpha, sogiosg.beta),
//						POL2CPLX(1.0, PI / 2.0)), 1.095);
//	}



	XU_3PhDQ = CPLXMULT(XU_3PhAB,
			POL2CPLX(1.0, -(p->WX_Theta + p->PD_ThetaFiOs)));

	p->XU_3PhRe = XU_3PhDQ.re;
	p->XU_3PhIm = XU_3PhDQ.im;

	//	p->XU_3PhRe = U3PhRe.Out;
	//	p->XU_3PhIm = U3PhIm.Out;

	p->XU_3PhAbs = sqrt(
			p->XU_3PhRe * p->XU_3PhRe
					+ p->XU_3PhIm * p->XU_3PhIm);



	/**/
//	p->XF_U3Ph = sogiosg.w / 2.0 / PI;

	/**/
	p->XU_3PhAbs = sqrt(
			p->XU_3PhRe * p->XU_3PhRe
					+ p->XU_3PhIm * p->XU_3PhIm);
	/**/
	//	LowPass(&p->XU_3PhSqu, p->XU_PhABLk * p->XU_PhABLk,
	//			p->XT_3PhSmpRnd * p->PN_U3PhRms_Flt);
	//	p->XU_3PhRms = sqrt(p->XU_3PhSqu);
	p->XU_3PhRms = p->XU_3PhAbs / SQRT2;

	/**/
	LowPass(&p->XU_DcLk1Flt, p->XU_DcLk1,
			p->XT_3PhSmpRnd * p->PN_UDcLk_Flt);
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

