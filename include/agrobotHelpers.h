
#ifndef AGROBOT_HELPERS_H
#define AGROBOT_HELPERS_H
//#pragma once //TODO ??
#include <stdint.h>

void byteArrToStr(uint8_t *, unsigned int, char *);
void generateWhoAmi();
//TODO make template function
template<typename T>
T mapVal(T x, T inMin, T inMax, T outMin, T outMax)
{
    return (x-inMin) * (outMax - outMin) / (inMax - inMin) + outMin;
}

template <typename T>
T valueToPercentsOf(T inp, T maxVal)
{
    return 100 / (maxVal / inp);
}



#endif
