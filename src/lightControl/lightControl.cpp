#include "ligthControl.h"

LightControl::LightControl()
{
    this->lightControlConfigured = false;
    this->_lightControlCfg = { 0,
                               0,
                               {0, 0},
                               0,
                               {0, 0, 0, 0,
                                0, 0, 0, 0,
                                0, 0, 0, 0,
                                0, 0, 0, 0,
                                0, 1, 2, 3,
                                4, 5, 9, 13,
                                14, 15, 15, 16,
                                18, 20, 22, 24,
                                28, 32, 36, 40,
                                44, 46, 50, 56,
                                62, 68, 74, 80,
                                86, 92, 98, 100,
                                100, 100, 100, 100,
                                100, 100, 100, 100,
                                100, 94, 88, 82,
                                76, 70, 64, 58,
                                52, 46, 40, 36,
                                32, 28, 24, 20,
                                18, 17, 16, 15,
                                14, 13, 12, 11,
                                10, 10, 5, 5,
                                5, 4, 3, 2,
                                1, 0, 0, 0,
                                0, 0, 0, 0}
    };
}

void LightControl::proecessLightControl()
{
}

void LightControl::correctLightLevel()
{
}
