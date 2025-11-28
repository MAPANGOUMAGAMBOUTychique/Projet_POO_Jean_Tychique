#pragma once
#include "Cellule.h"

class CelluleMorte :
    public Cellule
{
private:
	const bool estVivante;
public:
	CelluleMorte(int x, int y);
	~CelluleMorte() = default;
};