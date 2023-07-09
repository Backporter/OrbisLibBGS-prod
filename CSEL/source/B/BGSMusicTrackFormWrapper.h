#pragma once

#include "../B/BSIMusicTrack.h"
#include "../T/TESForm.h"

namespace ConsoleRE
{
	class BGSMusicTrack;

	class BGSMusicTrackFormWrapper : public TESForm, public BSIMusicTrack
	{
	public:
		static constexpr int TypeID = 116;
	public:
		~BGSMusicTrackFormWrapper() override;

		// override (TESForm)
		void ClearData() override;
		bool Load(TESFile* a_mod) override;
		void InitItemImpl() override;

		// override (BSIMusicTrack)
		void         DoUpdate() override;
		void         DoPlay() override;
		void         DoPause() override;
		void         DoFinish(bool a_arg1, float a_arg2) override;
		float        GetDurationImpl() const override;
		uint32_t     GetType() const override;
		bool         TestCanPlay() const override;
		uint32_t	 GetMusicStatus() const override;
		void         DoSetDuckingAttenuation(uint16_t a_val) override;
		void         DoClearDucking() override;
	public:
		BGSMusicTrack* track;
	};
	static_assert(sizeof(BGSMusicTrackFormWrapper) == 0x38);
}