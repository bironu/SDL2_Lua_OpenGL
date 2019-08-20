#ifndef MISC_H_
#define MISC_H_

#define _USE_MATH_DEFINES
#include <cmath>

inline double radian2degrees(double radian)
{
	return radian * 180.0 / M_PI;
}

inline double degrees2radian(double degrees)
{
	return M_PI * degrees / 180.0;
}

inline int power_of_two(int input)
{
	int value = 1;

	while ( value < input ) {
		value <<= 1;
	}
	return value;
}


#endif // MISC_H_
