#include <math.h>
#include <avr/io.h>
#include "stdio.h"

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
    SVG(){
        taille = 0;
        tailleTotale = 0;
        adresse = 0;
        for(int8_t i = 3; i > -1; i--){
            for (uint8_t j = 0; j < 8; j++){           
                uint8_t x = 19 + 11 * j;
                uint8_t y = 12 + 11 * i;
                points[nbPoints++] = Point(j+ (3-i)*8 + 1, x, y);
            }
        }
    }

    void init();
private:
    Point points[32];
    uint8_t nbPoints;

    Point pointsVisites[8];
    uint8_t nVisites;

    uint8_t taille;
    uint16_t tailleTotale;
    uint16_t adresse;
};