/*
 * control.c
 *
 *  Created on: 2019-9-27
 *      Author: 700363
 */
#include "math.h"

#include "UserDefs.h"
#include "UserMath.h"

#include "control.h"

/**/
void IIRFilter_2nd(struct IIRFILTER_2ND *data) {
	data->Out = data->b0 * data->In + data->b1 * data->oldIn1
			+ data->b2 * data->oldIn2 - data->a1 * data->oldOut1
			- data->a2 * data->oldOut2;
	/***********************************/
	data->oldIn2 = data->oldIn1;
	data->oldIn1 = data->In;
	data->oldOut2 = data->oldOut1;
	data->oldOut1 = data->Out;
}

/***************************
 *
 *
 *
 ****************************/
void AdaptIIRNotchFilter(struct IIRFILTER_2ND *data, float32 W0, float32 Ts) {
	data->b0 = 1.0;
	data->b1 = -2.0 * cos(W0 * Ts);
	data->b2 = 1.0;
//	data->a1 = (1 - W0 * Ts / 4) * data->b1;
	data->a1 = -2+ W0 * Ts / 2;
	data->a2 = pow((1 - W0 * Ts / 4), 2.0);
	if ((data->b1 + 2.0) < 0.0001) {
		data->In *= (1.0 + data->a1 + data->a2)*10000;
	} else {
		data->In *= (1.0 + data->a1 + data->a2) / (2.0 + data->b1);
	}
	IIRFilter_2nd(data);
}


/**/
void PI_CONTROLLER(struct PI_CONTROLLER *data) {
	//proportional term
	data->up = data->Kp * (data->Ref - data->Fbk);

	//integral term
	data->ui =
			(data->Out == data->v1) ?
					(data->Ki * (data->Ref - data->Fbk) + data->i1) : data->i1;
	data->i1 = data->ui;

	//control output
	data->v1 = data->up + data->ui;
	data->Out = (data->v1 > data->Umax) ? data->Umax : data->v1;
	data->Out = (data->Out < data->Umin) ? data->Umin : data->Out;
}

/*
 * 过调制
 * */
float32 OvMd(float32 M1) {

	//[0 1/sqrt(3) 0.579 0.6038 0.6057]
	//[0 1/sqrt(3) 0.58  0.6389 0.6667]

	float32 M;

	if (M1 < 0)
		M = 0;
	else if (M1 < ONEbySQRT3)
		M = M1;
	else if (M1 < 0.579)
		M = ONEbySQRT3
				+ (0.58 - ONEbySQRT3) / (0.579 - ONEbySQRT3)
						* (M1 - ONEbySQRT3);
	else if (M1 < 0.6038)
		M = 0.58 + (0.6389 - 0.58) / (0.6038 - 0.579) * (M1 - 0.579);
	else if (M1 < 0.6057)
		M = 0.6389 + (0.6667 - 0.6389) / (0.6057 - 0.6038) * (M1 - 0.6038);
	else
		M = 0.6667;

	return M;
}

/*
 * 空间电压矢量调节
 * */
void SVPWM(volatile float32 *DutyA, volatile float32 *DutyB,
		volatile float32 *DutyC, float32 _3PhAl, float32 _3PhBe) {
	float32 a, b, c, min, max, NrmFa, Cml;

	a = _3PhAl;
	b = -_3PhAl * 0.5 + _3PhBe * SQRT3byTWO;
	c = -_3PhAl * 0.5 - _3PhBe * SQRT3byTWO;

	min = Min(a, Min(b, c));
	max = Max(a, Max(b, c));

	NrmFa = Max(1.0, max - min);
	Cml = (max + min) * (-0.5);

	*DutyA = (a + Cml) / NrmFa + 0.5;
	*DutyB = (b + Cml) / NrmFa + 0.5;
	*DutyC = (c + Cml) / NrmFa + 0.5;
}

float32 Delay1(float32 In, volatile float32* PreIn) {
	float32 v01;
	v01 = *PreIn;
	*PreIn = In;

	return v01;
}

float32 DelayN(float32 In, volatile float32* PreInArr32, Uint16 N) {
	return *(PreInArr32);
}

/**/
void LowPass(volatile float32 *Flt, float32 Src, float32 TsPerT1) {
	*Flt = (*Flt + Src * TsPerT1) / (1.0 + TsPerT1);
}



void RmsClc(volatile float32 *rms, float32 Src, Uint16 N,
		volatile float32 *Square, volatile Uint16 *cnt) {
	*Square += Src * Src / N;
	*cnt += 1;
	if (*cnt >= N) {
		*rms = sqrt(*Square);
		*Square = 0;
		*cnt = 0;
	}
}

float32 FKG4(float32 X, float32 X1, float32 Y1, float32 X2, float32 Y2,
		float32 X3, float32 Y3, float32 X4, float32 Y4) {
	float32 Y;
	if (X < X1)
		Y = Y1;
	else if (X < X2)
		Y = Y1 + (Y2 - Y1) * (X - X1) / Max((X2 - X1), 0.00001);
	else if (X < X3)
		Y = Y2 + (Y3 - Y2) * (X - X2) / Max((X3 - X2), 0.00001);
	else if (X < X4)
		Y = Y3 + (Y4 - Y3) * (X - X3) / Max((X4 - X3), 0.00001);
	else
		Y = Y4;

	return Y;
}

