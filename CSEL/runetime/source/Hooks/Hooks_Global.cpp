#include "../../../../OrbisUtil/include/MemoryHandler.h"
#include "../../../../OrbisUtil/include/SystemWrapper.h"
#include "../../../../OrbisUtil/include//Logger.h"
#include "../../../../OrbisUtil/include/Relocation.h"
#include "../../../../OrbisUtil/include/Trampoline.h"
#include "../../../../OrbisUtil/Third-Party/herumi/xbayk/6.00/xbyak.h"
#include "../../../../OrbisUtil/include/Macro.h"

#include "../../Version.h"
#include "../Enderal/Enderal.h"

#include "../Hooks/Logger/Logger.h"
#include "../Hooks/Hooks_Global.h"
#include "../Hooks/Papyrus/PapyrusExt.h"
#include "../Hooks/VirtualMachine/_VirtualMachine.h"
#include "../Hooks/Scaleform/ScaleformExt.h"
#include "../Hooks/GFx/GFxExt.h"
#include "../Hooks/PlayerControls/PlayerControls.h"
#include "../Hooks/ItemData/ItemData.h"
#include "../Hooks/CraftingSubMenus/CraftingSubMenus.h"
#include "../Hooks/MessageQueueUI/MessageQueue.h"
#include "../Hooks/Data/Data.h"
#include "../Hooks/SaveLoad/SaveLoad.h"
#include "../Hooks/Misc/Misc.h"
#include "../Hooks/Favorites/Favorites.h"
#include "../Hooks/TaskPool/TaskPool.h"
#include "../Hooks/GameHandles/GameHandles.h"

#include <string.h>
#include <stdio.h>
#include <stdint.h>
#include <iostream>

namespace Runetime
{
	namespace Hooks
	{
		// Addresses
		Relocation<uintptr_t> UIQueueHookAddress                 ("",											0x111DAC5);
		Relocation<uintptr_t> VirtualMachineLogvtbl              ("",											0x1D99AC0);
		Relocation<uintptr_t> SmithingMenuSetRHOOK               ("",											0x9F3E8C);
		Relocation<uintptr_t> CraftingSubMenuSetRRHOOK           ("",											0x9F08FC);
		Relocation<uintptr_t> AlchemyMenuSetRRHOOK               ("",											0x9FC1FC);
		Relocation<uintptr_t> ScaleformHookAddress               ("",											0x111723B);
		Relocation<uintptr_t> GFxLoaderHook                      ("",											0x6A2A35);
		Relocation<uintptr_t> PapyrusHookAddress                 ("",											0xAE0BA8);
		
		Relocation<uintptr_t> LoadGameHookAddress				 ("",											0xAF4F41);
		Relocation<uintptr_t> RevertGameHookAddress				 ("",											0xAF5081);
		Relocation<uintptr_t> RevertGameHookAddress2			 ("",											0xAF67A9);
		Relocation<uintptr_t> SaveGameHookAddress				 ("",											0xAF4A9C);
		Relocation<uintptr_t> FormDeletionHookAddress			 ("",											0xAEC0BE);

		Relocation<uintptr_t> FormLoadingHookAddress             ("",											0x6A6568);
		Relocation<uintptr_t> PlayerControlsHook                 ("",											0x6A55B1);
		Relocation<uintptr_t> StandardItemDataHook               ("",											0x9DC683);
		Relocation<uintptr_t> MagicItemDataHook                  ("",											0xA38FE3);
		Relocation<uintptr_t> GameVersionFormatspecifer          ("",											0xAA4D62);
		Relocation<uintptr_t> TaskPoolHookAddress                ("",											0x6A7EAF);
		Relocation<uintptr_t> TaskPoolHookAddress2				 ("",											0x6A939D);

