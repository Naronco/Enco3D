#include "DiamondSquareAlgorithm.h"
#include <Enco3D/Enco3D.h>

int main(int argc, char *argv[])
{
	Enco3D_StartInstruction instruction;
	instruction.multisampleEnabled = true;
	instruction.windowWidth = 1600;
	instruction.windowHeight = 900;
	instruction.windowTitle = "Diamond Square Example";

	return Enco3D_Main(&instruction, new DiamondSquare);
}