
MEMORY
{
PAGE 0 :
    L01234567SARAM     : origin = 0x008000,     length = 0x006000
   	FLASH_ABCDEFGH     : origin = 0x300000,     length = 0x03FF80
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
	BOOT_RSVD          : origin = 0x000400,     length = 0x000080
 	M0SARAM            : origin = 0x000000,     length = 0x000400
 	M1SARAM            : origin = 0x000480,     length = 0x000380
 	RAM_L4L5L6L7       : origin = 0x00E000, 	length = 0x002000     /* on-chip RAM block L4 */
	ZONE7DATA          : origin = 0x200000,     length = 0x040000
}


SECTIONS
{
/* Program memory (PAGE 0) sections */
   	IQmath             : > FLASH_ABCDEFGH,      PAGE = 0
   	IQmathTables       : > IQTABLES,            PAGE = 0,           TYPE = NOLOAD
   	IQmathTables2      : > IQTABLES2,           PAGE = 0,           TYPE = NOLOAD
   	FPUmathTables      : > FPUTABLES,           PAGE = 0,           TYPE = NOLOAD
	.adc_cal       	   :  load = ADC_CAL,       PAGE = 0,           TYPE = NOLOAD

   	.reset             : > RESET,               PAGE = 0,           TYPE = DSECT
   	vectors            : > VECTORS,     	    PAGE = 0,           TYPE = DSECT
   	csm_rsvd           : > CSM_RSVD,            PAGE = 0,           TYPE = DSECT
   	csmpasswds         : > CSM_PWL,             PAGE = 0,           TYPE = DSECT

/* Data Memory (PAGE 1) sections */
    .stack             : > M0SARAM,             PAGE = 1
   	.ebss              : > RAM_L4L5L6L7,        PAGE = 1
   	.esysmem           : > M1SARAM,             PAGE = 1

/* User Defined Sections */
	codestart          : > BEGIN_FLASH,         PAGE = 0
   	wddisable		   : > FLASH_ABCDEFGH,      PAGE = 0
  	copysections	   : > FLASH_ABCDEFGH,      PAGE = 0
	CodeInFlash        : > FLASH_ABCDEFGH,      PAGE = 0
	ZONE7SARAM         : > ZONE7DATA,           PAGE = 1
/* 这一段有待斟酌，确定 */
	dclfuncs           :> FLASH_ABCDEFGH,       PAGE = 0

	.cinit			   :   LOAD = FLASH_ABCDEFGH,		            PAGE = 0
                		   RUN = L01234567SARAM,                    PAGE = 0
                		   LOAD_START(_cinit_loadstart),
                		   RUN_START(_cinit_runstart),
                		   SIZE(_cinit_size)

	.const			   :   LOAD = FLASH_ABCDEFGH,  	                PAGE = 0
                		   RUN = L01234567SARAM,	                PAGE = 0
                		   LOAD_START(_const_loadstart),
                		   RUN_START(_const_runstart),
                		   SIZE(_const_size)

	.econst			   :   LOAD = FLASH_ABCDEFGH,  	                PAGE = 0
                		   RUN = L01234567SARAM,                    PAGE = 0
                		   LOAD_START(_econst_loadstart),
               			   RUN_START(_econst_runstart),
                		   SIZE(_econst_size)

	.pinit			   :   LOAD = FLASH_ABCDEFGH,  	                PAGE = 0
                		   RUN = L01234567SARAM,                    PAGE = 0
                		   LOAD_START(_pinit_loadstart),
                		   RUN_START(_pinit_runstart),
                		   SIZE(_pinit_size)

	.switch			   :   LOAD = FLASH_ABCDEFGH,  	                PAGE = 0
                		   RUN = L01234567SARAM,                    PAGE = 0
                		   LOAD_START(_switch_loadstart),
                		   RUN_START(_switch_runstart),
                		   SIZE(_switch_size)

	.text			   :   LOAD = FLASH_ABCDEFGH, 		            PAGE = 0
                		   RUN = L01234567SARAM,                    PAGE = 0
                		   LOAD_START(_text_loadstart),
                		   RUN_START(_text_runstart),
                		   SIZE(_text_size)
}


/*
//===========================================================================
// End of file.
//===========================================================================
*/
