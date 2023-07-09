#pragma once

#include "../A/AutoRegisterFactory.h"
#include "../B/BSTDerivedCreator.h"

namespace ConsoleRE
{
	template <class Derived, class Manager>
	struct AutoRegisterCreator : public AutoRegisterFactory<BSTDerivedCreator<Derived, typename Manager::mapped_type>, Manager>
	{
	public:
		virtual ~AutoRegisterCreator();
	};
}