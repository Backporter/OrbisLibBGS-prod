#pragma once

#include "../T/TESBoundObject.h"
#include "../T/TESModelTextureSwap.h"

namespace ConsoleRE
{
	class BGSStaticCollection : public TESBoundObject, public TESModelTextureSwap
	{
	public:
		static constexpr int TypeID = 35;
	public:
		~BGSStaticCollection() override;

		// override (TESBoundObject)
		void ClearData() override;
		bool Load(TESFile* a_mod) override;
		void InitItemImpl() override;
	public:
	};
	static_assert(sizeof(BGSStaticCollection) == 0x60);

}