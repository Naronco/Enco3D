#ifndef _TESTGAME_H_
#define _TESTGAME_H_

#include <Enco3D.h>
using namespace Enco3D;

#include "ChaseComponent.h"

class TestGame : public IGame
{
private:
	SpotLight *m_spotLight{ nullptr };

public:
	void Init();
	void Deinit();
	
	void Update();
	void Render();
};

#endif