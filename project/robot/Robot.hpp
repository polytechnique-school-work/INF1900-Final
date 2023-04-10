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

enum class HeadDirection { NORTH, NORTHEAST, EAST, SOUTH_EAST, SOUTH, SOUTHWEST, WEAST, NORTHWEST };

class Robot {
public:
    Robot(WheelManager* wm, LightManager* lm, Sensor* s, SoundPlayer* sp)
        : wheelManager(wm), lightManager(lm), sensor(s), soundPlayer(sp) {}

    WheelManager* getWheelManager();

    LightManager* getLightManager();

    Sensor* getSensor();

    SoundPlayer* getSoundPlayer();

    HeadDirection getHeadDirection();
    void setHeadDirection(HeadDirection head);

    const uint8_t getSpeed();
    const uint16_t getWaitTurnDuration();

    /*
        On aura peut être pas besoin de ces elements.
    */
    uint16_t getX();
    uint16_t getY();
    void setX(uint16_t value);
    void setY(uint16_t value);

    /*
        Faire le calcul de déplacement ici.
        En gros on vient prendre le timestamp (durée de déplacement).
        On considère que tourner sur soi même ne prend pas de déplacement.
        Donc ce sera toujours des déplacements en fonction de la head.
    */
    void calculateMove(uint32_t timestamp);

private:
    WheelManager* wheelManager;
    LightManager* lightManager;
    Sensor* sensor;
    SoundPlayer* soundPlayer;
    uint16_t x;
    uint16_t y;
    const uint8_t speed           = 30;
    const double waitTurnDuration = 1000;
    HeadDirection headDirection   = HeadDirection::NORTH; // Valeur par défaut à changer.
};