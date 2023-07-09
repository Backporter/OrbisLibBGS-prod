#pragma once

#include "../F/FormTypes.h"

namespace ConsoleRE
{
	class Actor;
	class BGSEntryPointFunctionData;
	class TESFile;

	class BGSPerkEntry
	{
	public:
		virtual bool                CheckConditionFilters(uint32_t a_numArgs, void* a_args);
		virtual uint32_t            GetFunction();
		virtual void*				GetFunctionData() const;

		virtual ~BGSPerkEntry();

		virtual uint32_t 			GetType() const = 0;
		virtual void                ClearData();
		virtual void                InitItem(TESFile* a_owner);
		virtual bool                Load(TESFile* a_file);
		virtual void                SetParent(BGSPerk* a_parent);
		virtual uint16_t   			GetID() const;
		virtual void                ApplyPerkEntry(Actor* a_actor) = 0;
		virtual void                RemovePerkEntry(Actor* a_actor) = 0;
	public:
		uint8_t  rank;
		uint8_t  priority;
	};
	static_assert(sizeof(BGSPerkEntry) == 0x10);
}