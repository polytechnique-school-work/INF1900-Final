#include "Robot.hpp"

LightManager& Robot::getLights() { return this->lights; }

Sensor& Robot::getSensor() { return this->sensor; }

WheelManager& Robot::getWheels() { return this->wheels; }