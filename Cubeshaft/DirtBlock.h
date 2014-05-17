#ifndef __DIRTBLOCK_H_INCLUDED__
#define __DIRTBLOCK_H_INCLUDED__

#include "IBlock.h"

class DirtBlock : public IBlock
{
public:
	std::string getTextureNameAtBlockSide(int blockSide)
	{
		return "texture/terrain/block/dirt.png";
	}
};

#endif