		Relocation<uintptr_t> MiscUpdateEquipmentHookAddress     ("",                                           0x7CE971);
		Relocation<uintptr_t> MiscCameriaStateHookAddress        ("",                                           0x5CCA80);
		Relocation<uintptr_t> RenderTargetHook                   ("",                                           0xF9BD90);
		Relocation<uint32_t*> RenderTentsWidth                   ("",                                           0X37DA6F4);
		Relocation<uint32_t*> RenderTentsHeight                  ("",                                           0X37DA6F8);
		Relocation<uintptr_t> SetViewScaleModevtblHook           ("",                                           0x1E29DB0);
		Relocation<uintptr_t> EnchantConstructMenuSetHook        ("",                                           0x9F6F39);
		Relocation<uintptr_t> AlchemyMenuIndexFixUpHookAddress   ("",                                           0x9FBE21);
		Relocation<uintptr_t> FavoritesMenuItemSetHookAddress    ("",                                           0xA04B08);
		Relocation<uintptr_t> FavoritesMenuMagicSetHookAddress   ("",                                           0xA042AA);
		Relocation<uintptr_t> FavoritesMenuVampireSetHookAddress ("",                                           0xA03FA2);

		Relocation<uint32_t*> g_OpenedContainerOpenType          ("",											0x3199108);
		Relocation<uintptr_t> ContainerCategorizationHookAddress ("",                                           0x9E5CEC);		
		Relocation<uintptr_t> MapMenuMouseWheelHookAddress       ("",											0xA8CCBB);
		Relocation<uintptr_t> BGSKeywordCreateHookAddress        ("",                                           0x2E0F20);
		
		// == savegame ==
		Relocation<uintptr_t>	SaveGameNewGameHookTarget("", 0xA3DE9F);
		// == end of savegame ==


		// vars used by said hook
		char NewGameVersionFormatspecifer[]		   = "(CSEL build " CSEL_VERSION_STRING ") %s.%d";
		char EnderalNewGameVersionFormatspecifer[] = "(CSEL build " CSEL_VERSION_STRING " - Enderal) %s.%d";

		// functions that apply the hook(rather then doing them all in one function this will allow us to know **what** hook leads to a crash very quickly, it also makes this far cleaner)
		// VirtualMachine hoooks.
		void ApplyVMSaveGameHook()			{ PRINT_POS; VirtualMachine::SaveGameFunc = xUtilty::Trampoline::get(xUtilty::Trampoline::kBranch).write_call<5>(SaveGameHookAddress.address(),								FN_AS_RAW_ADDRESS(VirtualMachine::SaveGameHook));																																		      }
		void ApplyVMFormDeletionHook()		{ PRINT_POS; VirtualMachine::FormDeletionFunc = xUtilty::Trampoline::get(xUtilty::Trampoline::kBranch).write_call<5>(FormDeletionHookAddress.address(),						FN_AS_RAW_ADDRESS(VirtualMachine::FormDeletionHook));																																	      }
		void ApplyVMLoadGameHook()			{ PRINT_POS; VirtualMachine::LoadGameFunc =  xUtilty::Trampoline::get(xUtilty::Trampoline::kBranch).write_call<5>(LoadGameHookAddress.address(),							FN_AS_RAW_ADDRESS(VirtualMachine::LoadGameHook));																																		      }
		
		void ApplyVMReverGameHook()			
		{ 
			PRINT_POS; VirtualMachine::ReverGameFunc = xUtilty::Trampoline::get(xUtilty::Trampoline::kBranch).write_call<5>(RevertGameHookAddress.address(),															FN_AS_RAW_ADDRESS(VirtualMachine::RevertGameHook));
			PRINT_POS; xUtilty::Trampoline::get(xUtilty::Trampoline::kBranch).write_call<5>(RevertGameHookAddress2.address(),																							FN_AS_RAW_ADDRESS(VirtualMachine::RevertGameHook)); 
		}

