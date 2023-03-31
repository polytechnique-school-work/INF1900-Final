#include <math.h>

class Point
{
public:
    Point(int index = 0, int x = 0, int y = 0) : index_(index), x_(x), y_(y) {};

    int getIndex() {
        return index_;
    }
    int getX() {
        return x_;
    }
    int getY() {
        return y_;
    }

    bool operator==(Point autre) {
        bool xEqual = this->x_ == autre.getX();
        bool yEqual = this->y_ == autre.getY();
        return xEqual && yEqual;
    }
private:
    int index_;
    int x_;
    int y_;
};

class Vector
{
public:
	Vector(int x = 0, int y = 1) : x_(x), y_(y) 
	{
		norme_ = sqrt(pow(x_, 2) + pow(y_, 2));
		cosinus_ = x_ / norme_;
	}

    int getX() {
        return x_;
    }

    int getY() {
        return y_;
    }

	double getACos() {
		return acos(cosinus_);
	}

    double getNorme() {
        return norme_;
    }

private:
	int x_;
	int y_;
	double norme_;
	double cosinus_;
};

class Cosinus
{
public:
    Cosinus(int index = 0, double cos = 0.0) : index_(index), cos_(cos) {

    }

    int getIndex() {
        return index_;
    }

    double getCos() {
        return cos_;
    }
private:

	int index_;
	double cos_;
};

