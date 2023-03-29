#pragma once
#include <Clock/Clock.hpp>
#include <Light/LightManager.hpp>
#include <Sensor/Sensor.hpp>
#include <Wheel/WheelManager.hpp>
#include <avr/io.h>

class Robot {
public:
    Robot(WheelManager wm, LightManager lm, Sensor s)
        : wheelManager(wm), lightManager(lm), sensor(s) {}

    WheelManager& getWheelManager();

    LightManager& getLightManager();

    Sensor& getSensor();

private:
    WheelManager wheelManager;
    LightManager lightManager;
    Sensor sensor;
};