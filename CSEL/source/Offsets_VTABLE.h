#pragma once

#include "../../OrbisUtil/include/Relocation.h"

#include <array>

namespace ConsoleRE
{
	inline std::array<Relocation<uintptr_t>, 1>  VTABLE_WeaponRightSwingHandler 
	{ 
		Relocation<uintptr_t>("WeaponRightSwingHandler::Vtbl", 0x1D6CB58)
	};

	inline std::array<Relocation<uintptr_t>, 1>  VTABLE_WeaponLeftSwingHandler 
	{ 
		Relocation<uintptr_t>("WeaponLeftSwingHandler::Vtbl", 0x1D6CB90)
	};

	inline std::array<Relocation<uintptr_t>, 1>  VTABLE_RightHandSpellFireHandler 
	{ 
		Relocation<uintptr_t>("RightHandSpellFireHandler::Vtbl", 0x1D6CA10)
	};

	inline std::array<Relocation<uintptr_t>, 1>  VTABLE_LeftHandSpellFireHandler 
	{ 
		Relocation<uintptr_t>("LeftHandSpellFireHandler::Vtbl", 0x1D6C9C8)
	};

	inline std::array<Relocation<uintptr_t>, 1>  VTABLE_RightHandSpellCastHandler 
	{ 
		Relocation<uintptr_t>("RightHandSpellCastHandler::Vtbl", 0x1D6CAD8)
	};

	inline std::array<Relocation<uintptr_t>, 1>  VTABLE_LeftHandSpellCastHandler 
	{ 
		Relocation<uintptr_t>("LeftHandSpellCastHandler::Vtbl", 0x1D6CA98)
	};

	inline std::array<Relocation<uintptr_t>, 1>  VTABLE_VoiceSpellCastHandler 
	{ 
		Relocation<uintptr_t>("VoiceSpellCastHandler::Vtbl", 0x1D6CB18)
	};

	inline std::array<Relocation<uintptr_t>, 1>  VTABLE_VoiceSpellFireHandler 
	{ 
		Relocation<uintptr_t>("VoiceSpellFireHandler::Vtbl", 0x1D6CA58)
	};

	inline std::array<Relocation<uintptr_t>, 1>  VTABLE_BowDrawnHandler 
	{ 
		Relocation<uintptr_t>("BowDrawnHandler::Vtbl", 0x1D6D418)
	};

	inline std::array<Relocation<uintptr_t>, 1>  VTABLE_BowReleaseHandler 
	{ 
		Relocation<uintptr_t>("BowReleaseHandler::Vtbl", 0x1D6D458)
	};

	inline std::array<Relocation<uintptr_t>, 1>  VTABLE_WeaponBeginDrawRightHandler 
	{ 
		Relocation<uintptr_t>("WeaponBeginDrawRightHandler::Vtbl", 0x1D6CBD8)
	};

	inline std::array<Relocation<uintptr_t>, 1>  VTABLE_WeaponBeginSheatheRightHandler 
	{ 
		Relocation<uintptr_t>("WeaponBeginSheatheRightHandler::Vtbl", 0x1D6CC18)
	};

	inline std::array<Relocation<uintptr_t>, 1>  VTABLE_RightHandWeaponDrawHandler 
	{ 
		Relocation<uintptr_t>("RightHandWeaponDrawHandler::Vtbl", 0x1D6CCD8)
	};

	inline std::array<Relocation<uintptr_t>, 1>  VTABLE_RightHandWeaponSheatheHandler 
	{ 
		Relocation<uintptr_t>("RightHandWeaponSheatheHandler::Vtbl", 0x1D6CD18)
	};

	inline std::array<Relocation<uintptr_t>, 1> VTABLE_MenuOpenHandler
	{
		Relocation<uintptr_t>("MenuOpenHandler:Vtbl", 0x1D96CF0)
	};

	inline std::array<Relocation<uintptr_t>, 1> VTABLE_FavoritesHandler
	{
		Relocation<uintptr_t>("FavoritesHandler:Vtbl", 0x1D96D50)
	};

	inline std::array<Relocation<uintptr_t>, 1>  VTABLE_ActivateHandler
	{
		Relocation<uintptr_t>("ActivateHandler:Vtbl", 0x1D6B520)
	};

	inline std::array<Relocation<uintptr_t>, 1>  VTABLE_AttackBlockHandler
	{
		Relocation<uintptr_t>("AttackBlockHandler:Vtbl", 0x1D6B650)
	};

	inline std::array<Relocation<uintptr_t>, 1>  VTABLE_AutoMoveHandler
	{
		Relocation<uintptr_t>("AutoMoveHandler:Vtbl", 0x1D6B460)
	};

	inline std::array<Relocation<uintptr_t>, 1>  VTABLE_FirstPersonState
	{
		Relocation<uintptr_t>("FirstPersonState:Vtbl", 0x1D93C38)
	};

	inline std::array<Relocation<uintptr_t>, 1>  VTABLE_JumpHandler
	{
		Relocation<uintptr_t>("JumpHandler:Vtbl", 0x1D6B590)
	};

	inline std::array<Relocation<uintptr_t>, 1>  VTABLE_LookHandler
	{
		Relocation<uintptr_t>("LookHandler:Vtbl", 0x1D6B330)
	};

	inline std::array<Relocation<uintptr_t>, 1>  VTABLE_MovementHandler
	{
		Relocation<uintptr_t>("MovementHandler:Vtbl", 0x1D6B2D0)
	};

	inline std::array<Relocation<uintptr_t>, 1>  VTABLE_ReadyWeaponHandler
	{
		Relocation<uintptr_t>("ReadyWeaponHandler:Vtbl", 0x1D6B400)
	};

	inline std::array<Relocation<uintptr_t>, 1>  VTABLE_RunHandler
	{
		Relocation<uintptr_t>("RunHandler:Vtbl", 0x1D6B6C0)
	};

	inline std::array<Relocation<uintptr_t>, 1>  VTABLE_ShoutHandler
	{
		Relocation<uintptr_t>("ShoutHandler:Vtbl", 0x1D6B5F0)
	};

	inline std::array<Relocation<uintptr_t>, 1>  VTABLE_SneakHandler
	{
		Relocation<uintptr_t>("SneakHandler:Vtbl", 0x1D6B730)
	};

	inline std::array<Relocation<uintptr_t>, 1>  VTABLE_SprintHandler
	{
		Relocation<uintptr_t>("SprintHandler:Vtbl", 0x1D6B390)
	};

	inline std::array<Relocation<uintptr_t>, 1>  VTABLE_ThirdPersonState
	{
		Relocation<uintptr_t>("ThirdPersonState:Vtbl", 0x1D941E8)
	};

	inline std::array<Relocation<uintptr_t>, 1>  VTABLE_TogglePOVHandler
	{
		Relocation<uintptr_t>("TogglePOVHandler:Vtbl", 0x1D6B790)
	};

	inline std::array<Relocation<uintptr_t>, 1>  VTABLE_ToggleRunHandler
	{
		Relocation<uintptr_t>("ToggleRunHandler:Vtbl", 0x1D6B4C0)
	};
}