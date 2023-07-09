#pragma once

#include "../Tasklet.h"

#include "../../../../source/A/Actor.h"
#include "../../../../source/B/BSFaceGenManager.h"
#include "../../../../source/B/BSFaceGenNiNode.h"
#include "../../../../source/B/BGSHeadPart.h"
#include "../../../../source/T/TESNPC.h"
#include "../../../../source/T/TESForm.h"

namespace Tasks
{
	using namespace ConsoleRE;

	class TaskUpdateWeight : public Task::Tasklet
	{
	public:
		TaskUpdateWeight(ConsoleRE::Actor* a_actor, float a_delta, uint32_t a_flags, bool a_redrew);
		~TaskUpdateWeight() override = default;

		// override (Task::Tasklet)
		bool Invoke() override;
	public:
		ConsoleRE::Actor*      m_actor;
		float				   m_delta;
		uint32_t			   m_updateFlags;
		bool				   m_redraw;
	};
}