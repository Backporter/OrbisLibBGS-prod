#pragma once

#include "../T/TESDescription.h"
#include "../T/TESForm.h"

namespace ConsoleRE
{
	class BGSCollisionLayer : public TESForm, public TESDescription
	{
	public:
		static constexpr int TypeID = 132;
	public:
		~BGSCollisionLayer() override;

		// override (TESForm)
		void ClearData() override;
		bool Load(TESFile* a_mod) override;
		void InitItemImpl() override;
		void SetDelete(bool a_set) override;
	public:
		uint32_t								collisionIdx;
		Color									debugColor;
		uint32_t								flags;
		uint32_t								pad3C;
		BSFixedString							name;
		BSTArray<BGSCollisionLayer*>			collidesWith;
	};
	static_assert(sizeof(BGSCollisionLayer) == 0x58);
}