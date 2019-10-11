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
	//�������롢��������
	float32 XU_DcLk; //input
//	float32 XI_DcLk;
	float32 XI_PhA; //A�����˲ʱֵ
	float32 XI_PhB;
	float32 XI_PhC;
//	float32 XU_PhA;//A���ѹ˲ʱֵ
//	float32 XU_PhB;
//	float32 XU_PhC;
	float32 XU_PhABLk; //AB�ߵ�ѹ������ֵ
//	float32 XU_PhBCLk;
	float32 XU_Bt;
	float32 XI_Bt;
	float32 XI_BtCg;

	/*MEMSDA*/
	//��������ϵ������������
	/*POCPDA*/
	//���������
	/*CALIDA*/
	//У׼����������
	/*SIPRDA*/
	//�˲�
	float32 XU_3PhRe;/*3-phase output load voltage, phase-phase, real part*/
	float32 XU_3PhIm;/*3-phase output load voltage, phase-phase, imaginary part*/
	float32 XU_3PhAbs;/*3-phase output load voltage, phase-phase, peak value*/
	float32 XU_3PhSqu;
	float32 XU_3PhRms;/*3-phase output load voltage, phase-phase, RMS value*/
	cfloat32 XI_PhAB;
	cfloat32 XI_PhDQ;
	float32 XI_PhAbs;
	float32 XI_PhAct;
	float32 XI_PhRct;
	float32 XP_3Ph;
	float32 XQ_3Ph;
	float32 WX_Theta;
	float32 XF_U3Ph;/*Frequency of measured 3-phase output load voltage*/
	float32 XU_DcLk_Flt;
	float32 WU_3PhAbs_Flt;
	float32 XI_PhAct_Flt;
	float32 XI_PhRct_Flt;
	float32 XI_PhAct_Flt2;
	float32 XI_PhRct_Flt2;
	float32 XI_PhAbs_Flt;
	float32 XP_3Ph_Flt;
	float32 XQ_3Ph_Flt;
	cfloat32 XI_PhDQ_Flt;

	/*ACCLDA*/
	//�����޷�
	Uint16 S_IPhClTrsAv;
	float32 WU_IPhClTrs;/*3-phase output load voltage reference manipulation,transient phase current control*/
	float32 WU_IPhClTrs_Flt;
	Uint16 B_LimAct;
	float32 WU_IPhClRms;
	float32 XI_Ph1Squ;
	float32 XI_Ph2Squ;
	float32 XI_Ph3Squ;
	Uint16 XX_CntPh1Rms;
	Uint16 XX_CntPh2Rms;
	Uint16 XX_CntPh3Rms;
	float32 XI_Ph1Rms;
	float32 XI_Ph2Rms;
	float32 XI_Ph3Rms;
	float32 XI_Ph1Rms_Flt;
	float32 XI_Ph2Rms_Flt;
	float32 XI_Ph3Rms_Flt;

	/*UFCODA*/
	Uint16 S_3PhOvMd;
	cfloat32 WU_3PhSec;
	cfloat32 XZ_3PhFiNd;
	cfloat32 XZ_3PhFiCa;
	cfloat32 XZ_3PhTf;
	cfloat32 WU_3PhPm;
	cfloat32 WU_3PhPmAB;
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

	/*ACLS*/
	Uint16 B_IPhClTmWnd1Fl;
	Uint16 B_IPhClRmsTmFl;

	/*OVPT*/
	Uint16 C_OvpFcTs;
	Uint16 A_OvpFcTsOk;
	float32 XX_Duty4;

	/*BTCP*/
	Uint16 A_BtCpAv;
	Uint16 A_OvpAv;
	Uint16 S_OvpEn;
	float32 XX_Duty5;

	/**/
	Uint16 B_DspOvLdFl;
	Uint16 S_DspWdAlm;
	Uint16 S_DspFpgaComFl;
	Uint16 B_DspStkSvFl;

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
	Uint16 B_RqAuSzPrBc;	//ͬ��ʧ�ܹ���

	/*UF3PhCmp*/
	float32 WF_UF3PhCmp;
	float32 WU_UF3PhCmp;

	/*IPhClPsTrs 4ms*/
	float32 WI_PhActDsp;
	float32 WI_PhRctDsp;

	/*CvOpSaSq*/
	Uint16 NX_SqStCvOpSa;
	Uint16 C_Ck3PhGduFb;
	Uint16 C_CdAuLdCt;
	Uint16 C_CvOpSa;
	Uint16 C_AuSz;	//��ʼͬ��
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
	Uint16 B_EnU3PhCl;	//��ʼ�ջ�
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

	float32 PF_IRQBMax; //Dsp�ⲿ�ж����Ƶ�ʣ�������С���ʱ�䣬��������ʱ��

	float32 PX_DdCmpFa;
	float32 PI_DdCmpFu;
	float32 PI_DdCmpDs;

	float32 PX_3PhClRtHgh;
	float32 PX_3PhClRtLow;

	/**/
	float32 PZ_3PhFiNdRe; //	0,078 �˲���е���
	float32 PZ_3PhFiNdIm; //	0,207�˲���е翹
	float32 PZ_3PhFiCaIm; //	-5,47 �˲����ݵ翹���㵽һ�β�
	float32 PZ_3PhTfRe; //		0
	float32 PZ_3PhTfIm; //		0

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
//		Uint16 L_DsPlElm3PhMod;

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

	/*CvOpSaSq*/
	float32 PU_3PhIdlCmp;
	float32 PU_3PhActCmp;

	/*CvOpSa*/
	Uint16 L_PrlAcm;	//	TRUE

};

/**/
extern volatile struct Dsp_Data DspData;

/*DSP*/
/*IRQB*/
//���
extern void DspInit(void);

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif
