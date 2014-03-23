#include "TestGame.h"

int main(int argc, char *argv[])
{
	Enco3DEngine::GetInstance()->Init("Enco3D test", 1024, 576, new TestGame);
	Enco3DEngine::GetInstance()->MainLoop();
	Enco3DEngine::GetInstance()->Deinit();
	
	return 0;
}