#pragma once

#include "../N/NiProperty.h"

namespace ConsoleRE
{
	class NiAlphaProperty : public NiProperty
	{
	public:
		enum class AlphaFunction
		{
			kOne = 0,
			kZero = 1,
			kSrcColor = 2,
			kInvSrcColor = 3,
			kDestColor = 4,
			kInvDestColor = 5,
			kSrcAlpha = 6,
			kInvSrcAlpha = 7,
			kDestAlpha = 8,
			kInvDestAlpha = 9,
			kSrcAlphaSat = 10
		};
	public:
		~NiAlphaProperty() override;

		// override (NiProperty)
		const NiRTTI*      GetRTTI() const override;
		NiObject*          CreateClone(NiCloningProcess& a_cloning) override;
		void               LoadBinary(NiStream& a_stream) override;
		void               LinkObject(NiStream& a_stream) override;
		bool               RegisterStreamables(NiStream& a_stream) override;
		void               SaveBinary(NiStream& a_stream) override;
		bool               IsEqual(NiObject* a_object) override;
		Type 			   GetType() const override;
	public:
	};
	static_assert(sizeof(NiAlphaProperty) == 0x30);
}