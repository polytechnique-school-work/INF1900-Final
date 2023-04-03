#include <math.h>

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

