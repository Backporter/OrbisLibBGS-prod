#pragma once

#include "../QueryInterface/QueryInterface.h"

#include "../../../../runetime/Internal/Tasks/Tasklet.h"

namespace Interface
{
	class TaskInterface : public QueryInterface
	{
	public:
		// Interface ID
		static constexpr int TypeID = 2;

		// Interface Version
		static constexpr size_t Version = 1;
	public:
		TaskInterface() = default;
		~TaskInterface() override = default;
		
		// override (QueryInterface)
		int	GetInterfaceVersion() override;

		//  add
		virtual void AddTask(Task::Tasklet*);
		virtual void AddUITask(Task::Tasklet*);
	};
	static_assert(sizeof(TaskInterface) == 0x8);
}