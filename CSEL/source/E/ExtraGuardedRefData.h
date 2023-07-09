#pragma once

#include "../B/BSExtraData.h"
#include "../B/BSTArray.h"
#include "../E/ExtraDataTypes.h"

namespace ConsoleRE
{
	class ExtraGuardedRefData : public BSExtraData
	{
	public:
		static constexpr int TypeID = ExtraDataType<ExtraDataTypes::kGuardedRefData>;

		struct GuardInfo
		{
			uint32_t      guard;
			uint32_t	  unk4;
			uint32_t	  unk8;
		};
		static_assert(sizeof(GuardInfo) == 0xC);
	public:
		~ExtraGuardedRefData();

		// override (BSExtraData)
		uint32_t GetType() const override;
		bool     IsNotEqual(const BSExtraData* a_rhs) const override;
	public:
		BSTArray<GuardInfo> guards;
	};
}