#pragma once

#include "../Tasklet.h"

#include "../../../../source/A/Actor.h"

#include <stdint.h>

namespace Tasks
{
	class TaskUpdateExpression : public Task::Tasklet
	{
	public:
		TaskUpdateExpression(ConsoleRE::Actor* a_actor, uint8_t a_type, uint16_t a_index, float a_value);
		~TaskUpdateExpression() override = default;

		// override (Task::Tasklet)
		bool Invoke() override;
	public:
		ConsoleRE::Actor*		m_actor;
		float					m_value;
		uint16_t				m_index;
		uint8_t					m_type;
	};
}