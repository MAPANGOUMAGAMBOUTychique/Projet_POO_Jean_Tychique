#include "Cellule.h"

Cellule::Cellule(int x, int y) : x(x), y(y){}

int Cellule::getX() const{
	return x;
}

int Cellule::getY() const{
	return y;
}

