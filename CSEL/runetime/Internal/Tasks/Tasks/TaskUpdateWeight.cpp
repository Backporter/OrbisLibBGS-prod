#include "../Tasks/TaskUpdateWeight.h"

namespace Tasks
{
	TaskUpdateWeight::TaskUpdateWeight(ConsoleRE::Actor* a_actor, float a_delta, uint32_t a_flags, bool a_redrew) : 
		Tasklet("TaskUpdateWeight", 0, Task::General), 
		m_actor(a_actor), m_delta(a_delta), m_updateFlags(a_flags), m_redraw(a_redrew) 
	{}

	bool TaskUpdateWeight::Invoke()
	{
		if (m_actor)
		{
			ConsoleRE::TESNPC* npc = TES_RTTI(m_actor->data.objectReference, TESForm, TESNPC);
			if (npc)
			{
				ConsoleRE::BSFaceGenNiNode* facenode = m_actor->GetFaceGenNiNode();
				if (facenode)
				{
					facenode->AdjustHeadMorph(3, 0, m_delta);
					facenode->UpdateModelFace();
				}

				if (m_redraw && m_actor->IsWeaponDrawn())
				{
					m_actor->DrawWeaponMagicHands(false);
					m_actor->DrawWeaponMagicHands(true);
				}

				return true;
			}

			return false;
		}

		return false;
	}
}