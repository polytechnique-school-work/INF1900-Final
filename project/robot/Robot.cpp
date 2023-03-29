#include "Robot.hpp"

WheelManager& Robot::getWheelManager() { return wheelManager; }

LightManager& Robot::getLightManager() { return lightManager; }

Sensor& Robot::getSensor() { return sensor; }

SoundPlayer& Robot::getSoundPlayer() { return soundPlayer; }

uint16_t Robot::getX() { return this->x; }

uint16_t Robot::getY() { return this->y; }

void Robot::setX(uint16_t value) { this->x = value; }

void Robot::setY(uint16_t value) { this->y = value; }

const uint8_t Robot::getSpeed() { return this->speed; }

const uint16_t Robot::getWaitTurnDuration() { return this->speed; }

HeadDirection Robot::getHeadDirection() { return this->headDirection; }

void Robot::setHeadDirection(HeadDirection head) { this->headDirection = head; }