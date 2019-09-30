// TI File $Revision: /main/1 $
// Checkin $Date: August 18, 2006   13:46:25 $
//###########################################################################
//
// FILE:	DSP2833x_Gpio.c
//
// TITLE:	DSP2833x General Purpose I/O Initialization & Support Functions.
//
//###########################################################################
// $TI Release: DSP2833x/DSP2823x C/C++ Header Files V1.31 $
// $Release Date: August 4, 2009 $
//###########################################################################

#include "DSP2833x_Device.h"     // DSP2833x Headerfile Include File
#include "DSP2833x_Examples.h"   // DSP2833x Examples Include File

//---------------------------------------------------------------------------
// InitGpio: 
//---------------------------------------------------------------------------
// This function initializes the Gpio to a known (default) state.
//
// For more details on configuring GPIO's as peripheral functions,
// refer to the individual peripheral examples and/or GPIO setup example. 
void InitGpio(void)
{
	EALLOW;
	//Sampling period
//	GpioCtrlRegs.GPACTRL.bit.QUALPRD0 = 0x0A;//GPIO0-7
//	GpioCtrlRegs.GPACTRL.bit.QUALPRD1 = 0x0A;//GPIO8-15
	GpioCtrlRegs.GPACTRL.bit.QUALPRD2 = 0x0A;//GPIO16-23
//	GpioCtrlRegs.GPACTRL.bit.QUALPRD3 = 0x0A;//GPIO24-31
//	GpioCtrlRegs.GPBCTRL.bit.QUALPRD0 = 0x0A;//GPIO32-39
//	GpioCtrlRegs.GPBCTRL.bit.QUALPRD1 = 0x0A;//GPIO40-47
//	GpioCtrlRegs.GPBCTRL.bit.QUALPRD2 = 0x0A;//GPIO48-55
//	GpioCtrlRegs.GPBCTRL.bit.QUALPRD3 = 0x0A;//GPIO56-63

	GpioCtrlRegs.GPAMUX2.bit.GPIO30=0;		//GPIO30用于输出DSP2和DSP1标志信号 GPIO30复用为GPIO功能
	GpioCtrlRegs.GPADIR.bit.GPIO30=1;      //output
	GpioCtrlRegs.GPAPUD.bit.GPIO30=1;		//Disable pull-up


	GpioCtrlRegs.GPAMUX2.bit.GPIO18=0;		//GPIO18用于DSP2外部中断输入标志信号   GPIO18复用为GPIO功能
	GpioCtrlRegs.GPADIR.bit.GPIO18=0;       //input
	GpioCtrlRegs.GPAPUD.bit.GPIO18=0;		//Enable pull-up

	
	GpioCtrlRegs.GPAMUX2.bit.GPIO19=0;		//GPIO19用于DSP2获知RAM状态的标志信号  GPIO19复用为GPIO功能
	GpioCtrlRegs.GPADIR.bit.GPIO19=0;       //input
	GpioCtrlRegs.GPAPUD.bit.GPIO19=0;		//Enable pull-up


	EDIS;
}

//===========================================================================
// End of file.
//===========================================================================
