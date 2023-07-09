#pragma once

#include "../Tasklet.h"

#include "../../../../source/A/Actor.h"
#include "../../../../source/B/BGSHeadPart.h"

namespace Tasks
{
	class TaskChangeHeadPart : public Task::Tasklet
	{
	public:
		TaskChangeHeadPart(ConsoleRE::Actor* a_actor, ConsoleRE::BGSHeadPart* a_oldPart, ConsoleRE::BGSHeadPart* a_newPart);
		~TaskChangeHeadPart() override = default;

		// override (Task::Tasklet)
		bool Invoke() override;
	public:
		ConsoleRE::Actor*	    m_actor;
		ConsoleRE::BGSHeadPart* m_oldPart;
		ConsoleRE::BGSHeadPart* m_newPart;
	};
}