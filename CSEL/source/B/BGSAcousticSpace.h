#pragma once

#include "../T/TESBoundObject.h"

namespace ConsoleRE
{
	class BGSSoundDescriptorForm;
	class TESRegion;
	class BGSReverbParameters;

	class BGSAcousticSpace : public TESBoundObject
	{
	public:
		static constexpr int TypeID = 16;

		~BGSAcousticSpace() override;
	public:
		BGSSoundDescriptorForm* loopingSound;
		TESRegion*              soundRegion;
		BGSReverbParameters*    reverbType;
	};
}