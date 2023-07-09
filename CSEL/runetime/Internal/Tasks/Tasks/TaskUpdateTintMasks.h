#pragma once

#include "../Tasklet.h"

namespace Tasks
{
	class TaskUpdateTintMasks : public Task::Tasklet
	{
	public:
		TaskUpdateTintMasks();
		~TaskUpdateTintMasks() override = default;

		// override (Task::Tasklet)
		bool Invoke() override;
	public:
	};
}