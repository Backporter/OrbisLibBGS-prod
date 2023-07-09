#pragma once

#include "../B/BSFixedString.h"
#include "../F/FormTypes.h"
#include "../T/TESCondition.h"
#include "../T/TESForm.h"

namespace ConsoleRE
{
	struct TOPIC_INFO_DATA
	{
	public:
		enum class TOPIC_INFO_FLAGS
		{
			kNone = 0,
			kStartSceneOnEnd = 1 << 0,
			kRandom = 1 << 1,
			kSayOnce = 1 << 2,
			kRequiresPlayerActivation = 1 << 3,
			kInfoRefusal = 1 << 4,
			kRandomEnd = 1 << 5,
			kEndRunningScene = 1 << 6,
			kIsForceGreet = 1 << 7,
			kPlayerAddress = 1 << 8,
			kForceSubtitle = 1 << 9,
			kCanMoveWhileGreeting = 1 << 10,
			kNoLIPFile = 1 << 11,
			kPostProcess = 1 << 12,
			kCustomSoundOutput = 1 << 13,
			kSpendsFavorPoints = 1 << 14
		};
	public:
		float GetResetHours() { return static_cast<float>(timeUntilReset); }
	public:
		uint16_t flags;
		uint16_t timeUntilReset;
	};
	static_assert(sizeof(TOPIC_INFO_DATA) == 0x4);

	class TESTopicInfo : public TESForm
	{
	public:
		static constexpr int TypeID = 76;
	public:
		~TESTopicInfo() override;

		// override (TESForm)
		void InitializeData() override;
		void ClearData() override;
		bool Load(TESFile* a_mod) override;
		void LoadGame(BGSLoadFormBuffer* a_buf) override;
		void Revert(BGSLoadFormBuffer* a_buf) override;
		void InitItemImpl() override;
		void GetFormDetailedString(char* a_buf, uint32_t a_bufLen) override;
		void SetAltered(bool a_set) override;
		bool BelongsInGroup(FORM* a_form, bool a_allowParentGroups, bool a_currentOnly) override;
		void CreateGroupData(FORM* a_form, FORM_GROUP* a_group) override;
	public:
		TESTopic*									parentTopic;
		TESTopicInfo*								dataInfo;
		TESCondition								objConditions;
		uint16_t									infoIndex;
		bool										saidOnce;
		uint8_t										favorLevel;
		TOPIC_INFO_DATA								data;
		uint32_t									fileOffset;
	};
	static_assert(sizeof(TESTopicInfo) == 0x48);
}