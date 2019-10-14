/*
 * UserDefs.h
 *
 *  Created on: 2019-9-30
 *      Author: 700363
 */

#ifndef USERDEFS_H_
#define USERDEFS_H_

#define	TWObyTHREE	  	0.66666666666667       /* 2/3 */
#define ONEbySQRT3		0.57735026918963    /* 1/sqrt(3) */
#define SQRT3byTWO   	0.86602540378444    /* sqrt(3)/2 */
#define SQRT3   		1.73205080756888    /* sqrt(3)/2 */
#define	SQRT2			1.41421356237310
#define SQRT2bySQRT3    0.816397228637413   /*sqrt(2/3)*/
#define	PI  		  	3.14159265358979
#define	PI2  		  	6.28318530717959

#ifndef NULL
#define NULL ((void*)0)
#endif

#ifndef TRUE
#define TRUE (0==0)
#endif

#ifndef FALSE
#define FALSE (0!=0)
#endif

#ifndef NOT
#define NOT !
#endif

#ifndef AND
#define AND &&
#endif

#ifndef OR
#define OR ||
#endif

#ifndef OK
#define OK 0
#endif

#ifndef ERROR
#define ERROR (-1)
#endif

#ifndef INVALID
#define INVALID 1
#endif

#ifndef FAST
#define FAST register
#endif

#ifndef IMPORT
#define IMPORT extern
#endif

#ifndef LOCAL
#define LOCAL static
#endif


/*CCS编译器实现的char为16位，所以最小计量字节也为16位*/
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

typedef unsigned int BOOL;
typedef unsigned int WORD;
typedef unsigned long DWORD;
typedef void VOID;

//typedef INT16 CC_ANALOG;
//typedef UINT8 CC_BCD4;
//typedef INT16 CC_BIFRACT200;
//typedef UINT16 CC_BITSET256[16];
//typedef UINT8 CC_BOOL;
//typedef UINT8 CC_BOOLEAN2;
//typedef BYTE CC_BYTE;
//typedef UINT32 CC_DATE;
//typedef struct dt {UINT32 date; UINT16 ms;} CC_DATE_AND_TIME;
//typedef INT32 CC_DINT;
//typedef DWORD CC_DWORD;
//typedef UINT8 CC_ENUM4;
//typedef INT32 CC_FIXED;
//typedef INT16 CC_INT;
//typedef float CC_REAL;
//typedef INT8 CC_SINT;
//typedef char CC_STRING[81];
//typedef INT32 CC_TIME;
//typedef OS_TIMEDATE48 CC_TIMEDATE48;
//typedef INT32 CC_TIME_OF_DAY;
//typedef UINT32 CC_UDINT;
//typedef UINT16 CC_UINT;
//typedef UINT16 CC_UNIFRACT;
//typedef UINT8 CC_USINT;
//typedef WORD CC_WORD;

//typedef CC_ANALOG MWT_ANALOG;
//typedef CC_BCD4 MWT_BCD4;
//typedef CC_BIFRACT200 MWT_BIFRACT200;
//typedef CC_BOOL MWT_BOOL;
//typedef CC_BOOLEAN2 MWT_BOOLEAN2;
//typedef CC_BYTE MWT_BYTE;
//typedef CC_DATE MWT_DATE;
//typedef CC_DATE_AND_TIME MWT_DATE_AND_TIME;
//typedef CC_DINT MWT_DINT;
//typedef CC_DWORD MWT_DWORD;
//typedef CC_ENUM4 MWT_ENUM4;
//typedef CC_FIXED MWT_FIXED;
//typedef CC_INT MWT_INT;
//typedef CC_REAL MWT_REAL;
//typedef CC_SINT MWT_SINT;
//typedef CC_STRING MWT_STRING;
//typedef CC_TIME MWT_TIME;
//typedef CC_TIME_OF_DAY MWT_TIME_OF_DAY;
//typedef CC_TIMEDATE48 MWT_TIMEDATE48;
//typedef CC_UDINT MWT_UDINT;
//typedef CC_UINT MWT_UINT;
//typedef CC_UNIFRACT MWT_UNIFRACT;
//typedef CC_USINT MWT_USINT;
//typedef CC_WORD MWT_WORD;

#endif /* USERDEFS_H_ */
