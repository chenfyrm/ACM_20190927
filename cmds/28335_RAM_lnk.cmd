
MEMORY
{
PAGE 0 :
	BEGIN_M0           : origin = 0x000000,     length = 0x000002
   	L01234567SARAM     : origin = 0x008000,     length = 0x006000

   	CSM_RSVD           : origin = 0x33FF80,     length = 0x000076
   	BEGIN_FLASH        : origin = 0x33FFF6,     length = 0x000002
   	CSM_PWL            : origin = 0x33FFF8,     length = 0x000008
   	ADC_CAL            : origin = 0x380080,     length = 0x000009
   	OTP                : origin = 0x380400,     length = 0x000400
   	IQTABLES           : origin = 0x3FE000,     length = 0x000B50
   	IQTABLES2          : origin = 0x3FEB50,     length = 0x00008C
   	FPUTABLES          : origin = 0x3FEBDC,     length = 0x0006A0
   	BOOTROM            : origin = 0x3FF27C,     length = 0x000D44
   	RESET              : origin = 0x3FFFC0,     length = 0x000002
	VECTORS            : origin = 0x3FFFC2,     length = 0x00003E

PAGE 1 :
	BOOT_RSVD          : origin = 0x000002,     length = 0x00004E
	M0SARAM            : origin = 0x000050,     length = 0x0003B0
 	M1SARAM            : origin = 0x000400,     length = 0x000400
	RAM_L4L5L6L7       : origin = 0x00E000, 	length = 0x002000     /* on-chip RAM block L4 */
 	ZONE7DATA          : origin = 0x200000,     length = 0x040000
}

SECTIONS
{
/* Program memory (PAGE 0) sections */
    ramfuncs		   : > L01234567SARAM,      PAGE = 0
    .text              : > L01234567SARAM,      PAGE = 0
    .econst            : > L01234567SARAM,      PAGE = 0
    .cinit             : > L01234567SARAM,      PAGE = 0
    .pinit             : > L01234567SARAM,      PAGE = 0
    .switch            : > L01234567SARAM,      PAGE = 0

    dclfuncs           :> L01234567SARAM,       PAGE = 0

    IQmath             : > L01234567SARAM,      PAGE = 0
    IQmathTables       : > IQTABLES,            PAGE = 0,           TYPE = NOLOAD
    IQmathTables2      : > IQTABLES2,           PAGE = 0,           TYPE = NOLOAD
    FPUmathTables      : > FPUTABLES,           PAGE = 0,           TYPE = NOLOAD
	.adc_cal           : load = ADC_CAL,        PAGE = 0,           TYPE = NOLOAD

    .reset             : > RESET,               PAGE = 0,           TYPE = DSECT
    csm_rsvd           : > CSM_RSVD             PAGE = 0,           TYPE = DSECT
    csmpasswds         : > CSM_PWL              PAGE = 0,           TYPE = DSECT

/* Data Memory (PAGE 1) sections */
    .stack             : > M1SARAM,             PAGE = 1
    .ebss              : > RAM_L4L5L6L7,        PAGE = 1
    .esysmem           : > M0SARAM,             PAGE = 1

/* User Defined Sections */
    codestart          : > BEGIN_M0,            PAGE = 0
    ZONE7SARAM         : > ZONE7DATA,           PAGE = 1
}


/*
//===========================================================================
// End of file.
//===========================================================================
*/