		//other hooks.
		void ApplyLogHook()					{ PRINT_POS; xUtilty::safe_write<uint64_t>(VirtualMachineLogvtbl.address(),																									FN_AS_RAW_ADDRESS(Logger::Write));																																							  }
		void ApplyPapyrusHook()				{ PRINT_POS; Papyrus::_RegisterPapyrusFunctions = xUtilty::Trampoline::get(xUtilty::Trampoline::kBranch).write_call<5>(PapyrusHookAddress.address(),						FN_AS_RAW_ADDRESS(Papyrus::RegisterPapyrus));																																				  }
		void ApplyFormLoadHook()			{ PRINT_POS; xUtilty::Trampoline::get(xUtilty::Trampoline::kBranch).write_call<5>(FormLoadingHookAddress.address(),															FN_AS_RAW_ADDRESS(Data::LoadScripts));																																					      }
		void ApplyUIQueue()					{ PRINT_POS; xUtilty::Trampoline::get(xUtilty::Trampoline::kBranch).write_call<5>(UIQueueHookAddress.address(),																FN_AS_RAW_ADDRESS(MessageQueue::UI::ProcessQueue)); 																																	      }
		void ApplyScaleFormHook()			{ PRINT_POS; xUtilty::Trampoline::get(xUtilty::Trampoline::kBranch).write_call<6>(ScaleformHookAddress.address(),															FN_AS_RAW_ADDRESS(Scaleform::RegisterNewScaleform));																																	      }
		void ApplyScaleFormHook2()			{ PRINT_POS; xUtilty::safe_write<uint64_t>(SetViewScaleModevtblHook.address(),																								FN_AS_RAW_ADDRESS(Scaleform::RegisterNewScaleform));																																	      }
		void ApplyGFxHook()					{ PRINT_POS; GFx::func = xUtilty::Trampoline::get(xUtilty::Trampoline::kBranch).write_call<5>(GFxLoaderHook.address(),														FN_AS_RAW_ADDRESS(GFx::RegisterGFx));																																					      }
		void ApplyPlayerControlsHook()		{ PRINT_POS; RunetimePlayerControls::_RegisterPlayerControlls = xUtilty::Trampoline::get(xUtilty::Trampoline::kBranch).write_call<5>(PlayerControlsHook.address(),			FN_AS_RAW_ADDRESS(RunetimePlayerControls::RegisterPlayerControls));																														      }
		void ApplyStandardItemDataHook()	{ PRINT_POS; xUtilty::Trampoline::get(xUtilty::Trampoline::kBranch).write_call<5>(StandardItemDataHook.address(),															FN_AS_RAW_ADDRESS(ItemData::StandardItemDataHook));																																		      }
		void ApplyMagicItemDataHook()		{ PRINT_POS; xUtilty::Trampoline::get(xUtilty::Trampoline::kBranch).write_call<5>(MagicItemDataHook.address(),																FN_AS_RAW_ADDRESS(ItemData::MagicItemDataHook));																																		      }
		void ApplySmithingMenuSetHook()		{ PRINT_POS; CraftingSubMenusE::SmithingMenuSetR = xUtilty::Trampoline::get(xUtilty::Trampoline::kBranch).write_call<5>(SmithingMenuSetRHOOK.address(),						FN_AS_RAW_ADDRESS(CraftingSubMenusE::SmithingMenuSet));																																	      }
		void ApplyCraftingSubMenuSetHook()	{ PRINT_POS; CraftingSubMenusE::CraftingSubMenuSetR = xUtilty::Trampoline::get(xUtilty::Trampoline::kBranch).write_call<5>(CraftingSubMenuSetRRHOOK.address(),				FN_AS_RAW_ADDRESS(CraftingSubMenusE::CraftingSubMenuSet));																																      }
		void ApplyAlchemyMenuSetHook()		{ PRINT_POS; CraftingSubMenusE::AlchemyMenuSetR = xUtilty::Trampoline::get(xUtilty::Trampoline::kBranch).write_call<5>(AlchemyMenuSetRRHOOK.address(),						FN_AS_RAW_ADDRESS(CraftingSubMenusE::AlchemyMenuSet));																																	      }
		void ApplyNewGameHook()             { PRINT_POS; xUtilty::Trampoline::get(xUtilty::Trampoline::kBranch).write_call<5>(SaveGameNewGameHookTarget.address(),														FN_AS_RAW_ADDRESS(SaveGame::New::NewGame));																																				      }
		void ApplySaveGameHook()            { PRINT_POS; xUtilty::Trampoline::get(xUtilty::Trampoline::kBranch).write_call<5>(SaveGame::Save::savehooktarget.address(),													FN_AS_RAW_ADDRESS(SaveGame::Save::SaveGame));																																			      }
		void ApplyLoadGameHook()            { PRINT_POS; xUtilty::Trampoline::get(xUtilty::Trampoline::kBranch).write_call<5>(SaveGame::Load::loadhooktarget.address(),													FN_AS_RAW_ADDRESS(SaveGame::Load::LoadGame));																																			      }
		void ApplyDeleteGameHook()			{ PRINT_POS;																																																																				      }
		void ApplySaveQueueProcessorHook()  { PRINT_POS; xUtilty::Trampoline::get(xUtilty::Trampoline::kBranch).write_call<5>(SaveGame::Process::processhooktarget.address(),											FN_AS_RAW_ADDRESS(SaveGame::Process::ProcessQueue));																																	      }
		void ApplyEquipmentHook()			{ PRINT_POS; xUtilty::Trampoline::get(xUtilty::Trampoline::kBranch).write_call<5>(MiscUpdateEquipmentHookAddress.address(),													FN_AS_RAW_ADDRESS(Misc::UpdateEquipment));																																				      }
		
