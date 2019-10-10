#ifndef ACM_DSP_H_
#define ACM_DSP_H_

#ifdef __cplusplus
extern "C" {
#endif


/*STRUCTDEFS*/
struct Dsp_Data {
	//--------------------------------------------//
	//
	//
	//-------------------------------------------//
	/*ANINDA&CSIVDA*/
	//输入
	float32 XU_DcLk; //input
//	float32 XI_DcLk;
	float32 XI_PhA;
	float32 XI_PhB;
	float32 XI_PhC;
	float32 XU_PhABLk;
//	float32 XU_PhBCLk;

	/*MEMSDA*/
	//测量比例

	/*POCPDA*/
	//保护


	/*CALIDA*/
	//校准


	/*SIPRDA*/
	//滤波
	float32 XI_PhReFix;
	float32 XI_PhImFix;
	cfloat32 XI_PhAB;
	float32 XP_3Ph;
	float32 XQ_3Ph;
	float32 XI_PhAbs;
	float32 XI_PhAct;
	float32 XI_PhRct;
	cfloat32 XI_PhDQ;
	float32 WX_Theta;
	float32 XF_U3Ph;/*Frequency of measured 3-phase output load voltage*/

	float32 XU_3PhSqu;
	float32 XU_3PhRms;/*3-phase output load voltage, phase-phase, RMS value*/
	float32 XU_3PhRe;/*3-phase output load voltage, phase-phase, real part*/
	float32 XU_3PhIm;/*3-phase output load voltage, phase-phase, imaginary part*/
	float32 XU_3PhAbs;/*3-phase output load voltage, phase-phase, peak value*/
	float32 XU_3PhAbs_Notch;

	float32 XU_DcLkDy;
	float32 XU_DcLkFlt;
	float32 WU_3PhAbs_Flt;

	float32 XI_PhAct_Flt;
	float32 XI_PhRct_Flt;
	float32 XI_PhAct_Flt2;
	float32 XI_PhRct_Flt2;
	float32 XI_PhAbs_Flt;
	cfloat32 XI_PhDQ_Flt;
	float32 XP_3Ph_Flt;
	float32 XQ_3Ph_Flt;

	/*ACCLDA*/
	//保护
	float32 WU_IPhClTrs;/*3-phase output load voltage reference manipulation,transient phase current control*/
	Uint16 S_IPhClTrsAv;
	float32 WU_IPhClTrs_Flt;

	Uint16 XX_CntPh1Rms;
	Uint16 XX_CntPh2Rms;
	Uint16 XX_CntPh3Rms;
	float32 XI_Ph1Squ;
	float32 XI_Ph2Squ;
	float32 XI_Ph3Squ;
	float32 XI_Ph1Rms;
	float32 XI_Ph2Rms;
	float32 XI_Ph3Rms;
	float32 XI_Ph1Rms_Flt;
	float32 XI_Ph2Rms_Flt;
	float32 XI_Ph3Rms_Flt;

	float32 WU_IPhClRms;
	Uint16 B_LimAct;

	/*BACCDA*/

	/*UFCODA*/
	cfloat32 WU_3PhSec;
	cfloat32 WU_3PhPm;
	cfloat32 WU_3PhPmAB;
	float32 XU_DcLkStbFltSli;
	float32 XU_DcLkStbFltHev;
	float32 WU_DcLkStb;
	float32 WX_ThetaCv;
	float32 WU_Ref_Abs;
	float32 XX_MRef; //base Udc

	Uint16 S_3PhOvMd;
	float32 WU_OvMd;/*3-phase output load voltage manipulation due to over modulation*/
	float32 WU_3PhAbsOvMd;
	float32 WU_IPhClRmsRed;
	float32 WU_3PhAbs;
	cfloat32 WU_3PhAB;

	float32 XX_CrU;
	float32 XX_CrV;
	float32 XX_CrW;
	Uint16 S_UDcLkLow;

	/*PPG3*/
	float32 XT_Tsc;
	Uint16 XX_PwmPdVv;
	float32 XX_DutyA; //output
	float32 XX_DutyB;
	float32 XX_DutyC;
	Uint16 XX_Mode;
	Uint16 L_DsPlElm3PhMod; //TRUE


	/*SRTODA*/
	Uint16 B_EnCv;
	Uint16 A_CvOp;

	/**/
	float32 XP_Ovp;/*OVP power*/
	float32 XH_Ovp_Est;/*Estimated OVP temperature*/

	/*MEMS*/
	Uint16 B_U3PhRmsPlySvFl; //三相输出电压合理性监视

	/*ACLS*/
	Uint16 B_IPhClTmWnd1Fl;
	Uint16 B_IPhClRmsTmFl;

	/*OVPT*/
	float32 XX_Duty4A;
	Uint16 C_OvpFcTs;
	Uint16 A_OvpFcTsOk;

	Uint16 A_BtCpAv;

	Uint16 A_OvpAv;
	Uint16 S_OvpEn;

	/**/
	Uint16 B_DspOvLdFl;
	Uint16 S_DspWdAlm;
	Uint16 S_DspFpgaComFl;
	Uint16 B_DspStkSvFl;

	/*HSTIDA*/
//	float32

	/*FPGIDA*/

	//----------------------------------//
	//
	//
	//------------------------------------//
	/*ACCLMA*/
	/*IPhClGenOvLd 4ms*/
	float32 WF_IPhCl;
	Uint16 S_IPhClGenOvLdAv;

	/*IPhClPsTrs 4ms*/
	float32 WI_PhActDsp;
	float32 WI_PhRctDsp;

	float32 XX_IPhClTrsKpActDsp;
	float32 XX_IPhClTrsKpRctDsp;
	float32 XX_IPhClTrsKpAbsDsp;

	/*IPhDcCl*/
	float32 WU_IPhDcClDsp;

	/*COMPMA*/
	/*UF3PhCmp*/
	float32 WF_UF3PhCmp;
	float32 WU_UF3PhCmp;

	/*UFCOMA*/
	/*F3PhRef*/
	float32 WF_3PhDsp;/**/
	float32 WF_3PhU3PhRef;

	/*U3PhRef*/
	float32 WU_3PhU3PhRef;
	float32 WU_3PhRmp;
	float32 WU_3PhExt;

	/*U3PhCl*/
	float32 WU_3PhDsp;/**/
	float32 WU_3PhClIn;
	float32 WU_U3PhClOut;
	Uint16 S_U3PhClDivFl;

	/*TFrefRmp 16ms*/
	float32 XX_FRefRmpUp;
	float32 XX_FRefRmpDo;

	/*FrefUDcLk 16ms*/
	float32 XU_DcLkFlt2;
	float32 WF_3PhUDcLk;

	/*FrefRmp 16ms*/
	float32 WF_3PhRmp;
	Uint16 A_FNom;
	Uint16 B_FRefIPhInHigh;
	Uint16 B_IPhDcClEn;
	Uint16 S_CvCurLim;
	Uint16 S_ActComBus;

	/*AUSZMA*/
	/*F3PhSz 16ms*/
	float32 WF_UF3PhSz;
	float32 WF_UF3PhSzErr;

	/*U3PhSz 16ms*/
	float32 WU_UF3PhSz;
	float32 WU_UF3PhSzErr;

	/*UF3PhSz 16ms*/
	Uint16 A_AuSz;
	Uint16 B_RqAuSzPrBc;

	/*SRTOMA*/
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

	/*BAUCMA*/
	/*BtCpURef*/
	float32 WU_BtDsp;

	/*BTCPMA*/
	Uint16 B_RqBtCpSfBc;
	Uint16 B_RqBtCpPrBc;
	Uint16 B_RqBtCpSlt;
	Uint16 B_RqBtCpSa;
	Uint16 B_RqBtCpSo;
	Uint16 S_BtCpAv;

	/*OVPTMA*/
	Uint16 C_OvpFcTsDsp;

	Uint16 C_DspNt;
	Uint16 C_SaDsp;
	Uint16 C_RstDsp;
	Uint16 C_ResetDspDl;
	Uint16 B_DspRamTsSa;

	Uint16 B_FrOvpDsp;

	Uint16 NX_McuSqNo;

	/*ISCSMA*/
	Uint16 A_SrCtIOk;

	/*DIGIMA*/
	Uint16 A_CdAuLdCt;
	Uint16 A_CdChCt;
	Uint16 A_CdSrCt;

	/*ALCSMA 16ms*/
	Uint16 C_CdAuLdCt_ALCS;
	Uint16 B_RqPrBcReSa_ALCS;
	Uint16 B_3PhDsOpAuLdCt;

	Uint16 B_RqALCSPrBc;
	Uint16 B_AuLdCtOnFl;
	Uint16 B_AuLdCtOfFl;

	/*SFPAMA*/
	Uint16 A_GduFb3PhOk;

	/*SSSCMA*/
	/*MnStCl*/
	Uint16 NX_MnSqSt;
	Uint16 C_DcuNt;
	Uint16 C_DcuReNt;
	Uint16 S_DcuNt;
	Uint16 C_CvNt;
	Uint16 S_DcLkDh;
	Uint16 C_DcLkCh;
	Uint16 S_DcLkCh;
	Uint16 C_CvOpSa_MnSq;
	Uint16 S_CvOpSa;
	Uint16 C_CvOpSo_MnSq;
	Uint16 S_CvOpSo;
	Uint16 C_DcLkDh;
	Uint16 C_PrSd;
	Uint16 C_FsSd;
	Uint16 C_SfSd;
	Uint16 C_PrBc;
	Uint16 C_SfBc;
	Uint16 C_Slt;
	Uint16 S_PrSd;
	Uint16 S_FsSd;
	Uint16 S_SfSd;
	Uint16 S_PrBc;
	Uint16 S_SfBc;
	Uint16 S_Slt;

	Uint16 B_BcOpSrCt;	//通过打开分离接触器封锁
	Uint16 B_RqCvOpSa;
	Uint16 A_DcLkCh;
	Uint16 A_DcuNt;
	Uint16 B_RqDcLkCh;
	Uint16 B_RqDcuReNt;
	Uint16 S_SyRd;
	Uint16 A_DcLkDh;
	Uint16 B_RqDcLkDh;
	Uint16 S_CvRd;

	/*DCCHMA*/
	Uint16 C_Sa2qc;

	/*DCDHMA*/
	Uint16 C_So2qc;

	/*CVISMA*/
	Uint16 B_RqCvBc;
	Uint16 C_So2qc_slt;

	/*PRSDMA*/
	Uint16 C_FpgaPrSd;

	/*FSSDMA*/
	Uint16 C_FpgaFsSd;

	/*SFSDMA*/
	Uint16 C_FpgSfSd;

	/*PRBCMA*/
	Uint16 C_FpgaPrBc;

	/*MEMSMA*/
	Uint16 B_EnU3PhOpLoCl_mem;

	/*IUCLMA*/
	Uint16 S_IdlAcmBu;

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
		float32 PZ_3PhTfRe; //	0
		float32 PZ_3PhTfIm; //	0
		cfloat32 PZ_3PhFiNd;
		cfloat32 PZ_3PhFiCa;
		cfloat32 PZ_3PhTf;

		Uint16 L_UDcLkStbEn; //	TRUE
		float32 PN_UDcLkStbSliSmt; //	2200
		float32 PN_UDcLkStbHevSmt; //	13,5
		float32 PU_DcLkStbMaxMin; //	100
		float32 PX_KpUDcLkStb;
		float32 PX_KpUDcLkVoStbFb;

		float32 PX_3PhRndMax; //	0,0345
		Uint16 L_3PhRndEn; //	TRUE
		float32 PF_3PhSg; //1350

		Uint16 L_EnTPrDdCmp;
		Uint16 L_DsPlElm3PhMod;

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
	/*ACCLMA*/
	/*IPhClGenOvLd*/
	float32 PF_IPhClMin;	//	50
	float32 PF_IPhClMinErr;	//	25
	float32 PX_IPhClIntMax;	//	20000
	float32 PX_IPhClIntMin;	//	0
	float32 PT_IPhClInt;	//	100

	/*IPhClPsTrs*/
	float32 PI_IPhClActMax;	//	400
	float32 PI_IPhClActMin;	//	100
	float32 PI_IPhClActPsTrs;	//	450
	float32 PI_IPhClActOs;	//	100
	float32 PX_IPhClActDe;	//	200
	float32 PI_IPhClRctMax;	//400
	float32 PI_IPhClRctMin;	//0
	float32 PI_IPhClRctPsTrs;	//	300
	float32 PI_IPhClRctOs;	//100
	float32 PX_IPhClRctDePos;	//200
	float32 PX_IPhClRctDeNg;	//200
	float32 PI_IPhClPsTrsLim;	//	600
	float32 PX_IPhClTrsKpAct;	//	0,005
	float32 PX_IPhClTrsKpRct;	//	0,03
	float32 PX_IPhClTrsKpAbs;	//	0

	/*IPhDcCl*/
	Uint16 L_EnIPhDcCl;	//	TRUE
	float32 PU_IPhDcClMaxMin;	//	3
	float32 PX_KpIPhDcCl;	//	0,2
	float32 PX_KiIPhDcCl;	//	0,0001

	/*TFrefRmp*/
	float32 PX_FRefRmpUp;
	float32 PX_FRefRmpUpSlaveAcm;
	float32 PX_FRefRmpDo1;
	float32 PX_FRefRmpDo2;
	float32 PX_FRefRmpDo3;
	float32 PF_FRefRmpDo12;
	float32 PF_FRefRmpDo23;

	/*FrefUDcLk*/
	float32 PF_UDcLkMin;	//	50
	float32 PU_DcLkFRefMin;	//	1000
	float32 PU_DcLkFRefLow;	//	1000
	float32 PX_FRefRmpUDcLkUp;	//	40
	float32 PX_FRefRmpUDcLkDo;	//	40
	float32 PT_FRefUDcLk;	//100ms

	/*FrefRmp*/
	float32 PF_3PhNom;
	float32 PF_3PhMin;

	/*UF3PhCmp*/
	Uint16 L_EnUF3PhCmp;
	float32 PI_UF3PhCmpActHiLo;	//param
	float32 PF_UF3PhCmpActHiLo;
	float32 PI_UF3PhCmpRctHiLo;
	float32 PU_UF3PhCmpRctHiLo;

	/*F3PhSz*/
	float32 PX_KpF3PhSzCl;
	float32 PT_F3PhSzCl;
	float32 PF_UF3PhSzClMaxMin;
	float32 PT_UF3PhSzRmp;

	/*U3PhSz*/
	float32 PU_UF3PhSzClAdd;
	float32 PU_UF3PhSzClMaxMin;

	/*UF3PhSz*/
	float32 PF_UF3PhSzRdy;
	float32 PU_UF3PhSzRdy;
	float32 PT_UF3PhSzRdy;
	float32 PT_UF3PhSzFl;

	/*U3PhRef*/
	float32 PF_U3PhRef2;
	float32 PF_U3PhRef3;
	float32 PU_U3PhRef1;
	float32 PU_U3PhRef2;
	float32 PU_U3PhRef3;
	float32 PU_U3PhRef4;
	Uint16 L_ExtU3PhRef;
	float32 PX_ExtU3PhRefRmp;
	Uint16 L_EnRmpU3PhRef;
	float32 PX_U3PhRefRmpSel;
	float32 PX_U3PhRefRmp1;
	float32 PX_U3PhRefRmp2;

	/*U3PhCl*/
	Uint16 B_En3PhClFqAda;
	Uint16 L_En3PhCl;
	Uint16 L_EnU3PhOpLoCl;
	float32 PX_KpU3PhCl;
	float32 PT_U3PhCl;
	float32 PU_3PhClMax;
	float32 PU_3PhClMin;
	float32 PU_3PhClRefMax;
	float32 PU_3PhClRefMin;
	float32 PX_TrfRtPr3Ph;

	/*CvOpSaSq*/
	float32 PU_3PhIdlCmp;
	float32 PU_3PhActCmp;

	/*CvOpSa*/
	Uint16 L_PrlAcm;	//	TRUE

	/*DCDS*/
//	PARTAP_PU_DhDcLk_Max	100	V
//	PARTAP_PT_DcLkDhDy	600	ms
//	PARTAP_PT_FrOvp	500	ms
//	PARTAP_L_EnDhDcLkCvSl	TRUE
//	PARTAP_PU_DcLkCvSlDh	1000	V
};


/**/
extern volatile struct Dsp_Data DspData;

/*DSP*/
/*IRQB*/
//逆变
extern void DspInit(void);

extern void DspTask_185us(void);	//同步锁相

extern void DspTask_B(void);
extern void DspTask_C(void);
extern void DspTask_T2(void);
extern void DspTask_T3(void);

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif
