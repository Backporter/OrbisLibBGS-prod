#pragma once

#include "../B/BSExtraData.h"
#include "../E/ExtraDataTypes.h"

namespace ConsoleRE
{
	struct RagDollBone
	{
		int8_t		boneID;
		uint8_t		pad01;
		uint16_t	pad02;
		NiPoint3    bonePos;
		NiPoint3    boneRot;
	};
	static_assert(sizeof(RagDollBone) == 0x1C);

	struct RagDollData
	{
		int8_t		 boneCount;
		uint8_t		 pad01;
		uint16_t	 pad02;
		uint32_t	 pad04;
		RagDollBone* bones;
		NiPoint3     bip01Rot;
		uint32_t	 pad1C;
	};
	static_assert(sizeof(RagDollData) == 0x20);

	class ExtraRagDollData : public BSExtraData
	{
	public:
		static constexpr int TypeID = ExtraDataType<ExtraDataTypes::kRagDollData>;
	public:
		~ExtraRagDollData();

		// override (BSExtraData)
		uint32_t GetType() const override;
		bool     IsNotEqual(const BSExtraData* a_rhs) const override;
	public:
		RagDollData* ragDollData;
	};
	static_assert(sizeof(ExtraRagDollData) == 0x18);
}