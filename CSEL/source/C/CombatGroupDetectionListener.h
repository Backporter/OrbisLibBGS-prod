#pragma once

#include "../D/DetectionListener.h"

namespace ConsoleRE
{
	class CombatGroupDetectionListener : public DetectionListener
	{
	public:
		~CombatGroupDetectionListener() override;

		// override (DetectionListener)
		void Unk_03() override;

		// add
		virtual void Unk_06();
	public:
		void* unk10;
	};
	static_assert(sizeof(CombatGroupDetectionListener) == 0x18);
}