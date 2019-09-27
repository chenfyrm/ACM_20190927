#include "DSP2833x_Device.h"    
#include "DSP2833x_Examples.h"

void InitXInterrupt(void)
{
	EALLOW;
	GpioIntRegs.GPIOXINT1SEL.bit.GPIOSEL=18;
	XIntruptRegs.XINT1CR.bit.POLARITY=0;
	XIntruptRegs.XINT1CR.bit.ENABLE=1;
	EDIS;
}


