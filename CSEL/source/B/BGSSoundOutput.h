#pragma once

#include "../B/BSISoundOutputModel.h"
#include "../T/TESForm.h"

namespace ConsoleRE
{
	class BGSSoundOutput : public TESForm, public BSISoundOutputModel
	{
	public:
		static constexpr int TypeID = 131;
		
		struct Data
		{
		public:
			enum class Flag
			{
				kNone = 0,
				kAttenuatesWithDistance = 1 << 0,
				kAllowsRumble = 1 << 1
			};
		public:
			uint8_t	flags;
			uint8_t unk1;
			uint8_t unk2;
			uint8_t reverbSendPct;
		};
		static_assert(sizeof(Data) == 0x4);

		struct DynamicAttenuationCharacteristics : public BSIAttenuationCharacteristics
		{
		public:
			struct DataType
			{
			public:
				float			minDistance;
				float			maxDistance;
				uint8_t			curve[5];
				uint8_t			pad15;
				uint16_t		pad16;
			};
			static_assert(sizeof(DataType) == 0x10);
		public:
			~DynamicAttenuationCharacteristics() override;

			// override (BSIAttenuationCharacteristics)
			float        GetMaxDistance() const override;
			float        GetMinDistance() const override;
			uint8_t		 GetCurveValue(uint32_t a_idx) const override;
		public:
			DataType data;
		};
		static_assert(sizeof(DynamicAttenuationCharacteristics) == 0x18);

		struct SpeakerArrays
		{
		public:
			struct Channel
			{
			public:
				uint8_t l;
				uint8_t r;
				uint8_t c;
				uint8_t lfe;
				uint8_t rl;
				uint8_t rr;
				uint8_t bl;
				uint8_t br;
			};
			static_assert(sizeof(Channel) == 0x8);
		public:
			Channel channels[3];
		};
		static_assert(sizeof(SpeakerArrays) == 0x18);
	public:
		~BGSSoundOutput() override;

		// override (TESForm)
		void ClearData() override;
		bool Load(TESFile* a_mod) override;
		void InitItemImpl() override;
	public:
		// override (BSISoundOutputModel)
		bool                                 DoGetUsesHRTF() const override;
		bool                                 DoGetHasSpeakerBias() const override;
		bool                                 DoGetSpeakerBias(uint32_t a_arg1, uint32_t a_arg2, float(&a_arg3)[8]) const override;
		bool                                 DoGetAttenuatesWithDistance() const override;
		bool                                 DoGetAudibility(float a_distance) const override;
		uint32_t							 DoGetSupportedInputChannels() const override;
		const BSIAttenuationCharacteristics* DoGetAttenuation() const override;
		float                                DoGetReverbSendLevel() const override;
		bool								 DoGetSupportsMonitor(uint32_t a_arg1) const override;
	public:
		Data									data;
		uint32_t								type;
		DynamicAttenuationCharacteristics*		attenuation;
		SpeakerArrays*							speakerOutputs;
	};
	static_assert(sizeof(BGSSoundOutput) == 0x40);
}