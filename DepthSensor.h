#pragma once

#include <MS5837.h>
class DepthSensor
{
public:
    static void init();
    static float get_depth();
private:
    static DepthSensor &inst();
    MS5837 sensor;
    long long time_update = 0;
    float depth = 0;
};

