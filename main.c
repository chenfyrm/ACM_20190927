/*
 * main.c
 *
 *  Created on: 2019-9-27
 *      Author: 700363
 */
#include "project.h"

void main(void)
{
	InitSysCtrl();
	InitGpio();
	InitXintf();

	DELAY_US(10000L);

	DINT;
	IER = 0x0000;
	IFR = 0x0000;
	InitPieCtrl();
	InitPieVectTable();

	EALLOW;
	//	PieVectTable.XINT1 = &DPRAM_isr;
	PieVectTable.XINT1 = &DPRAM_isr;
	EDIS;

	InitCpuTimers();
	InitXInterrupt();
	IER = M_INT1;
	PieCtrlRegs.PIEIER1.bit.INTx4 = 1;

	EINT;
	ERTM;

	while (1) {

	}
}
