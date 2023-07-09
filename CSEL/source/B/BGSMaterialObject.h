#pragma once

#include "../B/BSMaterialObject.h"
#include "../B/BSString.h"
#include "../B/BSTArray.h"
#include "../T/TESForm.h"
#include "../T/TESModel.h"

namespace ConsoleRE
{
	class BGSMaterialObject : public TESForm, public TESModel, public BSMaterialObject
	{
	public:
		static constexpr int TypeID = 126;
		
		struct FILE_DATA
		{
			void*         buffer;
			uint32_t	  bufferSize;
			uint32_t	  pad0C;
		};
		static_assert(sizeof(FILE_DATA) == 0x10);
	public:
		~BGSMaterialObject() override;

		// override (TESForm)
		void ClearData() override;
		bool Load(TESFile* a_mod) override;

		// override (BSMaterialObject)
		void EnsureLoaded() override;
	public:
		BSTArray<FILE_DATA> fileData;
	};
	static_assert(sizeof(BGSMaterialObject) == 0xA8);
}