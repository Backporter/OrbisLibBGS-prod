#pragma once

#include "../B/BSPointerHandle.h"
#include "../B/BSTArray.h"
#include "../B/BSTList.h"
#include "../B/BSTSingleton.h"
#include "../F/FormTypes.h"
#include "../N/NiTArray.h"
// #include "../N/NiTList.h"
#include "../T/TESForm.h"

namespace ConsoleRE
{
	class BGSPrimitive;
	class InventoryChanges;
	class NiPoint3;
	class TESFile;
	class TESRegionDataManager;
	class TESRegionList;

	class TESObjectList;

	// confirmed name.
	class TESDataHandler
	{
	public:
		// 0xB07F0
		TESDataHandler() = delete;
		~TESDataHandler() = delete;

		static TESDataHandler*	GetSingleton();

		uint32_t				LoadScripts();
		TESForm*				LookupForm(uint32_t a_localFormID, const char* a_modName);

		template <class T>
		T*						LookupForm(uint32_t a_localFormID, const char* a_modName);

		TESFile*				LookupModByName(const char* a_modName);
		uint8_t					GetModIndex(const char* a_modName);

		TESFile*				LookupLoadedModByName(const char* a_modName);
		TESFile*				LookupLoadedModByIndex(uint8_t a_index);
		uint8_t					GetLoadedModIndex(const char* a_modName);

		TESFile*				LookupLoadedLightModByName(const char* a_modName);
		TESFile*				LookupLoadedLightModByIndex(uint16_t a_index);
		uint16_t				GetLoadedLightModIndex(const char* a_modName);
		bool					IsGeneratedID(uint32_t a_formID);

		BSTArray<TESForm*>&		GetFormArray(uint32_t a_formType);

		template <typename T>
		BSTArray<T*>&			GetFormArray();

		ObjectRefHandle			CreateReferenceAtLocation(TESBoundObject* a_base, const NiPoint3& a_location, const NiPoint3& a_rotation, TESObjectCELL* a_targetCell, TESWorldSpace* a_selfWorldSpace, TESObjectREFR* a_alreadyCreatedRef, BGSPrimitive* a_primitive, const ObjectRefHandle& a_linkedRoomRefHandle, bool a_forcePersist, bool a_arg11);
	public:
		TESObjectList*					  Unk000;
		BSTArray<TESForm*>				  FormsArray[0x8A];
		TESRegionList*					  Unk8A8;
		NiTPrimitiveArray<TESObjectCELL*> Unk8B0;
		NiTPrimitiveArray<BGSAddonNode*>  Unk8C8;
		char							  UnkE80[0x18];
		uint32_t						  Unk8F8;
		uint32_t						  Unk8FC;
		void*							  Unk900;
		BSSimpleList<TESFile*>			  Unk908;			// ?
		BSTArray<TESFile*>				  Unk918;			// ESMs/ESP's
		BSTArray<TESFile*>				  Unk928;			// ESL's only
		bool                              Unk938;
		bool                              Unk939;
		bool                              Unk93A;
		bool                              Unk93B;
		bool                              Unk93C;
		bool                              Unk93D;
		bool                              Unk93E;
		bool                              Unk93F;
		bool                              Unk940;
		bool                              Unk941;
		uint8_t							  unk942;
		uint8_t							  unk943;         
		uint32_t						  unk944;
		TESRegionDataManager*			  unk948;
	};
	static_assert(sizeof(TESDataHandler) == 0x950);
	static_assert(offsetof(TESDataHandler, Unk918) == 0x918);
	static_assert(offsetof(TESDataHandler, Unk928) == 0x928);

	template <class T>
	T* TESDataHandler::LookupForm(uint32_t a_localFormID, const char* a_modName)
	{
		auto form = LookupForm(a_localFormID, a_modName);
		if (!form)
		{
			return nullptr;
		}

		return form->FormType == T::TypeID ? static_cast<T*>(form) : nullptr;
	}
	
	template <class T>
	BSTArray<T*>& TESDataHandler::GetFormArray()
	{
		return reinterpret_cast<BSTArray<T*>&>(GetFormArray(T::TypeID));
	}
}