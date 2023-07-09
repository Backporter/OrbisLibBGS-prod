#include "../../../../../OrbisUtil/include/Mutex.h"
#include "../../../../../OrbisUtil/include/Logger.h"

#include "../TaskPool/TaskPool.h"

#ifndef USE_QUEUE
#define USE_QUEUE 1
#endif

// DEBUG: TEST IF swapping between queue/deque will chanbge performance and pick the better version.
#if USE_QUEUE
#include <queue>
#define Queue std::queue
#define _PushQueue(queue, data) queue.push(data);
#define _PopQueue(queue) queue.pop();
#else
#include <deque>
#define Queue std::deque
#define _PushQueue(queue, data) queue.push_back(data);
#define _PopQueue(queue) queue.pop_front();
#endif

namespace TaskPool
{
	static Queue<Task::Tasklet*> TaskQueue;
	
	static bool IsTaskQueueEmpty()
	{
		xUtilty::scoped_lock<xUtilty::Mutex> scoped(xUtilty::Mutex::GetSingleton(xUtilty::Mutex::kTasklet));
		return TaskQueue.empty();
	}

	void PushQueue(Task::Tasklet* a_message)
	{
		// get mutex for tasklet
		auto& taskletMutex = xUtilty::Mutex::GetSingleton(xUtilty::Mutex::kTasklet);

		// lock
		if (taskletMutex.Lock() != true)
		{
			// PRINT_POS;
		}

		// push
		_PushQueue(TaskQueue, a_message);

		// unlock
		if (taskletMutex.Unlock() != true)
		{
			// PRINT_POS;
		}
	}

	void ProcessQueue(ConsoleRE::BSTaskPool* a_this)
	{
		a_this->ProcessQueue();

// #if USE_TASKLET
		auto& taskletMutex = xUtilty::Mutex::GetSingleton(xUtilty::Mutex::kTasklet);

		while (!IsTaskQueueEmpty())
		{
			PRINT_POS;

			if (taskletMutex.Lock() != true)
			{
				// PRINT_POS;
			}

			auto* cmd = TaskQueue.front();
			_PopQueue(TaskQueue);
			
			if (taskletMutex.Unlock() != true)
			{
				// PRINT_POS;
			}

			auto ret = cmd->Invoke();
			if (!ret)
			{
				xUtilty::Log::GetSingleton()->Write(xUtilty::Log::logLevel::kWarning,"[TaskPool] Tasklet [Name: %s / Version: %d / Type: %d] Failed.", cmd->GetName(), cmd->GetVersion(), cmd->GetTaskType());
			}

			delete cmd;
		}
	}
// #endif
}