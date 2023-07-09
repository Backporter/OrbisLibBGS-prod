#pragma once

#include "../Tasklet.h"

#include "../../../../source/A/Actor.h"

namespace Tasks
{
	class TaskRegenHead : public Task::Tasklet
	{
	public:
		TaskRegenHead(ConsoleRE::Actor* a_actor);
		~TaskRegenHead() override = default;

		// override (Task::Tasklet)
		bool Invoke() override;
	public:
		ConsoleRE::Actor* m_actor;
	};
}