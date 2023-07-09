#pragma once

#include "../T/TESBoundAnimObject.h"

namespace ConsoleRE
{
	class BGSSoundDescriptorForm;

	class TESSound : public TESBoundAnimObject
	{
	public:
		static constexpr int TypeID = 15;
	public:
		~TESSound() override;

		// override (TESBoundAnimObject)
		void        InitializeData() override;
		bool        Load(TESFile* a_mod) override;
		void        InitItemImpl() override;
		bool        SetFormEditorID(const char* a_str) override;
		void        UnClone3D(TESObjectREFR* a_ref) override;
		NiAVObject* Clone3D(TESObjectREFR* a_ref) override;
	public:
		BGSSoundDescriptorForm* descriptor;
	};
	static_assert(sizeof(TESSound) == 0x30);
}