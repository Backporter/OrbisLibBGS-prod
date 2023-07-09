#pragma once

#include "../T/TESBoundObject.h"
#include "../T/TESModelTextureSwap.h"

namespace ConsoleRE
{
	class BGSArtObject : public TESBoundObject, public TESModelTextureSwap
	{
	public:
		static constexpr int TypeID = 125;
		
		struct Data
		{
		public:
			uint32_t artType;
		};
		static_assert(sizeof(Data) == 0x4);
	public:
		~BGSArtObject() override;

		// override (TESBoundObject)
		bool Load(TESFile* a_mod) override;
		void InitItemImpl() override;
	public:
		Data	data;
	};
	static_assert(sizeof(BGSArtObject) == 0x60);
}