void RAMP2(volatile float32 *Y, float32 X, float32 Dr, float32 Df, float32 Init,
		Uint16 Set, Uint16 Hold) {
	float32 Yinc, Ydec;
	if (!Hold) {
		if (Set) {
			*Y = Init;
		} else {
			Yinc = *Y + fabs(Dr);
			Ydec = *Y - fabs(Df);

			if (X > Yinc) {
				*Y = Yinc;
			} else if (X < Ydec) {
				*Y = Ydec;
			} else {
				*Y = X;
			}
		}
	}
}

void RAMP(volatile float32 *Y, float32 X, float32 TsPerTr, float32 TsPerTf,
		float32 Init, Uint16 Set, Uint16 Hold, float32 Max) {
	float32 Yinc, Ydec;
	if (!Hold) {
		if (Set) {
			*Y = Init;
		} else {
			Yinc = *Y + fabs(Max) * Min(TsPerTr, 1.0);
			Ydec = *Y - fabs(Max) * Min(TsPerTf, 1.0);

			if (X > Yinc) {
				*Y = Yinc;
			} else if (X < Ydec) {
				*Y = Ydec;
			} else {
				*Y = X;
			}
		}
	}

}

void INTEGR(volatile float32 *Y, float32 X, float32 TsPerT1, float32 Init,
		float32 Max, float32 Min, Uint16 Set, Uint16 Hold) {
	if (!Hold) {
		if (Set) {
			*Y = Init;
		} else {
			*Y = *Y + X * TsPerT1;
		}
	}

	*Y = Limit(*Y, Min, Max);
}

void PIREG(float32 Ref, float32 Fbk, float32 Kp, float32 TsPerT1, float32 Init,
		Uint16 Set, Uint16 Reset, float32 Max, float32 Min, volatile float32 *Y,
		volatile Uint16 *Yi) {
	float32 Err, Yp, Out;
	Err = Ref - Fbk;
	Yp = Kp * Err;
	if (Reset) {
		Yp = 0.0;
		*Yi = 0.0;
	} else if (Set) {
		*Yi = Init - Yp;
	} else {
		*Yi += Yp * Limit(TsPerT1, 0.0, 1.0);
	}

	Out = Yp + *Yi;
	if (Max < Min) {
		Out = 0.0;
	} else {
		if (Out <= Min) {
			Out = Min;
			*Yi = Out - Yp;
		} else if (Out >= Max) {

			Out = Max;
			*Yi = Out - Yp;

		}

	}
	*Y = Out;

}

/**/
Uint16 RTRIG(Uint16 In, volatile Uint16* PreIn) {
	Uint16 logic = FALSE;
	if (In) {
		if (!(*PreIn)) {
			logic = TRUE;
		}
	}
	*PreIn = In;

	return logic;
}

/**/
Uint16 FTRIG(Uint16 In, volatile Uint16* PreIn) {
	Uint16 logic = FALSE;
	if (!In) {
		if (*PreIn) {
			logic = TRUE;
		}
	}
	*PreIn = In;

	return logic;
}

/*
 * RS Flip Flop with reset dominant
 * */
void RS(volatile Uint16* Q, Uint16 Set, Uint16 Reset) {
	if (Reset) {
		*Q = FALSE;
	} else {
		if (Set)
			*Q = TRUE;
	}
}

/*
 * SR Flip Flop with set dominant
 * */
void SR(volatile Uint16* Q, Uint16 Set, Uint16 Reset) {
	if (Set) {
		*Q = TRUE;
	} else {
		if (Reset)
			*Q = FALSE;
	}
}

/*
 *
 * */

Uint16 DLYON_N(Uint16 In, Uint16 N, volatile TYPE_DLYONOFF_N* data) {
	Uint16 logic = FALSE;
	if (In) {
		if (!data->logic.bit.PreLogic) {
			data->Cnt = N;
		}
		if (data->Cnt > 0) {
			data->Cnt--;
		} else {
			logic = TRUE;
		}
	}
	data->logic.bit.PreLogic = In;

	return logic;
}


/**/

extern Uint16 DLYOFF_N(Uint16 In, Uint16 N, volatile TYPE_DLYONOFF_N* data) {
	Uint16 logic = TRUE;
	if (!In) {
		if (data->logic.bit.PreLogic) {
			data->Cnt = N;
		}
		if (data->Cnt > 0) {
			data->Cnt--;
		} else {
			logic = FALSE;
		}
	}
	data->logic.bit.PreLogic = In;

	return logic;
}


/**/

Uint16 DLYON_T(Uint16 In, float32 T, volatile TYPE_DLYONOFF_T* data, float32 CT) {
	Uint16 logic = FALSE;
	if (In) {
		if (!data->PreIn) {
			data->Tm = T;
		}
		if (data->Tm > 0) {
			data->Tm -= CT;
		} else {
			logic = TRUE;
		}
	}
	data->PreIn = In;

	return logic;
}


/**/

Uint16 DLYOFF_T(Uint16 In, float32 T, volatile TYPE_DLYONOFF_T* data,
		float32 CT) {
	Uint16 logic = TRUE;
	if (!In) {
		if (data->PreIn) {
			data->Tm = T;
		}
		if (data->Tm > 0) {
			data->Tm -= CT;
		} else {
			logic = FALSE;
		}
	}
	data->PreIn = In;

	return logic;

}


/**/
/*
Uint16 MONO(Uint16 In, Uint16 N, volatile TYPE_DLYONOFF_N* data) {
	Uint16 logic = FALSE;
//	if (RTRIG(In, &data->logic.bit.) || FTRIG(In, &data->logic)) {
//		data->Cnt = N;
//		if (data->Cnt > 0) {
//			data->Cnt--;
//			logic = TRUE;
//		}
//	}

	return logic;
}
*/
