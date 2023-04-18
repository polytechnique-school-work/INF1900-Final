#include "Robot.hpp"

WheelManager* Robot::getWheelManager() { return wheelManager; }

LightManager* Robot::getLightManager() { return lightManager; }

Sensor* Robot::getSensor() { return sensor; }

SoundPlayer* Robot::getSoundPlayer() { return soundPlayer; }

uint8_t Robot::getX() { return this->x; }

uint8_t Robot::getY() { return this->y; }

void Robot::setX(uint8_t value) { this->x = value; }

void Robot::setY(uint8_t value) { this->y = value; }

uint8_t Robot::getHeadDirection() { return this->headDirection; }

void Robot::setHeadDirection(uint8_t head) { this->headDirection = head; }

void Robot::incrementMemoryCount() { this->memoryCount++; }
uint8_t Robot::getMemoryCount() { return memoryCount; };