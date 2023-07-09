#pragma once

#include "../B/BGSIdleCollection.h"
#include "../T/TESBoundObject.h"
#include "../T/TESModel.h"

namespace ConsoleRE
{
	class BGSIdleMarker : public TESBoundObject, public TESModel, public BGSIdleCollection
	{
	public:
		static constexpr int TypeID = 47;

		~BGSIdleMarker() override;
	public:
	};
	static_assert(sizeof(BGSIdleMarker) == 0x70);
}