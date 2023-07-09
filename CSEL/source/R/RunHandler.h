#pragma once
#include "../H/HeldStateHandler.h"

namespace ConsoleRE
{
	class RunHandler : public HeldStateHandler
	{
	public:
		virtual ~RunHandler();
	
		bool CanProcess(InputEvent* a_event) override;                                  // 01
	};
}