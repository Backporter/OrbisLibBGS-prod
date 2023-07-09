#pragma once

#include "../B/BaseFormComponent.h"
#include "../T/TESForm.h"

namespace ConsoleRE
{
	class TESFaction;
	class TESForm;
	class TESGlobal;
	class ContainerItemExtra;

	struct LEVELED_OBJECT
	{
	public:
		TESForm*            form;
		uint16_t			count;
		uint16_t			level;
		uint32_t			pad0C;
		ContainerItemExtra* itemExtra;
	};
	static_assert(sizeof(LEVELED_OBJECT) == 0x18);

	class TESLeveledList : public BaseFormComponent
	{
	public:
		~TESLeveledList() override;

		// override (BaseFormComponent)
		void InitializeDataComponent() override;
		void ClearDataComponent() override;
		void CopyComponent(BaseFormComponent* a_rhs) override;

		// add
		virtual uint8_t			GetChanceNone();
		virtual bool			GetMultCalc();
		virtual int32_t			GetLevDifferenceMax();
		virtual bool			GetCanContainFormsOfType(uint32_t a_type) const = 0;
	public:
		LEVELED_OBJECT*			    entries;
		int8_t						chanceNone;
		uint8_t                     llFlags;
		uint8_t						numEntries;
		uint8_t						unk13;
		uint32_t					pad14;
		void*                       unk18;
		TESGlobal*                  chanceGlobal;
	};
	static_assert(sizeof(TESLeveledList) == 0x28);
}