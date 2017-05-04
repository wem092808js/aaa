#pragma once

// It's actually in DLLMain but w/e
extern bool DoUnload;
#include "Utilities.h"


namespace Hooks
{
	void Initialise();
	void UndoHooks();
	void FakeLagConstant();
	void FakeLagInAir();
	void FakeLagOnCrouch();
	void FakeLagOnGround();

	// VMT Managers
	extern Utilities::Memory::VMTManager VMTPanel; // Hooking drawing functions
	extern Utilities::Memory::VMTManager VMTClient; // Maybe CreateMove
	extern Utilities::Memory::VMTManager VMTClientMode; // CreateMove for functionality
	extern Utilities::Memory::VMTManager VMTModelRender; // DrawModelEx for chams
	extern Utilities::Memory::VMTManager VMTPrediction; // InPrediction for no vis recoil
};