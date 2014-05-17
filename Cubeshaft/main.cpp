#include <Enco3D\Enco3D.h>
#include "Cubeshaft.h"

int main(int argc, char *argv[])
{
	Enco3D_StartInstruction instruction;
	instruction.aaSamples = 16;
	instruction.multisampleEnabled = true;
	instruction.windowWidth = 1024;
	instruction.windowHeight = 576;
	instruction.windowTitle = "Cubeshaft";

	return Enco3D_Main(&instruction, new Cubeshaft);
}