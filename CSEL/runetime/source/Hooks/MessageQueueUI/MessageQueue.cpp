#include "MessageQueue.h"

#include <chrono>

#ifndef USE_QUEUE
#define USE_QUEUE 1
#endif

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

namespace MessageQueue
{
	namespace UI
	{
		static Queue<Task::Tasklet*> MessageQueue;

		void PushQueue(Task::Tasklet* a_message)
		{
			auto& UiMutex = xUtilty::Mutex::GetSingleton(xUtilty::Mutex::kUI);

			UiMutex.Lock();
			_PushQueue(MessageQueue, a_message);
			UiMutex.Unlock();
		}

		void ProcessQueue(ConsoleRE::UIMessageQueue* a_this)
		{
			a_this->ProcessCommands();

			auto& UiMutex = xUtilty::Mutex::GetSingleton(xUtilty::Mutex::kUI);

			UiMutex.Lock();

			while (!MessageQueue.empty())
			{
				auto* cmd = MessageQueue.front();
				if (cmd)
				{
					auto ret = cmd->Invoke();
					if (!ret)
					{
						xUtilty::Log::GetSingleton()->Write(xUtilty::Log::logLevel::kWarning, "[MessageQueue::UI] Tasklet [Name: %s / Version: %d / Type: %d] Failed.", cmd->GetName(), cmd->GetVersion(), cmd->GetTaskType());
					}

					delete cmd;
				}

				_PopQueue(MessageQueue)
			}

			UiMutex.Unlock();
		}
	}
}