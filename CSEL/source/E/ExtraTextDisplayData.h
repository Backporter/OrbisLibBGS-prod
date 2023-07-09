#pragma once

#include "../B/BSExtraData.h"
#include "../B/BSFixedString.h"
#include "../E/ExtraDataTypes.h"

namespace ConsoleRE
{
	class BGSMessage;
	class TESBoundObject;
	class TESQuest;

	// 0x38
	class ExtraTextDisplayData : public BSExtraData
	{
	public:
		static constexpr int TypeID = 153;

		enum class DisplayDataType
		{
			kUninitialized = -1,
			kCustomName = -2
		};
	public:
		ExtraTextDisplayData();
		explicit ExtraTextDisplayData(const char* a_name);
		ExtraTextDisplayData(TESBoundObject* a_form, float a_temperFactor);
		~ExtraTextDisplayData() override = default;

		// override (BSExtraData)
		uint32_t GetType() const override;

		//
		const char* GetDisplayName(TESBoundObject* a_baseObject, float a_temperFactor);
		bool		IsPlayerSet();
		void		SetName(const char* a_name);
	public:
		BSFixedString                                   displayName;
		BGSMessage*                                     displayNameText;
		TESQuest*                                       ownerQuest;
		int32_t											ownerInstance; 
		float                                           temperFactor;      
		uint16_t										customNameLength;  
		uint16_t										pad32;
		uint32_t										pad34;
	};
	static_assert(sizeof(ExtraTextDisplayData) == 0x38);
}