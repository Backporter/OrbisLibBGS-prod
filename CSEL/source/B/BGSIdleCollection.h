#pragma once

#include "../B/BaseFormComponent.h"

namespace ConsoleRE
{
	class TESIdleForm;

	class BGSIdleCollection : public BaseFormComponent
	{
	public:
		~BGSIdleCollection() override;

		// override (BaseFormComponent)
		void InitializeDataComponent() override;
		void ClearDataComponent() override;
		void CopyComponent(BaseFormComponent* a_rhs) override;
	public:
		int8_t										idleFlags;
		int8_t										idleCount;
		uint16_t									pad0A;
		uint32_t									pad0C;
		TESIdleForm**								idles;
		float										timerCheckForIdle;
		uint32_t									pad1C;
	};
	static_assert(sizeof(BGSIdleCollection) == 0x20);
}