/*
 * control.h
 *
 *  Created on: 2019-9-27
 *      Author: 700363
 */

#ifndef CONTROL_H_
#define CONTROL_H_



struct IIRFILTER_2ND{
	float32 In;				//input
	float32 Out;			//output
	float32 a1;				//param
	float32 a2;
	float32 b0;
	float32 b1;
	float32 b2;
	float32 oldIn1;				//state
	float32 oldIn2;
	float32 oldOut1;
	float32 oldOut2;
} ;

#define IIRFILTER_2ND_DEFAULTS {		\
	0.0, 		\
	0.0, 		\
	0.0, 		\
	0.0,	\
	0.0,	\
	0.0,	\
	0.0, 	\
	0.0,	\
	0.0, 	\
	0.0,	\
	0.0,	\
	}

void IIRFilter_2nd(struct IIRFILTER_2ND *data);
void AdaptIIRNotchFilter(struct IIRFILTER_2ND *data, float32 W0,
		float32 Ts);

//
struct PI_CONTROLLER{
	float32 Ref;   			// Input: reference set-point
	float32 Fbk;   			// Input: feedback
	float32 Out;   			// Output: controller output
	float32 Kp;				// Parameter: proportional loop gain
	float32 Ki;			    // Parameter: integral gain
	float32 Umax;			// Parameter: upper saturation limit
	float32 Umin;			// Parameter: lower saturation limit
	float32 up;				// Data: proportional term
	float32 ui;				// Data: integral term
	float32 v1;				// Data: pre-saturated controller output
	float32 i1;				// Data: integrator storage: ui(k-1)
	float32 w1;				// Data: saturation record: [u(k-1) - v(k-1)]
} ;

#define PI_CONTROLLER_DEFAULTS {		\
	0.0, 		\
	0.0, 		\
	0.0, 		\
	1.0,	\
	0.0,	\
	1.0,	\
	-1.0, 	\
	0.0,	\
	0.0, 	\
	0.0,	\
	0.0,	\
	1.0 	\
	}

void PI_CONTROLLER(struct PI_CONTROLLER *data);

float32 OvMd(float32 M1);
void SVPWM(volatile float32 *DutyA, volatile float32 *DutyB,
		volatile float32 *DutyC, float32 _3PhAl, float32 _3PhBe );



float32 Delay1(float32 In, volatile float32* PreIn);
float32 DelayN(float32 In, volatile float32* PreInArr32, Uint16 N);
void LowPass(volatile float32 *Flt, float32 Src, float32 TsPerT1);

void RmsClc(volatile float32 *rms, float32 Src, Uint16 N,
		volatile float32 *Square, volatile Uint16 *cnt);
void RAMP2(volatile float32 *Y, float32 X, float32 Dr, float32 Df,
		float32 Init, Uint16 Set, Uint16 Hold);
void RAMP(volatile float32 *Y, float32 X, float32 TsPerTr,
		float32 TsPerTf, float32 Init, Uint16 Set, Uint16 Hold, float32 Max);
float32 Cycle(void);
extern void INTEGR(volatile float32 *Y, float32 X, float32 T, float32 Init,
		float32 Max, float32 Min, Uint16 Set, Uint16 Hold);
extern float32 FKG4(float32 X, float32 X1, float32 Y1, float32 X2, float32 Y2,
		float32 X3, float32 Y3, float32 X4, float32 Y4);
extern void PIREG(float32 Ref, float32 Fbk, float32 Kp, float32 TsPerT1,
		float32 Init, Uint16 Set, Uint16 Reset, float32 Max, float32 Min,
		volatile float32 *Y, volatile float32 *Yi);
extern Uint16 RTRIG(Uint16 In, volatile Uint16* PreIn);
extern Uint16 FTRIG(Uint16 In, volatile Uint16* PreIn);
extern void RS(volatile Uint16* Q, Uint16 Set, Uint16 Reset);
extern void SR(volatile Uint16* Q, Uint16 Set, Uint16 Reset);

struct LOGICAL_BITS {
	Uint16 Logic :1;
	Uint16 PreLogic :1;
	Uint16 RTrig :1;
	Uint16 FTrig :1;
	Uint16 rsvd1 :12;
};

union LOGICAL {
	Uint16 all;
	struct LOGICAL_BITS bit;
};

typedef struct DLYONOFF_N {
	union LOGICAL logic;
	Uint16 Cnt;
} TYPE_DLYONOFF_N;

typedef struct DLYONOFF_T {
	Uint16 PreIn;
	float32 Tm;
} TYPE_DLYONOFF_T;

#define DLYONOFF_DEFAULTS {\
	0,\
	0.0,\
}
extern Uint16 DLYON_N(Uint16 In, Uint16 N, volatile TYPE_DLYONOFF_N* data);
extern Uint16 DLYOFF_N(Uint16 In, Uint16 N, volatile TYPE_DLYONOFF_N* data);
extern Uint16 DLYON_T(Uint16 In, float32 T, volatile TYPE_DLYONOFF_T* data,
		float32 CT);
extern Uint16 DLYOFF_T(Uint16 In, float32 T, volatile TYPE_DLYONOFF_T* data,
		float32 CT);
extern Uint16 MONO(Uint16 In, Uint16 N, volatile TYPE_DLYONOFF_N* data);

typedef struct {
	float32 phase;	//input
	float32 alpha;	//output
	float32 beta;
	float32 Ts;	//param
	float32 w0;
	float32 K;
	float32 Ki;
	float32 oldPhase1;	//state
	float32 oldPhase2;
	float32 oldAlpha1;
	float32 oldAlpha2;
	float32 oldBeta1;
	float32 oldBeta2;
	float32 a;	//local
	float32 b;
	float32 w;
	float32 peak;
	float32 ErrF;
	float32 ComW;
} TYPE_SOGIOSGMA;

#define SOGIOSGMA_DEFAULTS {\
	0.0,\
	0.0,\
	0.0,\
	1.0/1350.0/2.0,\
	100*3.1415926,\
	1.4142135,\
	10000,\
	0.0,\
	0.0,\
	0.0,\
	0.0,\
	0.0,\
	0.0,\
	0.0,\
	0.0,\
	100*3.1415926,\
	0.0,\
	0.0,\
	0.0\
	}

extern void SOGIOSGFLL(TYPE_SOGIOSGMA *interface);

#endif /* CONTROL_H_ */
