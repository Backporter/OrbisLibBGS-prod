#pragma once

#include "../B/BSTArray.h"
#include "../B/BGSBodyPartData.h"

#include "../T/TESForm.h"
#include "../T/TESModel.h"
#include "../T/TESActorBase.h"

namespace ConsoleRE
{
	class BGSBodyPartData;

	// 0x180
	class BGSRagdoll : public TESForm, public TESModel
	{
	public:
		static constexpr int TypeID = 106;
		virtual ~BGSRagdoll();
	public:
		uint64_t		 unk048;
		uint64_t		 unk050;
		uint64_t		 unk058;
		uint64_t		 unk060;
		uint64_t		 unk068;
		uint64_t		 unk070;
		uint64_t		 unk078;
		uint64_t		 unk080;
		uint64_t		 unk088;
		uint64_t		 unk090;
		BSTArray<void*>  unk098;
		uint64_t		 unk0A8;
		uint64_t		 unk0B0;
		uint64_t		 unk0B8;
		uint64_t		 unk0C0;
		BSTArray<void*>  unk0C8;
		BSTArray<void*>  unk0D8;
		uint64_t		 unk0E8;
		BSTArray<void*>  unk0F0;
		BSTArray<void*>  unk100;
		uint64_t		 unk110;
		BSTArray<void*>  unk118;
		BSTArray<void*>  unk128;
		uint64_t		 unk138;
		uint64_t		 unk140;
		uint64_t		 unk148;
		uint64_t		 unk150;
		uint64_t		 unk158;
		uint64_t		 unk160;
		uint64_t		 unk168;
		BGSBodyPartData* unk170;
		TESActorBase*    unk178;
	};
	static_assert(sizeof(BGSRagdoll) == 0x180, "");
}