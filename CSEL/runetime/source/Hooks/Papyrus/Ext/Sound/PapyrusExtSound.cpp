#include "../Sound/PapyrusExtSound.h"

#include "../../../../../../source/B/BSFixedString.h"
#include "../../../../../../source/N/NativeFunction.h"

#include "../../../../../../source/B/BGSSoundDescriptorForm.h"
#include "../../../../../../source/T/TESSound.h"

#include <math.h>
#include <cmath>

namespace PapyrusExtSound
{
	// I really hate doing this...
	using namespace ConsoleRE;

	BGSSoundDescriptorForm* GetSoundDescriptor(TESSound* base)
	{
		if (base)
		{
			return base->descriptor;
		}

		return NULL;
	}

	bool RegisterSound(ConsoleRE::BSScript::Internal::VirtualMachine* VM)
	{
		VM->RegisterFunction(new BSScript::NativeFunction<false, NFDLSE(GetSoundDescriptor), TESSound, BGSSoundDescriptorForm*>("GetDescriptor", "Sound", GetSoundDescriptor));
		return true;
	}
}