#pragma once

#include "../T/TESForm.h"

namespace ConsoleRE
{
	class TESNPC;
	class BGSAssociationType;

	class BGSRelationship : public TESForm 
	{
	public:
		static constexpr int TypeID = 121;
		
		~BGSRelationship() override;
	public:
		TESNPC*												npc1;
		TESNPC*												npc2;
		BGSAssociationType*									assocType;
		uint8_t												level;
		uint8_t												unk39;
		uint8_t												unk3A;
		uint8_t												flags;
		uint32_t											pad3C;
	};
}