		void ApplyTaskPoolHook()            
		{ 
			PRINT_POS; xUtilty::Trampoline::get(xUtilty::Trampoline::kBranch).write_call<5>(TaskPoolHookAddress.address(),																								FN_AS_RAW_ADDRESS(TaskPool::ProcessQueue));	
			PRINT_POS; xUtilty::Trampoline::get(xUtilty::Trampoline::kBranch).write_call<5>(TaskPoolHookAddress2.address(),																								FN_AS_RAW_ADDRESS(TaskPool::ProcessQueue));
		}

		void ApplyCameraStateHook()         { PRINT_POS; xUtilty::Trampoline::get(xUtilty::Trampoline::kBranch).write_branch<6>(MiscCameriaStateHookAddress.address(),													FN_AS_RAW_ADDRESS(Misc::UpdatecameraState)); xUtilty::safe_write<uint8_t>(MiscCameriaStateHookAddress.get() + 6, 0xC3);															  }
		void ApplySaveGameHistorySaver()	{ PRINT_POS; SaveGame::Logs::func = xUtilty::Trampoline::get(xUtilty::Trampoline::kBranch).write_call<5>(SaveGame::Logs::HookTarget.address(),								FN_AS_RAW_ADDRESS(SaveGame::Logs::strcpy_s));																																					      }
		void ApplyHandleHooks()				{ PRINT_POS; GameHandles::Apply();																																																																  }

