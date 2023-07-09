#pragma once

#include "../Tasklet.h"

#include "../../../../source/T/TESObjectREFR.h"

namespace Tasks
{
	class TaskUpdateHarvestModel : public Task::Tasklet
	{
	public:
		TaskUpdateHarvestModel(ConsoleRE::TESObjectREFR* a_ref);
		~TaskUpdateHarvestModel() override = default;
		
		// override (Task::Tasklet)
		bool Invoke() override;
	public:
		ConsoleRE::TESObjectREFR* m_ref;
	};
}