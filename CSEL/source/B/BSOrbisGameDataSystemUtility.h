#pragma once

#include "../B/BSGameDataSystemUtility.h"

namespace ConsoleRE
{
	class BSOrbisGameDataSystemUtility : public BSGameDataSystemUtility
	{
	public:
		~BSOrbisGameDataSystemUtility() override;

		// override (BSGameDataSystemUtility)
		void Initialize() override;
	public:
	};
}