#pragma once

#include "../../../../../OrbisUtil/include/Relocation.h"
#include "../../../../../OrbisUtil/include/Mutex.h"

#include "../../../../source/B/BSTArray.h"
#include "../../../../source/U/UI.h"
#include "../../../../source/U/UIMessageQueue.h"

#include "../../../../runetime/Internal//Tasks/Tasklet.h"

#include <deque>
#include <queue>

namespace MessageQueue
{
	namespace UI
	{
		void PushQueue(Task::Tasklet* a_message);
		void ProcessQueue(ConsoleRE::UIMessageQueue* a_this);
	}
}
