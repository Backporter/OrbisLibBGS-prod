#pragma once

#include "../Tasklet.h"

#include "../../../../source/P/PlayerCharacter.h"

namespace Tasks
{
	class TaskUpdateHairColor : public Task::Tasklet
	{
	public:
		TaskUpdateHairColor();
		~TaskUpdateHairColor() override = default;

		// override (Task::Tasklet)
		bool Invoke() override;
	public:
	};
}