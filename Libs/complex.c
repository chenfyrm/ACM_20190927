/*
 * complex.c
 *
 *  Created on: 2019-9-27
 *      Author: 700363
 */
#include "math.h"
#include "UserDefs.h"

#include "complex.h"


void CPLX2FRAC(volatile float32 *Re, volatile float32 *Im, cfloat32 Z) {
	*Re = Z.re;
	*Im = Z.im;
}

cfloat32 FRAC2CPLX(float32 Re, float32 Im) {
	cfloat32 Z;
	Z.re = Re;
	Z.im = Im;
	return Z;
}

cfloat32 CPLXMOV(cfloat32 Z) {
	cfloat32 Z1;
	Z1.re = Z.re;
	Z1.im = Z.im;
	return Z1;
}

cfloat32 CPLXCONJ(cfloat32 Z) {
	cfloat32 Z_conj;
	Z_conj.re = Z.re;
	Z_conj.im = -Z.im;
	return Z_conj;
}

cfloat32 CPLXMULT(cfloat32 Z1, cfloat32 Z2) {
	cfloat32 Z;
	Z.re = Z1.re * Z2.re - Z1.im * Z2.im;
	Z.im = Z1.re * Z2.im + Z1.im * Z2.re;
	return Z;
}

cfloat32 CPLXMULT_SHFT(cfloat32 Z1, cfloat32 Z2, int32 m) {
	cfloat32 Z = { 0, 0 };
	return Z;
}

float32 CPLXNORM(cfloat32 Z) {
	return Z.re * Z.re + Z.im * Z.im;
}

cfloat32 CPLXSCA(cfloat32 Z1, float32 a) {
	cfloat32 Z;
	Z.re = Z1.re * a;
	Z.im = Z1.im * a;
	return Z;
}

cfloat32 CPLXSCA_SHFT(cfloat32 Z1, float32 a, int32 m) {
	cfloat32 Z = { 0, 0 };
	return Z;
}

cfloat32 CPLXSHFT(cfloat32 Z1, int32 m) {
	cfloat32 Z = { 0, 0 };
	return Z;
}

cfloat32 CPLXSUB(cfloat32 Z1, cfloat32 Z2) {
	cfloat32 Z;
	Z.re = Z1.re - Z2.re;
	Z.im = Z1.im - Z2.im;
	return Z;
}

cfloat32 CPLXADD(cfloat32 Z1, cfloat32 Z2) {
	cfloat32 Z;
	Z.re = Z1.re + Z2.re;
	Z.im = Z1.im + Z2.im;
	return Z;
}

cfloat32 _PREVCPLX(cfloat32 Z) {

	return Z;
}

cfloat32 CPLXDIVSCA(cfloat32 Z1, float32 F, int32 m) {
	cfloat32 Z = { 0, 0 };
	return Z;
}

cfloat32 CPLXDIV(cfloat32 Z1, cfloat32 Z2) {
	cfloat32 Z;
	Z.re = (Z1.re * Z2.re + Z1.im * Z2.im) / (Z2.re * Z2.re + Z2.im * Z2.im);
	Z.im = (-Z1.re * Z2.im + Z1.im * Z2.re) / (Z2.re * Z2.re + Z2.im * Z2.im);
	return Z;
}

void CPLX2POL(volatile float32 *r, volatile float32 *fi, cfloat32 Z) {
	*r = sqrt(Z.re * Z.re + Z.im * Z.im);
	*fi = fmod(atan2(Z.im, Z.re), PI2);
}

cfloat32 PH3TOCPLX(float32 a, float32 b, float32 c) {
	cfloat32 Z;
	Z.re = (a - 0.5 * (b + c)) * 2.0 / 3.0;
	Z.im = (b - c) * ONEbySQRT3;
	return Z;
}

void CPLXTO3PH(volatile float32 *a, volatile float32 *b, volatile float32 *c,
		cfloat32 Z) {
	*a = Z.re;
	*b = -Z.re * 0.5 + Z.im * SQRT3byTWO;
	*c = -Z.re * 0.5 - Z.im * SQRT3byTWO;
}

cfloat32 POL2CPLX(float32 r, float32 fi) {
	cfloat32 Z;
	Z.re = r * cos(fi);
	Z.im = r * sin(fi);
	return Z;
}

void CplxLowPass(volatile cfloat32 *Flt, cfloat32 Src, float32 TsPerT1) {
	Flt->re = (Flt->re + Src.re * TsPerT1) / (1.0 + TsPerT1);
	Flt->im = (Flt->im + Src.im * TsPerT1) / (1.0 + TsPerT1);
}
