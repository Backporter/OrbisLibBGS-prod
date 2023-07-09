#pragma once

#include "../T/TESObjectACTI.h"

namespace ConsoleRE
{
	class TESObjectREFR;
	class BGSVoiceType;

	class BGSTalkingActivator : public TESObjectACTI
	{
	public:
		static constexpr int TypeID = 25;
	public:
		~BGSTalkingActivator() override;

		// override (TESObjectACTI)
		void                        InitializeData() override;
		bool                        Load(TESFile* a_mod) override;
		void                        SaveGame(BGSSaveFormBuffer* a_buf) override;
		void                        LoadGame(BGSLoadFormBuffer* a_buf) override;
		void                        Revert(BGSLoadFormBuffer* a_buf) override;
		void                        InitItemImpl() override;
		bool                        GetDangerous() const override;
		bool                        Activate(TESObjectREFR* a_targetRef, TESObjectREFR* a_activatorRef, uint8_t a_arg3, TESBoundObject* a_arg4, int32_t a_targetCount) override;
		void                        SetObjectVoiceType(BGSVoiceType* a_voiceType) override;
		BGSVoiceType* 				GetObjectVoiceType() const override;
	public:
		TESObjectREFR* tempRef;
		BGSVoiceType*  voiceType;
	};
	static_assert(sizeof(BGSTalkingActivator) == 0xD0);
}