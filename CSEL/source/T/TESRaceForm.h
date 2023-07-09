#pragma once

#include "../B/BaseFormComponent.h"

namespace ConsoleRE
{
	class TESRace;

	class TESRaceForm : public BaseFormComponent
	{
	public:
		~TESRaceForm() override;

		// override (BaseFormComponent)
		void InitializeDataComponent() override;
		void ClearDataComponent() override;
		void CopyComponent(BaseFormComponent* a_rhs) override;
	public:
		TESRace* race;
	};
	static_assert(sizeof(TESRaceForm) == 0x10);
}