		// bigger functions that use xbayk..
		void ApplyVersionHook()
		{
			size_t ID = 0;
			if (Enderal::IsEnderal)
			{
				ID = sizeof(EnderalNewGameVersionFormatspecifer);
			}
			else
			{
				ID = sizeof(NewGameVersionFormatspecifer);
			}

			char* Buffer = (char*)xUtilty::Trampoline::get(xUtilty::Trampoline::kBranch).allocate(ID);

			// lea takes 32-bit address, always assert before
			assert((uintptr_t)Buffer <= UINT32_MAX);
			if (Enderal::IsEnderal)
			{
				memcpy(Buffer, EnderalNewGameVersionFormatspecifer, ID);
			}
			else
			{
				memcpy(Buffer, NewGameVersionFormatspecifer, ID);
			}

			// create our xbayk code
			struct DUMMY : Xbyak::CodeGenerator
			{
				DUMMY(char* versionbuf) : Xbyak::CodeGenerator()
				{
					// this will die If its not within a 32-bit distance, you seriously need to assert this otherwise this could cause a crash...
					lea(rdx, ptr[versionbuf]);

					// jump back to after the hook.
					jmp(ptr[rip]);
					dq(GameVersionFormatspecifer.address() + 7);
				}
			};

			//
			auto& localTrampoline = xUtilty::Trampoline::get(xUtilty::Trampoline::kBranch);

			//
			DUMMY xbaykcode(Buffer);
			
			//
			auto buf = localTrampoline.allocate(xbaykcode);
			localTrampoline.write_branch<6>(GameVersionFormatspecifer.address(), buf);
			
			xUtilty::Log::GetSingleton()->Write(xUtilty::Log::logLevel::kInfo, "xbaykcode for ApplyVersionHook: %p", buf);

			//
			xUtilty::safe_write<uint8_t>(GameVersionFormatspecifer.address() + 6, 0x90);
		}

		void ApplyRenderTargetHook()
		{
			// create our xbayk code
			struct DUMMY : Xbyak::CodeGenerator
			{
				DUMMY(uint32_t a_width, uint32_t a_height) : Xbyak::CodeGenerator()
				{
					Xbyak::Label retn;
					cmp(esi, 0xF);
					jnz(retn);
					mov(dword[rdx], a_width);
					mov(dword[rdx + 4], a_height);

					// merged function:
					mov(rax, RenderTentsWidth.address());
					mov(dword[rax], a_width);
					mov(rax, RenderTentsHeight.address());
					mov(dword[rax], a_height);
					jmp(retn);

					L(retn);
					mov(rax, rdx);
					movsxd(rsi, esi);
					jmp(ptr[rip]);
					dq(RenderTargetHook.address() + 6);

				}
			};

			//
			auto& localTrampoline = xUtilty::Trampoline::get(xUtilty::Trampoline::kBranch);

			//
			auto INI = xUtilty::INIHandler::INIHandler::GetSingleton()->GetINIOptions();
			DUMMY xbaykcode(INI->RenderTargetTextureWidth, INI->RenderTargetTextureHeight);

			//
			auto buf = localTrampoline.allocate(xbaykcode);
			localTrampoline.write_branch<6>(RenderTargetHook.address(), buf);

			xUtilty::Log::GetSingleton()->Write(xUtilty::Log::logLevel::kInfo, "xbaykcode for ApplyRenderTargetHook: %p", buf);
		}

		void ApplyEnchantConstructMenuSetHook()
		{
			// create our xbayk code
			struct DUMMY : Xbyak::CodeGenerator
			{
				DUMMY() : Xbyak::CodeGenerator()
				{
					Xbyak::Label retn;
					
					mov(rdx, qword [r13 + 0x18]);

					mov(rax, (uintptr_t)CraftingSubMenusE::CraftingSubMenusEnchantConstructMenuItemChangeEntrySet);
					call(rax);
					jmp(retn);

					L(retn);
					jmp(ptr[rip]);
					dq(EnchantConstructMenuSetHook.address() + 5);

				}
			};

			//
			auto& localTrampoline = xUtilty::Trampoline::get(xUtilty::Trampoline::kBranch);
			
			//
			DUMMY xbaykcode;

			//
			auto buf = localTrampoline.allocate(xbaykcode);
			localTrampoline.write_branch<5>(EnchantConstructMenuSetHook.address(), buf);

			xUtilty::Log::GetSingleton()->Write(xUtilty::Log::logLevel::kInfo, "xbaykcode for ApplyEnchantConstructMenuSetHook: %p", buf);
		}
	
