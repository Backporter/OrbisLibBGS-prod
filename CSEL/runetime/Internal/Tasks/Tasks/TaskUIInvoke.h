#pragma once

#include "../Tasklet.h"

#include "../../../../source/B/BSFixedString.h"
#include "../../../../source/U/UI.h"
#include "../../../../source/G/GFxValue.h"

namespace Tasks
{
	class TaskUIInvoke : public Task::Tasklet
	{
	public:
		TaskUIInvoke(ConsoleRE::BSFixedString a_name, ConsoleRE::BSFixedString a_target);
		~TaskUIInvoke() override = default;

		// override (Task::Tasklet)
		bool Invoke() override;
	public:
		ConsoleRE::BSFixedString		 m_name;
		ConsoleRE::BSFixedString		 m_target;
		std::vector<ConsoleRE::GFxValue> m_args;
	};
}