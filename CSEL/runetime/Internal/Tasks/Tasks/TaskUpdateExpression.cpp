#include "../Tasks/TaskUpdateExpression.h"

#include "../../../../source/B/BSFaceGenManager.h"
#include "../../../../source/B/BSFaceGenNiNode.h"
#include "../../../../source/B/BSFaceGenAnimationData.h"


namespace Tasks
{
	TaskUpdateExpression::TaskUpdateExpression(ConsoleRE::Actor* a_actor, uint8_t a_type, uint16_t a_index, float a_value) : 
		Tasklet("TaskUpdateExpression", 0, Task::Geometry)
	{
		m_actor = a_actor;
		m_index = a_index;
		m_type = a_type;

		if (a_value < 0.0f) a_value = 0.0f;
		if (a_value > 1.0f) a_value = 1.0f;

		m_value = a_value;
	}

	bool TaskUpdateExpression::Invoke()
	{
		if (m_actor)
		{
			ConsoleRE::BSFaceGenAnimationData* animdata = m_actor->GetFaceGenAnimationData();
			if (animdata)
			{
				if (m_type != 255)
				{
					ConsoleRE::BSFaceGenManager::GetSingleton()->Unk48 = 0;
					auto& keyframe = animdata->keyframes[m_type];
					if (m_index >= keyframe.Unk18)
					{
						return false;
					}

					keyframe.Unk10[m_index] = m_value;
					keyframe.Unk1C = 0;
				}
				else
				{
					// animdata->exprOverride = 0;
					animdata->Reset(1.0f, 1, 1, 0, 0);
					ConsoleRE::BSFaceGenManager::GetSingleton()->Unk48 = 1;
				}

				auto* face = m_actor->GetFaceGenNiNode();
				if (face)
				{
					face->UpdateModelFace();
				}

				return true;
			}

			return false;
		}

		return false;
	}
}
