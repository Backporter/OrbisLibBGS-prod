#pragma once

#include "../T/TESBoundAnimObject.h"
#include "../T/TESLeveledList.h"
#include "../T/TESModelTextureSwap.h"

namespace ConsoleRE
{
	class TESLevCharacter : public TESBoundAnimObject, public TESLeveledList, public TESModelTextureSwap
	{
	public:
		static constexpr int TypeID = 44;
	public:
		~TESLevCharacter() override;

		// override (TESBoundAnimObject)
		bool        Load(TESFile* a_mod) override;
		void        SaveGame(BGSSaveFormBuffer* a_buf) override;
		void        LoadGame(BGSLoadFormBuffer* a_buf) override;
		void        Revert(BGSLoadFormBuffer* a_buf) override;
		void        InitItemImpl() override;
		void        UnClone3D(TESObjectREFR* a_ref) override;
		NiAVObject* Clone3D(TESObjectREFR* a_ref) override;

		// override (TESLeveledList)
		int32_t    GetLevDifferenceMax() override;
		bool	   GetCanContainFormsOfType(uint32_t a_type) const override;
	};
	static_assert(sizeof(TESLevCharacter) == 0x88);

}