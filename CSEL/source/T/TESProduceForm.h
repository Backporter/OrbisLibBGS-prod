#pragma once

#include "../B/BaseFormComponent.h"

namespace ConsoleRE
{
	class BGSSoundDescriptorForm;
	class TESBoundObject;

	struct SEASON
	{
		enum : uint32_t
		{
			kNone = 0xFFFFFFFF,
			kSpring = 0,
			kSummer,
			kFall,
			kWinter,
			kTotal,
		};
	};

	class TESProduceForm : public BaseFormComponent
	{
	public:
		~TESProduceForm() override;

		// override (BaseFormComponent)
		void InitializeDataComponent() override;
		void ClearDataComponent() override;
		void CopyComponent(BaseFormComponent* a_rhs) override;
	public:
		BGSSoundDescriptorForm*			harvestSound;
		TESBoundObject*					produceItem;
		int8_t							produceChance[SEASON::kTotal];
	};
	static_assert(sizeof(TESProduceForm) == 0x20);
}