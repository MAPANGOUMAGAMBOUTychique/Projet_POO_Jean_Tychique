#pragma once
class Cellule
{
private:
	int x;
	int y;
public:
	Cellule() = default;
	Cellule(int x, int y);
	int getX() const ;
	int getY() const;
	virtual ~Cellule() = default;
};

