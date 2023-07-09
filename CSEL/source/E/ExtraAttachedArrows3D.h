#pragma once

#include "../B/BSExtraData.h"
#include "../B/BSPointerHandle.h"
#include "../E/ExtraDataTypes.h"

namespace ConsoleRE
{
	class ExtraAttachedArrows3D : public BSExtraData
	{
	public:
		static constexpr int TypeID = ExtraDataType<ExtraDataTypes::kAttachedArrows3D>;

		struct DataItem
		{
		public:
			NiPointer<NiAVObject> arrow3D;
			uint64_t			  timeStamp;
			BGSProjectile*        source;
		};
		static_assert(sizeof(DataItem) == 0x18);
	public:
		~ExtraAttachedArrows3D() override;

		// override (BSExtraData)
		uint32_t GetType() const override;
		bool     IsNotEqual(const BSExtraData* a_rhs) const override;
	public:
		BSTArray<DataItem>	data;
		uint16_t			nextStorage;
		uint16_t			oldestStorage;
	};
	static_assert(sizeof(ExtraAttachedArrows3D) == 0x28);
}