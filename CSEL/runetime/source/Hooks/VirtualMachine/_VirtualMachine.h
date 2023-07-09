#pragma once

#include "../../../../../OrbisUtil/include/Relocation.h"

#include "../../../../source/V/VirtualMachine.h"

namespace VirtualMachine
{
	// _t
	using bfunc_t = bool(ConsoleRE::BSScript::Internal::VirtualMachine*, void*, void*);
	using vfunc_t = void(ConsoleRE::BSScript::Internal::VirtualMachine*);
	using ffunc_t = void(ConsoleRE::BSScript::Internal::VirtualMachine*, uint64_t);

	// rel
	extern Relocation<bfunc_t*> LoadGameFunc;
	extern Relocation<bfunc_t*> SaveGameFunc;
	extern Relocation<vfunc_t*> ReverGameFunc;
	extern Relocation<ffunc_t*> FormDeletionFunc;

	//
	bool LoadGameHook(ConsoleRE::BSScript::Internal::VirtualMachine* a_this, void* a_unk2, void* a_unk3);
	bool SaveGameHook(ConsoleRE::BSScript::Internal::VirtualMachine* a_this, void* a_unk2, void* a_unk3);
	void RevertGameHook(ConsoleRE::BSScript::Internal::VirtualMachine* a_this);
	void FormDeletionHook(ConsoleRE::BSScript::Internal::VirtualMachine* a_this, uint64_t handle);
}