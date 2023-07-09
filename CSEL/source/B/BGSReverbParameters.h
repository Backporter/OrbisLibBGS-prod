#pragma once

#include "../B/BSIReverbType.h"
#include "../T/TESForm.h"

namespace ConsoleRE
{
	class BGSReverbParameters : public TESForm, public BSIReverbType
	{
	public:
		static constexpr int TypeID = 134;
		
		struct ReverbParams
		{
		public:
			uint16_t decayTime;
			uint16_t hfReference;
			int8_t   roomFilter;
			int8_t   roomHFFilter;
			int8_t   reflections;
			int8_t   reverb;
			int8_t   decayHFRatio;
			int8_t   reflectionDelay;
			int8_t   reverbDelay;
			int8_t   diffusionPct;
			int8_t   densityPct;
			uint8_t  pad0D;
		};
		static_assert(sizeof(ReverbParams) == 0xE);
	public:
		~BGSReverbParameters() override;

		// override (TESForm)
		void InitializeData() override;
		bool Load(TESFile* a_mod) override;

		// override (BSIReverbType)
		int32_t				DoGetRoomLevel() const override;
		int32_t				DoGetRoomHFLevel() const override;
		float               DoGetDecayTime() const override;
		float               DoGetDecayHFRatio() const override;
		int32_t				DoGetReflectionLevel() const override;
		float               DoGetReflectionDelay() const override;
		int32_t				DoGetReverbLevel() const override;
		float               DoGetReverbDelay() const override;
		float               DoGetDiffusion() const override;
		float               DoGetDensity() const override;
		float				DoGetHFReference() const override;
	public:
		ReverbParams  data;
	};
	static_assert(sizeof(BGSReverbParameters) == 0x38);
}