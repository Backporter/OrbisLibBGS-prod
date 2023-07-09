#pragma once

namespace ConsoleRE
{
	struct PerkRankData;

	class PerkRankVisitor
	{
	public:
		virtual bool Accept(PerkRankData*) = 0;
	};
}