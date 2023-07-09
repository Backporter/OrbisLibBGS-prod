#pragma once

#include "../B/BSExtraData.h"
#include "../B/BSPointerHandle.h"
#include "../E/ExtraDataTypes.h"

namespace ConsoleRE
{
	class ExtraSayToTopicInfo : public BSExtraData
	{
	public:
		static constexpr int TypeID = ExtraDataType<ExtraDataTypes::kSayTopicInfo>;
	public:
		~ExtraSayToTopicInfo();

		// override (BSExtraData)
		uint32_t GetType() const override;
	public:
		TESTopic*			topic;
		uint8_t				unk18;
		uint8_t				pad19;
		uint16_t			pad1A;
		float				subtitleSpeechDelay;
		BGSDialogueBranch*	exclusiveBranch;
		int32_t				unk28;
		uint8_t				unk2C;
		uint8_t				pad2D;
		uint16_t			pad2E;
		uint32_t			unk30;
		uint32_t			pad34;
		DialogueItem*		item;
	};
	static_assert(sizeof(ExtraSayToTopicInfo) == 0x40);
}