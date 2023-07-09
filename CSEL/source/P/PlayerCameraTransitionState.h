#pragma once

#include "../T/TESCameraState.h"

namespace ConsoleRE
{
	class PlayerCameraTransitionState : public TESCameraState
	{
	public:
		~PlayerCameraTransitionState();
	public:
		void*			Unk20;
		TESCameraState* transitionFrom;
		TESCameraState* transitionTo;
		uint16_t		Unk38;
	};
}