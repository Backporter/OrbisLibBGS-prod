#include "../Tasks/TaskUpdateHarvestModel.h"

#include "../../../../source/N/NiAVObject.h"

namespace Tasks
{
	TaskUpdateHarvestModel::TaskUpdateHarvestModel(ConsoleRE::TESObjectREFR* a_ref) : 
		Tasklet("TaskChangeHeadPart", 0, Task::Geometry), 
		m_ref(a_ref) 
	{}

	bool TaskUpdateHarvestModel::Invoke()
	{
		if (m_ref)
		{
			ConsoleRE::NiAVObject* s_model = m_ref->Get3D1();
			if (s_model)
			{
				m_ref->UpdateHarvestModel(s_model);
				return true;
			}
		}

		return false;
	}
}