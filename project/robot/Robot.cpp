#include "Robot.hpp"

WheelManager& Robot::getWheelManager() { return wheelManager; }

LightManager& Robot::getLightManager() { return lightManager; }

Sensor& Robot::getSensor() { return sensor; }