
#ifndef AGROBOT_HELPERS_H
#define AGROBOT_HELPERS_H
//#pragma once //TODO ?? 
 #include <stdint.h>



    void byteArrToStr(uint8_t* , unsigned int, char*);
    void generateWhoAmi();
    double mapDouble(double, double, double, double, double);
    double valueToPercentsOf(double, double);




#endif
