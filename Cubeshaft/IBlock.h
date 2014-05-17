#ifndef __IBLOCK_H_INCLUDED__
#define __IBLOCK_H_INCLUDED__

#include <string>

enum BlockSide : int
{
	West = 0,
	East = 1,
	Top = 2,
	Bottom = 3,
	North = 4,
	South = 5,
};

class IBlock
{
public:
	virtual std::string getTextureNameAtBlockSide(int blockSide) = 0;
};

#endif