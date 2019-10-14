/*
 * UserMath.c
 *
 *  Created on: 2019-9-30
 *      Author: 700363
 */
#include "UserDefs.h"
#include "UserMath.h"

float32 Min(float32 a, float32 b) {
	if (a <= b)
		return a;
	else
		return b;
}

float32 Max(float32 a, float32 b) {
	if (a <= b)
		return b;
	else
		return a;
}

float32 Limit(float32 x, float32 low, float32 up) {
	return Max(low, Min(x, up));
}

