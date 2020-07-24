// Copyright Daniel Thompson @ https://github.com/CakeQ and Archie Whitehead 2020 All Rights Reserved.

#include "DropPointGridCoord.h"

FDropPointGridCoord::FDropPointGridCoord()
{

}

FDropPointGridCoord::FDropPointGridCoord(const int32& NewX, const int32& NewY)
{
	GridX = NewX;
	GridY = NewY;
}

bool FDropPointGridCoord::operator==(const FDropPointGridCoord& Coord2) const
{
	return GridX == Coord2.GridX && GridY == Coord2.GridY;
}

FDropPointGridCoord FDropPointGridCoord::operator+=(const FDropPointGridCoord& Coord2)
{
	GridX += Coord2.GridX;
	GridY += Coord2.GridY;
	return *this;
}

FDropPointGridCoord FDropPointGridCoord::operator-=(const FDropPointGridCoord& Coord2)
{
	GridX -= Coord2.GridX;
	GridY -= Coord2.GridY;
	return *this;
}
