#include "../SoundDescriptor/PapyrusExtSoundDescriptor.h"

#include "../../../../../../source/B/BSFixedString.h"
#include "../../../../../../source/N/NativeFunction.h"

#include "../../../../../../source/B/BGSSoundDescriptorForm.h"
#include "../../../../../../source/T/TESSound.h"

#include "../../../../../../source/B/BGSSoundDescriptor.h"
#include "../../../../../../source/B/BGSStandardSoundDef.h"

#include <math.h>
#include <cmath>

namespace PapyrusExtSoundDescriptor
{
	// I really hate doing this...
	using namespace ConsoleRE;

	float GetDecibelAttenuation(BGSSoundDescriptorForm* base)
	{
		if (base)
		{
			if (base->soundDescriptor)
			{
				return static_cast<BGSStandardSoundDef*>(base->soundDescriptor)->soundCharacteristics.staticAttenuation / 100.0f;
			}
		}

		return 0.0f;
	}

	void SetDecibelAttenuation(BGSSoundDescriptorForm* base, float val)
	{
		if (base)
		{
			if (base->soundDescriptor)
			{
				static_cast<BGSStandardSoundDef*>(base->soundDescriptor)->soundCharacteristics.staticAttenuation = (uint16_t)(val * 100.0f);
			}
		}
	}

	uint32_t GetDecibelVariance(BGSSoundDescriptorForm* base)
	{
		if (base)
		{
			if (base->soundDescriptor)
			{
				return static_cast<BGSStandardSoundDef*>(base->soundDescriptor)->soundCharacteristics.frequencyVariance;
			}
		}

		return 0;
	}
	
	void SetDecibelVariance(BGSSoundDescriptorForm* base, uint32_t val)
	{
		if (base)
		{
			if (base->soundDescriptor)
			{
				if (val < 255)
				{
					static_cast<BGSStandardSoundDef*>(base->soundDescriptor)->soundCharacteristics.frequencyVariance = val;
				}
			}
		}

	}
	
	uint32_t GetFrequencyVariance(BGSSoundDescriptorForm* base)
	{
		if (base)
		{
			if (base->soundDescriptor)
			{
				return static_cast<BGSStandardSoundDef*>(base->soundDescriptor)->soundCharacteristics.frequencyVariance;
			}
		}


		return 0;
	}
	
	void SetFrequencyVariance(BGSSoundDescriptorForm* base, uint32_t val)
	{
		if (base)
		{
			if (base->soundDescriptor)
			{
				if (val < 255)
				{
					static_cast<BGSStandardSoundDef*>(base->soundDescriptor)->soundCharacteristics.dbVariance = val;
				}
			}
		}

	}
	
	uint32_t GetFrequencyShift(BGSSoundDescriptorForm* base)
	{
		if (base)
		{
			if (base->soundDescriptor)
			{
				return static_cast<BGSStandardSoundDef*>(base->soundDescriptor)->soundCharacteristics.frequencyShift;
			}
		}

		return 0;
	}

	void SetFrequencyShift(BGSSoundDescriptorForm* base, uint32_t val)
	{
		if (base)
		{
			if (base->soundDescriptor)
			{
				if (val < 255)
				{
					static_cast<BGSStandardSoundDef*>(base->soundDescriptor)->soundCharacteristics.frequencyShift = val;
				}
			}
		}
	}
	

	bool RegisterSoundDescriptor(ConsoleRE::BSScript::Internal::VirtualMachine* VM)
	{
		VM->RegisterFunction(new BSScript::NativeFunction<false,   NFDLSE(GetDecibelAttenuation), BGSSoundDescriptorForm, float>	      ("GetDecibelAttenuation", "SoundDescriptor",	GetDecibelAttenuation));
		VM->RegisterFunction(new BSScript::NativeFunction<false,   NFDLSE(SetDecibelAttenuation), BGSSoundDescriptorForm, void, float>    ("SetDecibelAttenuation", "SoundDescriptor",	SetDecibelAttenuation));
		VM->RegisterFunction(new BSScript::NativeFunction<false,   NFDLSE(GetDecibelVariance),	  BGSSoundDescriptorForm, uint32_t>       ("GetDecibelVariance",	"SoundDescriptor",	GetDecibelVariance));
		VM->RegisterFunction(new BSScript::NativeFunction<false,   NFDLSE(SetDecibelVariance),	  BGSSoundDescriptorForm, void, uint32_t> ("SetDecibelVariance",	"SoundDescriptor",	SetDecibelVariance));
		VM->RegisterFunction(new BSScript::NativeFunction<false,   NFDLSE(GetFrequencyVariance),  BGSSoundDescriptorForm, uint32_t>       ("GetFrequencyVariance",	"SoundDescriptor",	GetFrequencyVariance));
		VM->RegisterFunction(new BSScript::NativeFunction<false,   NFDLSE(SetFrequencyVariance),  BGSSoundDescriptorForm, void, uint32_t> ("SetFrequencyVariance",	"SoundDescriptor",	SetFrequencyVariance));
		VM->RegisterFunction(new BSScript::NativeFunction<false,   NFDLSE(GetFrequencyShift),	  BGSSoundDescriptorForm, uint32_t>       ("GetFrequencyShift",		"SoundDescriptor",	GetFrequencyShift));
		VM->RegisterFunction(new BSScript::NativeFunction<false,   NFDLSE(SetFrequencyShift),	  BGSSoundDescriptorForm, void, uint32_t> ("SetFrequencyShift",		"SoundDescriptor",	SetFrequencyShift));
		
		return true;
	}
}