/*
 * control.h
 *
 *  Created on: 2019-9-27
 *      Author: 700363
 */

#ifndef CONTROL_H_
#define CONTROL_H_

extern float32 Delay1(float32 In, volatile float32* PreIn);
extern float32 DelayN(float32 In, volatile float32* PreInArr32, Uint16 N);
extern void LowPass(volatile float32 *Flt, float32 Src, float32 TsPerT1);

extern void RmsClc(volatile float32 *rms, float32 Src, Uint16 N,
		volatile float32 *Square, volatile Uint16 *cnt);
extern void RAMP2(volatile float32 *Y, float32 X, float32 Dr, float32 Df,
		float32 Init, Uint16 Set, Uint16 Hold);
extern void RAMP(volatile float32 *Y, float32 X, float32 TsPerTr,
		float32 TsPerTf, float32 Init, Uint16 Set, Uint16 Hold, float32 Max);
extern float32 Cycle(void);
extern void INTEGR(volatile float32 *Y, float32 X, float32 T, float32 Init,
		float32 Max, float32 Min, Uint16 Set, Uint16 Hold);
extern float32 FKG4(float32 X, float32 X1, float32 Y1, float32 X2, float32 Y2,
		float32 X3, float32 Y3, float32 X4, float32 Y4);
extern void PIREG(float32 Ref, float32 Fbk, float32 Kp, float32 TsPerT1,
		float32 Init, Uint16 Set, Uint16 Reset, float32 Max, float32 Min,
		volatile float32 *Y, volatile Uint16 *Yi);
extern Uint16 RTRIG(Uint16 In, volatile Uint16* PreIn);
extern Uint16 FTRIG(Uint16 In, volatile Uint16* PreIn);
extern void RS(volatile Uint16* Q, Uint16 Set, Uint16 Reset);
extern void SR(volatile Uint16* Q, Uint16 Set, Uint16 Reset);

/*
extern Uint16 DLYON_N(Uint16 In, Uint16 N, volatile TYPE_DLYONOFF_N* data);
extern Uint16 DLYOFF_N(Uint16 In, Uint16 N, volatile TYPE_DLYONOFF_N* data);
extern Uint16 DLYON_T(Uint16 In, float32 T, volatile TYPE_DLYONOFF_T* data,
		float32 CT);
extern Uint16 DLYOFF_T(Uint16 In, float32 T, volatile TYPE_DLYONOFF_T* data,
		float32 CT);
extern Uint16 MONO(Uint16 In, Uint16 N, volatile TYPE_DLYONOFF_N* data);
*/

#endif /* CONTROL_H_ */
