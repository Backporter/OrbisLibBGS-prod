#pragma once

#include "../B/BSAtomic.h"
#include "../B/BSFaceGenKeyframeMultiple.h"
#include "../N/NiExtraData.h"
#include "../N/NiPoint3.h"

namespace ConsoleRE
{
	class BSFaceGenAnimationData : public NiExtraData
	{
	public:
		~BSFaceGenAnimationData() override;

		// override (NiExtraData)
		const NiRTTI* GetRTTI() const override;

		// ...
		void ClearExpressionOverride() noexcept { exprOverride = false; }

		void Reset(float a_timer, bool a_resetExpression, bool a_resetModifierAndPhoneme, bool a_resetCustom, bool a_closeEyes)
		{
			using func_t = void(decltype(this), float, bool, bool, bool, bool);
			Relocation<func_t*> func("", 0x45E090);
			return func(this, a_timer, a_resetExpression, a_resetModifierAndPhoneme, a_resetCustom, a_closeEyes);
		}

		void SetExpression(uint32_t type, float value)
		{
			using func_t = void(decltype(this), uint32_t, float);
			Relocation<func_t*> func("", 0x45E6A0);
			return func(this, type, value);
		}
	public:
		BSFaceGenKeyframeMultiple*	transitionTargetKeyFrame;
		BSFaceGenKeyframeMultiple	keyframes[12];
		NiPoint3					Unk1A0;
		uint32_t					Unk1AC;
		uint64_t					Unk1B0;
		uint64_t					Unk1B8;
		uint64_t					Unk1C0;
		uint64_t					Unk1C8;
		uint8_t						Unk1D0;
		uint8_t						Unk1D1;
		uint16_t					Unk1D2;
		uint32_t					Unk1D4;
		uint64_t					Unk1D8;
		uint64_t					Unk1E0;
		uint64_t					Unk1E8;
		uint32_t					Unk1F0;
		uint32_t					Unk1F4;
		uint64_t					Unk1F8;
		uint32_t					Unk200;
		float						blinkDelay;
		uint32_t					Unk208;
		uint32_t					Unk20C;
		uint32_t					Unk210;
		uint16_t					Unk214;
		uint8_t						Unk216;
		uint8_t						Unk217;
		uint8_t						Unk218;
		uint8_t						Unk219;
		uint8_t						Unk21A;
		uint8_t						Unk21B;
		uint8_t						Unk21C;
		uint8_t						Unk21D;
		bool						exprOverride;
		uint8_t						Unk21F;
		mutable BSSpinLock			lock;
		uint64_t					Unk228;
	};
	static_assert(sizeof(BSFaceGenAnimationData) == 0x238);
}