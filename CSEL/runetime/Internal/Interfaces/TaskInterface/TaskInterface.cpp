#include "TaskInterface.h"

#include "../../../source/Hooks/TaskPool/TaskPool.h"
#include "../../../source/Hooks/MessageQueueUI/MessageQueue.h"

namespace Interface
{
	int	TaskInterface::GetInterfaceVersion()
	{
		return Version;
	}

	void TaskInterface::AddTask(Task::Tasklet* a_func)	 
	{ 
		return TaskPool::PushQueue(a_func);			
	}
	
	void TaskInterface::AddUITask(Task::Tasklet* a_func) 
	{ 
		return MessageQueue::UI::PushQueue(a_func);	
	}
}