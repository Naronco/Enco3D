#ifndef _TESTGAME_H_
#define _TESTGAME_H_

#include "Player.h"

#include <Enco3D.h>

using namespace Enco3D::Core;
using namespace Enco3D::Component;
using namespace Enco3D::Rendering;
using namespace Enco3D::Physics;
using namespace Enco3D::Audio;

class TestGame : public IGame
{
public:
	void Init();
	void Deinit();
	
	void Update();
	void Render();
};

#endif