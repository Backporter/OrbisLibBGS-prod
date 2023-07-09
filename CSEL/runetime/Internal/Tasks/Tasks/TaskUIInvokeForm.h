#pragma once

#include "../Tasklet.h"

#include "../../../../source/B/BSFixedString.h"

#include <stdint.h>

namespace Tasks
{
	class TaskUIInvokeForm : public Task::Tasklet
	{
	public:
		TaskUIInvokeForm(const char* a_name, const char* a_target, uint64_t a_Form, uint32_t a_FormID);
		~TaskUIInvokeForm() override = default;

		// override (Task::Tasklet)
		bool Invoke() override;
	public:
		ConsoleRE::BSFixedString m_name;
		ConsoleRE::BSFixedString m_target;
		uint64_t				 m_Form;
		uint32_t				 m_FormID;
	};

}