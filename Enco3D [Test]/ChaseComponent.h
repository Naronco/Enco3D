#ifndef _CHASECOMPONENT_H_
#define _CHASECOMPONENT_H_

#include <Enco3D.h>

class ChaseComponent : public IGameComponent
{
public:
	void Update()
	{
		Vector3f source = GetTransform()->GetTranslation();
		Vector3f destination = GetRenderingEngine()->GetMainCamera()->GetTranslation();
		GetTransform()->SetTranslation(source + (destination - source) * GetTimer()->GetDeltaTime());
	}
};

#endif