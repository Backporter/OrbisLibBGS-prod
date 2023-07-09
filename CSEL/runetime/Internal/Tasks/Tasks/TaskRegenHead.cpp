#include "../Tasks/TaskRegenHead.h"

#include "../../../../source/B/BSFaceGenManager.h"
#include "../../../../source/B/BGSHeadPart.h"
#include "../../../../source/T/TESNPC.h"
#include "../../../../source/F/FormTraits.h"

namespace Tasks
{
	TaskRegenHead::TaskRegenHead(ConsoleRE::Actor* a_actor) : 
		Tasklet("TaskRegenHead", 0, Task::Geometry), 
		m_actor(a_actor)
	{}

	bool TaskRegenHead::Invoke()
	{
		if (m_actor)
		{
			ConsoleRE::TESNPC* npc = m_actor->GetObjectReference()->As<ConsoleRE::TESNPC>();

			if (npc)
			{
				ConsoleRE::BSFaceGenNiNode* faceNode = m_actor->GetFaceGenNiNode();
				ConsoleRE::BGSHeadPart*     facePart = npc->GetCurrentHeadPartByType(1);

				if (faceNode && facePart)
				{
					ConsoleRE::BSFaceGenManager::GetSingleton()->RegenerateHead(faceNode, facePart, npc);
				}

				return true;
			}
		}
		
		return false;
	}
}