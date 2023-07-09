#pragma once

#include "../B/BSAtomic.h"
#include "../B/BSExtraData.h"
#include "../B/BSTArray.h"
#include "../E/ExtraDataTypes.h"
#include "../F/FormTypes.h"

namespace ConsoleRE
{
	class BGSBaseAlias;

	struct BGSRefAliasInstanceData
	{
		TESQuest*                    quest;
		const BGSBaseAlias*          alias;
		const BSTArray<TESPackage*>* instancedPackages;
	};
	static_assert(sizeof(BGSRefAliasInstanceData) == 0x18);

	// 0x30
	class ExtraAliasInstanceArray : public BSExtraData
	{
	public:
		static constexpr int TypeID = ExtraDataType<ExtraDataTypes::kAliasInstanceArray>;
	public:
		ExtraAliasInstanceArray();
		~ExtraAliasInstanceArray() override;

		// override (BSExtraData)
		uint32_t GetType() const override;
	public:
		BSTArray<BGSRefAliasInstanceData*> aliases;
		mutable BSReadWriteLock            lock;
	};
	static_assert(sizeof(ExtraAliasInstanceArray) == 0x30);
}