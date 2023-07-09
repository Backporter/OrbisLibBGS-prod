#pragma once

#include "../B/BSIMusicTrack.h"
#include "../T/TESCondition.h"

namespace ConsoleRE
{
	class TESFile;
	class TESForm;

	class BGSMusicTrack : public BSIMusicTrack
	{
	public:
		~BGSMusicTrack() override;

		// override (BSIMusicTrack)
		bool TestCanPlay() const override;

		// add
		virtual void InitItem(TESForm* a_form);
		virtual void Load(TESFile* a_mod) = 0;
	public:
		TESCondition  conditions;
		uint32_t	  unk18;
	};
	static_assert(sizeof(BGSMusicTrack) == 0x20);
}