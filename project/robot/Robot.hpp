#pragma once
#include <Clock/Clock.hpp>
#include <Light/LightManager.hpp>
#include <Sensor/Sensor.hpp>
#include <Wheel/WheelManager.hpp>
#include <avr/io.h>

class Robot {
public:
    Robot(WheelManager wheels, LightManager lights, Sensor sensor)
        : wheels(wheels), lights(lights), sensor(sensor) {}
    WheelManager& getWheels();
    LightManager& getLights();
    Sensor& getSensor();

private:
    WheelManager wheels;
    LightManager lights;
    Sensor sensor;
}