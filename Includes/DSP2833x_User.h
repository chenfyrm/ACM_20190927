// ------------------------------------------------------------------------
//          Copyright (C) 2010 Texas Instruments, Incorporated.
//                          All Rights Reserved.
// ==========================================================================
//
// FILE:   DSP2833x_User.h
//
// TITLE:  Prototypes and Definitions for the user system
//
//###########################################################################
// $TI Release: C28x Floating Point Unit Library V1.30 $
// $Release Date: January 01, 2018 $
//###########################################################################

#ifndef DSP2833x_USER_H
#define DSP2833x_USER_H

#ifdef __cplusplus
extern "C" {
#endif

//===================================================================================
#define F_150M 150.0e6
#define _150M 6.66666667e-9 

#define	RFFT_STAGES	8
#define	RFFT_SIZE	(1 << RFFT_STAGES)

#define ClrEPwm1Timer() EPwm1Regs.TBCTR=0
#define StopEPwm1Timer()  EPwm1Regs.TBCTL.bit.CTRMODE=3
#define StartEPwm1Timer() EPwm1Regs.TBCTL.bit.CTRMODE=0
//==========================================================
#define EnScibTxData() ScibRegs.SCICTL1.bit.TXENA=1
#define DsScibTxData() ScibRegs.SCICTL1.bit.TXENA=0
//===========================================================
#define SetRstAD1() GpioDataRegs.GPBSET.bit.GPIO59=1
#define ClrRstAD1() GpioDataRegs.GPBCLEAR.bit.GPIO59=1
//===========================================================
#define TX485()     GpioDataRegs.GPASET.bit.GPIO9=1
#define RX485()     GpioDataRegs.GPACLEAR.bit.GPIO9=1
//===========================================================
#define   C_SIN45           0.70721358
#define   C_COS60           0.5                 //cos60
#define   C_SIN60           0.86602540      	//sin60
#define   C_32COEF          0.81649658      	//sqrt(2/3)
#define   C_23COEF          1.22474487      	//sqrt(3/2)
#define	  C_2SQRT	        1.41421356      	//sqrt(2)
#define	  C_13SQRT          0.57735027      	//sqrt(1/3)
//*********************电压环用到的常量*********************************
#define UDC_DELT 	        0.000078125	//对应9.375KHz delt_t , 每隔0.0001067s PI调节一次
//**********************谐波电流计算************************************
#define Tri_wave_amp        2925  //3000
#define ModuWaveLimit_High  5450 //5850  //7500    //控制器输出限幅，由载波幅值和死区决定
#define ModuWaveLimit_Low   400//-5850 //-7500
#define AddSampleCount      6             //同时扩展一个周期的采样点数和超前点数

struct FFT_DATA
{
	float DC;
	float F;
	float th5;
	float th7;
	float th5_7;
	float th11;
	float th13;
	float th11_13;
	float H;
	float THD;
};
struct ABC
{
	float a;
	float b;
	float c;
	float n;
};

struct  flagsci_BITS {        // bit    
   Uint16 Recv_byt:1;         // 0           
   Uint16 Overtime:1;   // 1     
   Uint16 Keyrunorstp:1;       // 2   
   Uint16 rsvd1:13;       // 15:3        
}; 
union flagsci_REG {
   Uint16              all;
   struct flagsci_BITS  bit;
};

extern volatile struct flagsci_BITS flagsci;//TRSCI
extern int16 paramet[170];//TRSCI
extern Uint16 scitx_sta;//TRSCI
extern Uint16 SW_ID;

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif   // - end of DSP2833x_USER_H

//===========================================================================
// End of file.
//===========================================================================

