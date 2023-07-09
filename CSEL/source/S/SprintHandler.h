#pragma once
#include "../H/HeldStateHandler.h"

namespace ConsoleRE
{
	class SprintHandler : public HeldStateHandler
	{
	public:
		virtual ~SprintHandler();

		bool CanProcess(InputEvent* a_event) override;
	};
}