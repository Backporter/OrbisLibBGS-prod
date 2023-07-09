#pragma once

#include "../T/TESProduceForm.h"
#include "../T/TESObjectACTI.h"

namespace ConsoleRE
{
	class TESFlora : public TESObjectACTI,  public TESProduceForm 
	{
	public:
		static constexpr int TypeID = 39;
		TESFlora();
		virtual ~TESFlora();
	public:

	};
}