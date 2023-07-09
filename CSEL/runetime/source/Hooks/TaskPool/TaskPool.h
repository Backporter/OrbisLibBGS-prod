#pragma once

#include "../../../../source/B/BSTaskPool.h"
#include "../../../Internal/Tasks/Tasklet.h"

namespace TaskPool
{
	void PushQueue(Task::Tasklet* a_message);

	void ProcessQueue(ConsoleRE::BSTaskPool* a_this);
}