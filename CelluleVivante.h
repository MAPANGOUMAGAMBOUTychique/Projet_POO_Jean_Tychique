#pragma once
#include "Cellule.h"
class CelluleVivante :
    public Cellule
{
private:
	const bool estVivante;
public:
	CelluleVivante(int x, int y);
	~CelluleVivante() = default;

};