		void ApplyAlchemyMenuIndexFixUpHook()
		{
			// create our xbayk code
			struct DUMMY : Xbyak::CodeGenerator
			{
				DUMMY() : Xbyak::CodeGenerator()
				{
					Xbyak::Label retn;

					// given the ret arg is always zero, we can just highjack it and we'll have everything we need without much code.
					mov(rdx, qword[rsp + 0xA8]);

					// call
					mov(rax, (uintptr_t)CraftingSubMenusE::AlchemyMenuIndexFixUp);
					call(rax);
					jmp(retn);
					
					L(retn);
					jmp(ptr[rip]);
					dq(AlchemyMenuIndexFixUpHookAddress.address() + 5);

				}
			};

			//
			auto& localTrampoline = xUtilty::Trampoline::get(xUtilty::Trampoline::kBranch);

			//
			DUMMY xbaykcode;

			//
			auto buf = localTrampoline.allocate(xbaykcode);
			localTrampoline.write_branch<5>(AlchemyMenuIndexFixUpHookAddress.address(), buf);

			xUtilty::Log::GetSingleton()->Write(xUtilty::Log::logLevel::kInfo, "xbaykcode for ApplyAlchemyMenuIndexFixUpHook: %p", buf);
		}

		void ApplyItemFavoritesMenuSetHook()
		{
			struct DUMMY : Xbyak::CodeGenerator
			{
				DUMMY() : Xbyak::CodeGenerator()
				{
					Xbyak::Label retn;

					// OG
					call(ptr[rax + 0x70]);

					mov(rdi, qword[rsp + 0x48]);
					lea(rsi, ptr[rsp + 0x68]);
					mov(rdx, r14);

					mov(rax, (uintptr_t)Favorites::ItemFavoritesSet);
					call(rax);

					// OG
					mov(rdi, r14);
					
					// return:
					jmp(retn);

					// ez
					L(retn);
					jmp(ptr[rip]);
					dq(FavoritesMenuItemSetHookAddress.address() + 6);

				}
			};

			//
			auto& localTrampoline = xUtilty::Trampoline::get(xUtilty::Trampoline::kBranch);

			//
			DUMMY xbaykcode;
			
			//
			auto buf = localTrampoline.allocate(xbaykcode);
			localTrampoline.write_branch<6>(FavoritesMenuItemSetHookAddress.address(), buf);

			xUtilty::Log::GetSingleton()->Write(xUtilty::Log::logLevel::kInfo, "xbaykcode for ApplyItemFavoritesMenuSetHook: %p", buf);
		}
		
		void ApplyMagicFavoritesMenuSetHook()
		{
			struct DUMMY : Xbyak::CodeGenerator
			{
				DUMMY() : Xbyak::CodeGenerator()
				{
					Xbyak::Label retn;

					// OG:
					call(ptr[rax + 0x70]);

					mov(rdi, qword[rbx + 0x10]);
					lea(rsi, ptr[rsp + 0x60]);
					mov(rdx, r12);

					mov(rax, (uintptr_t)Favorites::MagicFavoritesSet);
					call(rax);

					// OG:
					mov(rdi, r12);
					
					// ret;
					jmp(retn);


					// ez
					L(retn);
					jmp(ptr[rip]);
					dq(FavoritesMenuMagicSetHookAddress.address() + 6);

				}
			};

			//
			auto& localTrampoline = xUtilty::Trampoline::get(xUtilty::Trampoline::kBranch);

			//
			DUMMY xbaykcode;
			
			//
			auto buf = localTrampoline.allocate(xbaykcode);
			localTrampoline.write_branch<6>(FavoritesMenuMagicSetHookAddress.address(), buf);

			xUtilty::Log::GetSingleton()->Write(xUtilty::Log::logLevel::kInfo, "xbaykcode for ApplyMagicFavoritesMenuSetHook: %p", buf);
		}

