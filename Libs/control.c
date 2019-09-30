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
/*
void PI_CONTROLLER(TYPE_PI_CONTROLLER *data) {
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
*/

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
/*
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
*/

/**/
/*
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
*/

/**/
/*
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
*/

/**/
/*
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
*/

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
