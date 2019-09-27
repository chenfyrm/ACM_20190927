/*
 * complex.h
 *
 *  Created on: 2019-9-27
 *      Author: 700363
 */

#ifndef COMPLEX_H_
#define COMPLEX_H_

typedef struct {
	float32 re;
	float32 im;
} cfloat32;

extern void CPLX2FRAC(volatile float32 *Re, volatile float32 *Im, cfloat32 Z);
extern cfloat32 FRAC2CPLX(float32 Re, float32 Im);
extern cfloat32 CPLXMOV(cfloat32 Z);
extern cfloat32 CPLXCONJ(cfloat32 Z);
extern cfloat32 CPLXMULT(cfloat32 Z1, cfloat32 Z2);
extern cfloat32 CPLXMULT_SHFT(cfloat32 Z1, cfloat32 Z2, int32 m);
extern float32 CPLXNORM(cfloat32 Z);
extern cfloat32 CPLXSCA(cfloat32 Z1, float32 a);
extern cfloat32 CPLXSCA_SHFT(cfloat32 Z1, float32 a, int32 m);
extern cfloat32 CPLXSHFT(cfloat32 Z, int32 m);
extern cfloat32 CPLXSUB(cfloat32 Z1, cfloat32 Z2);
extern cfloat32 CPLXADD(cfloat32 Z1, cfloat32 Z2);
extern cfloat32 _PREVCPLX(cfloat32 Z);
extern cfloat32 CPLXDIVSCA(cfloat32 Z1, float32 F, int32 m);
extern cfloat32 CPLXDIV(cfloat32 Z1, cfloat32 Z2);
extern void CPLX2POL(volatile float32 *r, volatile float32 *fi,
		volatile cfloat32 Z);
extern cfloat32 PH3TOCPLX(float32 a, float32 b, float32 c);
extern void CPLXTO3PH(volatile float32 *a, volatile float32 *b,
		volatile float32 *c, cfloat32 Z);
extern cfloat32 POL2CPLX(float32 r, float32 fi);

#endif /* COMPLEX_H_ */
