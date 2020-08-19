#include "agrobotHelpers.h"


void byteArrToStr(uint8_t* arr, unsigned int len, char outStr[])
{
  //char outStr[len * 2];
  for (unsigned int i = 0; i < len; i++)
  {
    uint8_t n1 = (arr[i] >> 4) & 0x0F;
    uint8_t n2 = (arr[i] >> 0) & 0x0F;
    outStr[i * 2 + 0] = n1 < 0xA ? '0' + n1 : 'A' + n1 - 0xA;
    outStr[i * 2 + 1] = n2 < 0xA ? '0' + n2 : 'A' + n2 - 0xA;
  }
 // outStr[len * 2] = '\0';
 // return outStr;
}




void generateWhoAmi()
{


}

double mapDouble(double x, double inMin, double inMax, double outMin, double outMax)
{
  return (x-inMin) * (outMax - outMin) / (inMax - inMin) + outMin;
}

double valueToPercentsOf(double inp, double maxVal)
{
  return 100 / (maxVal /inp);
  
}
