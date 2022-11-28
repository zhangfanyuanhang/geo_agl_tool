#pragma once

#ifndef MATH_DEFINES_H
#define MATH_DEFINES_H

#include <stdint.h>
#include <math.h>

namespace gte {

	const double_t M_PI = 3.1415926;
	const double_t ZOOM_IN = 1000.0;
	const double_t ZOOM_OUT = 1.0 / ZOOM_IN;


	enum ORDER {
		OrderUndetermined = 0,
		ClockWise = 1,
		CounterClockWise = 2,
	};
}


#endif // !MATH_DEFINES_H

