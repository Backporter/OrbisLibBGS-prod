#pragma once

#include "../../../../../OrbisUtil/include/Relocation.h"

#include "../../../../source/A/Actor.h"
#include "../../../../source/T/TESCamera.h"
#include "../../../../source/T/TESCameraState.h"

namespace Misc
{
	void SetCrossHairRefr(void*,ConsoleRE::NiPointer<ConsoleRE::TESObjectREFR>* a_crossHairRefr);
	ConsoleRE::TESObjectREFR* GetCrossHairRefr();

	void UpdateEquipment(void* a_this, ConsoleRE::Actor* a_actor);
	void PushCrossHairRefEvent();

	void PushGlobalCameraEvents(ConsoleRE::TESCameraState* old, ConsoleRE::TESCameraState* current);
	void UpdatecameraState(ConsoleRE::TESCamera* a_this, ConsoleRE::TESCameraState* a_rhs);
}