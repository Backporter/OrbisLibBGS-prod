#include "../Tasks/TaskUpdateWorldData.h"

namespace Tasks
{
	TaskUpdateWorldData::TaskUpdateWorldData(ConsoleRE::NiAVObject* a_object) : 
		Tasklet("TaskUpdateWorldData", 0, Task::World),
		m_object(a_object)
	{
		if (a_object)
		{
			a_object->IncrementRef();
		}
	}

	TaskUpdateWorldData::~TaskUpdateWorldData()
	{
		if (m_object)
		{
			m_object->DeincrementRef();
		}
	}

	bool TaskUpdateWorldData::Invoke()
	{
		ConsoleRE::NiUpdateData worldData;

		if (m_object)
		{
			m_object->UpdateWorldData(&worldData);
		}

		return true;
	}

}