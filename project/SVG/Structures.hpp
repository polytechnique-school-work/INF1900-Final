#define F_CPU 8000000UL

#include <math.h>
#include <avr/io.h>
#include <string.h>
#include "Logger/Logger.hpp"
#include "Clock/Clock.hpp"
#include "Light/LightManager.hpp"
#include <stdio.h>
#include "Memory/memoire_24.h"
#include <util/delay.h>

class Point
{
public:
    Point(uint8_t index = 0, uint8_t x = 0, uint8_t y = 0) : index_(index), x_(x), y_(y) {};

    uint8_t getIndex() {
        return index_;
    }
    uint8_t getX() {
        return x_;
    }
    uint8_t getY() {
        return y_;
    }

    bool operator==(Point autre) {
        bool xEqual = this->x_ == autre.getX();
        bool yEqual = this->y_ == autre.getY();
        return xEqual && yEqual;
    }
private:
    uint8_t index_;
    uint8_t x_;
    uint8_t y_;
};

class Vector
{
public:
	Vector(int8_t x = 0, int8_t y = 1) : x_(x), y_(y) 
	{
		norme_ = sqrt(pow(x_, 2) + pow(y_, 2));
		cosinus_ = x_ / norme_;
	}

    int8_t getX() {
        return x_;
    }

    int8_t getY() {
        return y_;
    }

	float getACos() {
		return acos(cosinus_);
	}

    float getNorme() {
        return norme_;
    }

private:
	int8_t x_;
	int8_t y_;
	float norme_;
	float cosinus_;
};

class Cosinus
{
public:
    Cosinus(int8_t index = 0, float cos = 0.0) : index_(index), cos_(cos) {

    }

    int8_t getIndex() {
        return index_;
    }

    float getCos() {
        return cos_;
    }
private:

	int8_t index_;
	float cos_;
};

class SVG
{
public:
    SVG(Clock &clock, LightManager &light){
        this->clock = &clock;
        this->light = &light;

        previousTimestamp = clock.getTimestamp();
        color = Color::OFF;

        nVisites = 0;
        nbPoints = 0;
        nContour = 0;

        crc = 0xFFFFFFFF;
    }

    void transmettreMessage(const char* message);

    uint16_t calculAire();

    void transmitSVG();

    void sortArray(Cosinus cosinus[], uint8_t& nCosinus);

    void init();

    void ecrireRectangles();

    void trouverPointsVisites();

    void makeCircles();

    void algorithmeGraham();

    void makePolygon();

    void visiterPoint(uint8_t indice){
        if (indice!=0){
            indicesVisites[nVisites++] = indice;
        }
    }

    uint32_t crc; 
private:
    Clock* clock = nullptr;
    uint32_t previousTimestamp;

    LightManager* light = nullptr;
    Color color;

    Point points[32];
    uint8_t nbPoints;

    Point pointsVisites[8];
    uint8_t nVisites;

    Point pointsContour[8];
    uint8_t nContour;

    uint8_t indicesVisites[8];

};