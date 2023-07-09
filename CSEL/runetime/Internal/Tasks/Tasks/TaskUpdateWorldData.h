#pragma once

#include "../Tasklet.h"

#include "../../../../source/N/NiAVObject.h"

namespace Tasks
{
	class TaskUpdateWorldData : public Task::Tasklet
	{
	public:
		TaskUpdateWorldData(ConsoleRE::NiAVObject* a_object);
		~TaskUpdateWorldData() override;

		// override (Task::Tasklet)
		bool Invoke() override;
	public:
		ConsoleRE::NiAVObject* m_object;
	};
}