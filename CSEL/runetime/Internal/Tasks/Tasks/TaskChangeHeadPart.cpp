#include "../Tasks/TaskChangeHeadPart.h"

namespace Tasks
{
	TaskChangeHeadPart::TaskChangeHeadPart(ConsoleRE::Actor* a_actor, ConsoleRE::BGSHeadPart* a_oldPart, ConsoleRE::BGSHeadPart* a_newPart) : 
		Tasklet("TaskChangeHeadPart", 0, Task::Geometry), 
		m_actor(a_actor), m_oldPart(a_oldPart), m_newPart(a_newPart)
	{}

	bool TaskChangeHeadPart::Invoke()
	{
		if (m_actor)
		{
			m_actor->SwapHeadPart(m_oldPart, m_newPart);
			return true;
		}

		return false;
	}
}