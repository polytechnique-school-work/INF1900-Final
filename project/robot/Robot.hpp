#pragma once
#include <Clock/Clock.hpp>
#include <Light/LightManager.hpp>
#include <Sensor/Sensor.hpp>
#include <SoundPlayer/SoundPlayer.hpp>
#include <Wheel/WheelManager.hpp>
#include <avr/io.h>

/*

    Le NORD pointe vers le haut de la table.

*/
//                              0       1         2        3        4        5        6        7
// enum class HeadDirection { NORTH, NORTHEAST, EAST, SOUTH_EAST, SOUTH, SOUTHWEST, WEAST, NORTHWEST
// };

class Robot {
public:
    Robot(WheelManager* wm, LightManager* lm, Sensor* s, SoundPlayer* sp)
        : wheelManager(wm), lightManager(lm), sensor(s), soundPlayer(sp) {}

    WheelManager* getWheelManager();

    LightManager* getLightManager();

    Sensor* getSensor();

    SoundPlayer* getSoundPlayer();

    uint8_t getHeadDirection();
    void setHeadDirection(uint8_t head);

    uint8_t getX();
    uint8_t getY();
    void setX(uint8_t value);
    void setY(uint8_t value);

    void incrementMemoryCount();
    uint8_t getMemoryCount();

private:
    WheelManager* wheelManager;
    LightManager* lightManager;
    Sensor* sensor;
    SoundPlayer* soundPlayer;
    uint8_t x             = 0;
    uint8_t y             = 0;
    uint8_t memoryCount   = 0;
    uint8_t headDirection = 0; // Valeur par défaut à changer.
};