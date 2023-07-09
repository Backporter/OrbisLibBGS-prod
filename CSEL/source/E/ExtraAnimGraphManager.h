#pragma once

#include "../B/BSExtraData.h"
#include "../B/BSTSmartPointer.h"
#include "../E/ExtraDataTypes.h"

namespace ConsoleRE
{
	class BSAnimationGraphManager;

	class ExtraAnimGraphManager : public BSExtraData
	{
	public:
		static constexpr int TypeID = ExtraDataType<ExtraDataTypes::kAnimGraphManager>;
	public:
		~ExtraAnimGraphManager() override;

		// override (BSExtraData)
		uint32_t GetType() const override;
	public:
		BSTSmartPointer<BSAnimationGraphManager> animGraphMgr;
	};
	static_assert(sizeof(ExtraAnimGraphManager) == 0x18);
}