#pragma once

#include "../B/BGSDestructibleObjectForm.h"
#include "../T/TESFullName.h"
#include "../T/TESObjectSTAT.h"

namespace ConsoleRE
{
	struct MOVABLE_STATIC_DATA
	{
	public:
		enum class Flag
		{
			kNone = 0,
			kOnLocalMap = 1 << 0
		};
	public:
		uint8_t flags;
	};
	static_assert(sizeof(MOVABLE_STATIC_DATA) == 0x1);

	class BGSMovableStatic : public TESFullName, public BGSDestructibleObjectForm, public TESObjectSTAT
	{
	public:
		static constexpr int TypeID = 36;
	public:
		~BGSMovableStatic() override;

		// override (TESObjectSTAT)
		void InitializeData() override;
		bool Load(TESFile* a_mod) override;
		void InitItemImpl() override;
	public:
		BGSSoundDescriptorForm* soundLoop;
		MOVABLE_STATIC_DATA		data;
	};
	static_assert(sizeof(BGSMovableStatic) == 0xA8);
}