		void ApplyVampireFavoritesMenuSetHook()
		{
			struct DUMMY : Xbyak::CodeGenerator
			{
				DUMMY() : Xbyak::CodeGenerator()
				{
					Xbyak::Label retn;

					call(ptr[rax + 0x70]);

					mov(rdi, qword[r15 + 0x10]);
					lea(rsi, ptr[rsp + 0x60]);
					mov(rdx, r12);

					mov(rax, (uintptr_t)Favorites::MagicFavoritesSet);
					call(rax);

					mov(rdi, r12);
					jmp(retn);

					L(retn);
					jmp(ptr[rip]);
					dq(FavoritesMenuVampireSetHookAddress.address() + 6);

				}
			};

			//
			auto& localTrampoline = xUtilty::Trampoline::get(xUtilty::Trampoline::kBranch);

			//
			DUMMY xbaykcode;
			
			//
			auto buf = localTrampoline.allocate(xbaykcode);
			localTrampoline.write_branch<6>(FavoritesMenuVampireSetHookAddress.address(), buf);

			xUtilty::Log::GetSingleton()->Write(xUtilty::Log::logLevel::kInfo, "xbaykcode for ApplyVampireFavoritesMenuSetHook: %p", buf);
		}

		void ApplyContainerCategorizationHook()
		{
			/*
			if (xUtilty::INIHandler::INIHandler::GetSingleton()->GetINIOptions()->EnableContainerCategorization)
			{
				xUtilty::Notify(".ini enabled container categorization");
				ForceContainerCategorization = 1;
			}

			struct DUMMY : Xbyak::CodeGenerator
			{
				DUMMY() : Xbyak::CodeGenerator()
				{
					Xbyak::Label UseCategories;
					Xbyak::Label NoCatagories;

					mov(rax, (uintptr_t)&ForceContainerCategorization);
					mov(eax, ptr[rax]);
					cmp(eax, 0);
					jnz(UseCategories);

					mov(rax, g_OpenedContainerOpenType.address());
					mov(eax, ptr[rax]);
					cmp(eax, 3);
					jz(UseCategories);
					jmp(NoCatagories);

					L(UseCategories);
					jmp(ptr[rip]);
					dq(ContainerCategorizationHookAddress.address() + 0x9);

					L(NoCatagories);
					jmp(ptr[rip]);
					dq(ContainerCategorizationHookAddress.address() + 0x18);
				}
			};

			//
			auto& localTrampoline = xUtilty::Trampoline::get(xUtilty::Trampoline::kBranch);

			DUMMY xbaykcode;

			auto buf = localTrampoline.allocate(xbaykcode);
			localTrampoline.write_branch<5>(ContainerCategorizationHookAddress.address(), buf);

#if _DEBUG
			PRINT_FMT("xbaykcode %p", buf);
#endif
			*/
		}

		void ApplyMapMenuMouseWheelHook()
		{
			struct DUMMY : Xbyak::CodeGenerator
			{
				DUMMY() : Xbyak::CodeGenerator()
				{
					Xbyak::Label retlbl;
					
					// og
					mov(ptr[rax + 0x3085D], cl);

					// our
					mov(rax, (uintptr_t)&DisableMapMenuMouseWheel);
					mov(al, ptr[rax]);
					jmp(retlbl);

					L(retlbl);
					add(rsp, 0x10);
					pop(rbx);
					pop(r14);
					pop(r15);
					pop(rbp);
					ret();
				}
			};

			//
			auto& localTrampoline = xUtilty::Trampoline::get(xUtilty::Trampoline::kBranch);

			//
			DUMMY xbaykcode;
			
			//
			auto buf = localTrampoline.allocate(xbaykcode);
			localTrampoline.write_branch<6>(MapMenuMouseWheelHookAddress.address(), buf);
			
			xUtilty::Log::GetSingleton()->Write(xUtilty::Log::logLevel::kInfo, "xbaykcode for ApplyMapMenuMouseWheelHook: %p", buf);

			//
			xUtilty::safe_write(MapMenuMouseWheelHookAddress.address() + 6, static_cast<uint16_t>(0x9090));
		}
	}
}