#ifndef ACM_DSP_H_
#define ACM_DSP_H_

#ifdef __cplusplus
extern "C" {
#endif

#ifndef DSP28_DATA_TYPES
#define DSP28_DATA_TYPES
typedef int                int16;
typedef long               int32;
typedef long long          int64;
typedef unsigned int       Uint16;
typedef unsigned long      Uint32;
typedef unsigned long long Uint64;
typedef float              float32;
typedef long double        float64;
#endif

/*
 * STRUCTDEFS
 * */
struct Dsp_Data {
	//--------------------------------------------//
	//
	//
	//-------------------------------------------//
	/*ANINDA&CSIVDA*/
	//采样输入、仿真输入
	float32 XU_DcLk; //input
	float32 XI_PhA; //A相电流瞬时值
	float32 XI_PhB;
	float32 XI_PhC;
	float32 XU_PhABLk; //AB线电压互感器值
	float32 XU_Bt;
	float32 XI_Bt;
	float32 XI_BtCg;

	/*MEMSDA*/
	//测量比率系数、测量保护
	/*POCPDA*/
	//相过流保护
	/*CALIDA*/
	//校准、测量保护
	/*SIPRDA*/
	//滤波
	float32 XU_3PhRe;/*3-phase output load voltage, phase-phase, real part*/
	float32 XU_3PhIm;/*3-phase output load voltage, phase-phase, imaginary part*/
	float32 XU_3PhAbs;/*3-phase output load voltage, phase-phase, peak value*/
	float32 XU_3PhRms;/*3-phase output load voltage, phase-phase, RMS value*/
	float32 XI_PhAbs;
	float32 XI_PhAct;
	float32 XI_PhRct;
	float32 XP_3Ph;
	float32 XQ_3Ph;
	float32 WX_Theta;
	float32 XT_U3Ph;/*Period of measured 3-phase output load voltage*/
	float32	XU_BtFlt;
	float32 XI_BtFlt;
	float32 XI_BtCgFlt;
	float32 XI_BtCg2Flt;
	float32 XU_DcLk1Flt;
	float32 WU_3PhAbs_Flt;
	float32 XI_PhAct_Flt;
	float32 XI_PhRct_Flt;
	float32 XI_PhAct_Flt2;
	float32 XI_PhRct_Flt2;
	float32 XI_PhAbs_Flt;
	float32 XP_3Ph_Flt;
	float32 XQ_3Ph_Flt;

	/*ACCLDA*/
	//电流限幅
	Uint16 S_IPhClTrsAv;
	float32 WU_IPhClTrs;/*3-phase output load voltage reference manipulation,transient phase current control*/
	float32 WU_IPhClTrs_Flt;

	Uint16 B_LimAct;
	float32 WU_IPhClRms;
	float32 XI_Ph1Rms;
	float32 XI_Ph2Rms;
	float32 XI_Ph3Rms;
	float32 XI_Ph1Rms_Flt;
	float32 XI_Ph2Rms_Flt;
	float32 XI_Ph3Rms_Flt;

	/*UFCODA*/
	Uint16 S_3PhOvMd;
	Uint16 S_UDcLkLow;
	float32 WX_ThetaCv;
	float32 XU_DcLkStbFltSli;
	float32 XU_DcLkStbFltHev;
	float32 WU_DcLkStb;
	float32 WU_Ref_Abs;
	float32 XX_MRef; //base Udc
	float32 WU_OvMd;/*3-phase output load voltage manipulation due to over modulation*/
	float32 WU_3PhAbsOvMd;
	float32 WU_IPhClRmsRed;
	float32 WU_3PhAbs;
	float32 XX_CrU;
	float32 XX_CrV;
	float32 XX_CrW;

	/*PPG3*/
	float32 XT_Tsc;
	float32 XX_DutyA; //output
	float32 XX_DutyB;
	float32 XX_DutyC;
	Uint16 XX_Mode;

	/*SRTODA*/
	Uint16 B_EnCv;
	Uint16 S_Opto;
	Uint16 A_CvOp;

	/*ACLS*/
	Uint16 B_IPhClTmWnd1Fl;
	Uint16 B_IPhClRmsTmFl;

	/*OVPT*/
	Uint16 A_OvpAv;
	Uint16 S_OvpEn;
	Uint16 C_OvpFcTs;
	Uint16 A_OvpFcTsOk;
	float32 XP_Ovp;/*OVP power*/
	float32 XH_Ovp_Est;/*Estimated OVP temperature*/
	float32 XX_Duty4;

	/*BTCP*/
	Uint16 A_BtCpAv;
	float32 XX_Duty5;


	//----------------------------------//
	//
	//
	//------------------------------------//
	/*TFrefRmp*/
	float32 XX_FRefRmpUp;
	float32 XX_FRefRmpDo;

	/*FrefRmp*/
	Uint16 A_FNom;
	float32 WF_3PhRmp;

	/*FrefUDcLk 16ms*/
	float32 XU_DcLkFlt2;
	float32 WF_3PhUDcLk;

	/*IPhClGenOvLd 4ms*/
	float32 WF_IPhCl;

	/*F3PhRef*/
	float32 WF_3PhU3PhRef;
	float32 WF_3PhDsp;

	/*U3PhRef*/
	float32 WU_3PhU3PhRef;
	float32 WU_3PhRmp;

	/*U3PhCl*/
	float32 WU_3PhClIn;
	float32 WU_U3PhClOut;
	float32 WU_3PhDsp;

	/*F3PhSz 16ms*/
	float32 WF_UF3PhSzErr;
	float32 WF_UF3PhSz;

	/*U3PhSz 16ms*/
	float32 WU_UF3PhSzErr;
	float32 WU_UF3PhSz;

	/*UF3PhSz 16ms*/
	Uint16 A_AuSz;
	Uint16 B_RqAuSzPrBc;	//同步失败故障

	/*UF3PhCmp*/
	float32 WF_UF3PhCmp;
	float32 WU_UF3PhCmp;

	/*IPhClPsTrs 4ms*/
	float32 WI_PhActDsp;
	float32 WI_PhRctDsp;
	float32 XX_IPhClTrsKpActDsp;
	float32 XX_IPhClTrsKpRctDsp;
	float32 XX_IPhClTrsKpAbsDsp;

	/*CvOpSaSq*/
	Uint16 NX_SqStCvOpSa;
	Uint16 C_Ck3PhGduFb;
	Uint16 C_CdAuLdCt;
	Uint16 C_CvOpSa;
	Uint16 C_AuSz;	//开始同步
	Uint16 A_CvOpSa;

	/*CvOpSoSq*/
	Uint16 NX_SqStCvOpSo;
	Uint16 C_CvBc;
	Uint16 C_CkSrCtI;	//(*Command check of current through contactors*)
	Uint16 C_OpAuLdCt;
	Uint16 C_OpChCt;
	Uint16 C_OpSrCt;
	Uint16 A_CvOpSo;

	/*CvOpSa_X*/
	Uint16 C_CvOpSaDsp;
	Uint16 C_Sa2qcDsp;
	Uint16 B_EnU3PhCl;	//开始闭环
	Uint16 B_EnU3PhOpLoCl;
	Uint16 B_EnUBtCl;
	Uint16 B_EnIBtCl;
	Uint16 A_CvCl;

	/*BtCpURef*/
	float32 WU_BtDsp;


	//--------------------------------------------//
	//
	//
	//-------------------------------------------//
	float32 PN_IPhFixMcu_Flt;
	float32 PN_U3PhRms_Flt;
	float32 PN_UDcLk_Flt;
	float32 PN_URef_Flt;
	float32 PN_IPhActRct_Flt;
	float32 PN_IPhActRctMcu_Flt;
	float32 PN_IPhAbs_Flt;
	float32 PN_PQ3PhMcu_Flt;
	float32 PN_IPhDQ_Flt;
	float32 PN_URefIPhClTrs_Flt;
	float32 PN_IPhRms_Flt;

	float32 PD_ThetaFiOs; //1.047

	float32 PU_PhClTrsMax; //	75
	float32 PI_PhClTrsAbsLim; //	600

	float32 PF_IRQBMax; //Dsp外部中断最大频率，计算最小间隔时间，计数单步时间

	float32 PX_DdCmpFa;
	float32 PI_DdCmpFu;
	float32 PI_DdCmpDs;

	float32 PX_3PhClRtHgh;
	float32 PX_3PhClRtLow;

	/**/
	float32 PZ_3PhFiNdRe; //	0,078 滤波电感电阻
	float32 PZ_3PhFiNdIm; //	0,207滤波电感电抗
	float32 PZ_3PhFiCaIm; //	-5,47 滤波电容电抗折算到一次侧
	float32 PZ_3PhTfRe; //		0
	float32 PZ_3PhTfIm; //		0

	Uint16 L_UDcLkStbEn; //	TRUE
	float32 PN_UDcLkStbSliSmt; //	2200
	float32 PN_UDcLkStbHevSmt; //	13,5
	float32 PU_DcLkStbMaxMin; //	100
	float32 PX_KpUDcLkStb;//150

	float32 PX_3PhRndMax; //	0,0345
	Uint16 L_3PhRndEn; //	TRUE
	float32 PF_3PhSg; //1350

	Uint16 L_EnTPrDdCmp;
	Uint16 L_DsPlElm3PhMod; //TRUE

	//DUVP
	float32 PARTDP_PU_DcLkMin; //	1000

	//DOVP
	float32 PARTDP_PU_DcLkHgh4; //	1950

	//MEMS
	float32 PX_U3PhMmSvMax;	//0,9
	float32 L_U3PhRmsPlySv;	//TRUE
	float32 PU_U3PhRmsPlySvLim;	//35	V
	float32 PT_U3PhRmsPlySvDy;	//1	s

	//ACCL
	Uint16 L_EnIPhClRms;	//	FALSE
	float32 PI_PhClRmsLim;	//	800	A

	//--------------------------------------------//
	//
	//
	//-------------------------------------------//
	/*TFrefRmp*/
	float32 PX_FRefRmpUp;
	float32 PX_FRefRmpDo1;
	float32 PX_FRefRmpDo2;
	float32 PX_FRefRmpDo3;
	float32 PF_FRefRmpDo12;	//
	float32 PF_FRefRmpDo23;

	/*FrefRmp*/
	float32 PF_3PhNom;
	float32 PF_3PhMin;

	/*FrefUDcLk*/
	float32 PT_FRefUDcLk;	//100ms
	float32 PF_UDcLkMin;	//	50
	float32 PU_DcLkFRefMin;	//	1000
	float32 PU_DcLkFRefLow;	//	1000
	float32 PX_FRefRmpUDcLkUp;	//	40
	float32 PX_FRefRmpUDcLkDo;	//	40

	/*IPhClGenOvLd*/

	/*F3PhRef*/

	/*U3PhRef*/
	Uint16 L_ExtU3PhRef;
	float32 PF_U3PhRef2;
	float32 PF_U3PhRef3;
	float32 PU_U3PhRef1;
	float32 PU_U3PhRef2;
	float32 PU_U3PhRef3;
	float32 PU_U3PhRef4;
	Uint16 L_EnRmpU3PhRef;

	/*U3PhCl*/
	float32 PX_TrfRtPr3Ph;
	float32 PU_3PhClRefMax;
	float32 PU_3PhClRefMin;
	float32 PX_KpU3PhCl;
	float32 PT_U3PhCl;
	float32 PU_3PhClMax;
	float32 PU_3PhClMin;

	/*F3PhSz*/
	float32 PT_UF3PhSzRmp;
	float32 PX_KpF3PhSzCl;
	float32 PT_F3PhSzCl;
	float32 PF_UF3PhSzClMaxMin;

	/*U3PhSz*/
	float32 PU_UF3PhSzClAdd;
	float32 PT_U3PhSzCl;
	float32 PU_UF3PhSzClMaxMin;

	/*UF3PhSz*/
	float32 PF_UF3PhSzRdy;
	float32 PU_UF3PhSzRdy;
	float32 PT_UF3PhSzRdy;
	float32 PT_UF3PhSzFl;

	/*UF3PhCmp*/
	Uint16 L_EnUF3PhCmp;
	float32 PI_UF3PhCmpActHiLo;
	float32 PF_UF3PhCmpActHiLo;
	float32 PI_UF3PhCmpRctHiLo;
	float32 PU_UF3PhCmpRctHiLo;

	/*IPhClPsTrs*/
	float32 PX_IPhClTrsKpAct;	//	0,005
	float32 PX_IPhClTrsKpRct;	//	0,03
	float32 PX_IPhClTrsKpAbs;	//	0

	/*CvOpSaSq*/
	float32 PU_3PhIdlCmp;
	float32 PU_3PhActCmp;

	/*CvOpSa*/
	Uint16 L_PrlAcm;	//	TRUE


	/**/
	Uint16 C_AuSzR;
	Uint16 C_AuSzF;
	Uint16 ZeroOut;
	Uint16 Set;
	Uint16 Reset;
	Uint16 FadeOut;
	float32	Init;
	float32	Interger;
}DspDate;

/*
 *
 * */
extern volatile struct Dsp_Data DspData;


//以下原DSP任务
/*
 *
 * */
extern void DspInit(void);

/*
 * IRQB 370us
 * */
extern void SIPR_B(void);
extern void ACCL_B(void);
extern void UFCO_B(void);
extern void PPG3_B(void);

/*
 * IRQC 200us
 * */
extern void SRTO_C(void);

/*
 * T2 1ms
 * */
void HSTI_T2(void);
void MEMS_T2(void);
void ACCL_T2(void);
void ACLS_T2(void);
void OVPT_T2(void);
void OROP_T2(void);
void POCP_T2(void);
void AICS_T2(void);
void HSTO_T2(void);

/*
 * T3 100ms
 * */
void HSTP_T3(void);


//以下原MCU任务
/*
 * A_Cl1 4ms
 * */
extern void IPhClPsTrs(void);
extern void IPhClGenOvLd(void);
extern void UF3PhCmp(void);

extern void F3PhRef(void);
extern void U3PhRef(void);

extern void U3PhCl(void);



/*
 * A_Cl2 16ms
 * */
extern void TFrefRmp(void);
extern void FrefRmp(void);

extern void FrefUDcLk(void);

extern void F3PhSz(void);
extern void U3PhSz(void);
extern void UF3PhSz(void);


#ifdef __cplusplus
}
#endif /* extern "C" */

#endif
