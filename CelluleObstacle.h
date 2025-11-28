#pragma once
#include "Cellule.h"
class CelluleObstacle :
    public Cellule
{
 private:
	const bool estObstacle;
public:
	CelluleObstacle(int x, int y);
	~CelluleObstacle() = default;
};

