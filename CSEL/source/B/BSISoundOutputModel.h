#pragma once

namespace ConsoleRE
{
	class BSISoundOutputModel
	{
	public:
		struct BSIAttenuationCharacteristics
		{
			virtual ~BSIAttenuationCharacteristics();

			// add
			virtual float        GetMaxDistance() const = 0;
			virtual float        GetMinDistance() const = 0;
			virtual uint8_t		 GetCurveValue(uint32_t a_idx) const = 0;
		};
		static_assert(sizeof(BSIAttenuationCharacteristics) == 0x8);
	public:
		virtual ~BSISoundOutputModel();

		// add
		virtual bool                                 DoGetUsesHRTF() const = 0;
		virtual bool                                 DoGetHasSpeakerBias() const = 0;
		virtual bool                                 DoGetSpeakerBias(uint32_t a_arg1, uint32_t a_arg2, float(&a_arg3)[8]) const = 0;
		virtual bool                                 DoGetAttenuatesWithDistance() const = 0;
		virtual bool                                 DoGetAudibility(float a_distance) const = 0;
		virtual uint32_t							 DoGetSupportedInputChannels() const = 0;
		virtual const BSIAttenuationCharacteristics* DoGetAttenuation() const = 0;
		virtual float                                DoGetReverbSendLevel() const = 0;
		virtual bool                                 DoGetSupportsMonitor(uint32_t a_arg1) const = 0;
	};
}