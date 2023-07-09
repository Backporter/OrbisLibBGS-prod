#pragma once

#include "../../../OrbisUtil/include/Relocation.h"

#include "../B/BSAtomic.h"
#include "../B/BSFixedString.h"
#include "../B/BSTHashMap.h"
#include "../B/BSTSingleton.h"
#include "../N/NiSmartPointer.h"
#include "../N/NiObject.h"
#include "../N/NiCamera.h"

namespace ConsoleRE
{
	class BGSHeadPart;
	class BSFaceGenModel;
	class BSFaceGenNiNode;
	class TESNPC;

	struct BSFaceGenModelMap
	{
	public:
		class Entry : public NiRefObject
		{
		public:
			NiPointer<BSFaceGenModel> model;
			uint64_t				  time;
		};
		static_assert(sizeof(Entry) == 0x20);
	public:
		BSTHashMap<BSFixedString, NiPointer<Entry>> Unk00;
		BSReadWriteLock                             Unk20;
		bool                                        Unk30;
		bool										Unk31;
		bool										Unk32;
		bool										Unk33;
		bool										Unk34;
		bool										Unk35;
		bool										Unk36;
		bool										Unk37;
	};
	static_assert(sizeof(BSFaceGenModelMap) == 0x38, "");

	class BSFaceGenManager
	{
	public:
		BSFaceGenManager() = delete;
		~BSFaceGenManager() = delete;

		static BSFaceGenManager* GetSingleton()
		{
			Relocation<BSFaceGenManager**> Singleton("", 0x20C0090);
			return *Singleton;
		}

		void RegenerateHead(BSFaceGenNiNode* a_node, BGSHeadPart* a_headpart, TESNPC* a_npc)
		{
			using func_t = void(decltype(this), BSFaceGenNiNode*, BGSHeadPart*, TESNPC*);
			Relocation<func_t*> func("", 0x4754C0);
			return func(this, a_node, a_headpart, a_npc);
		}

		void ApplyMorph(BSFaceGenNiNode * a_faceGenNode, BGSHeadPart * a_headPart, BSFixedString& a_morphName, float a_relative)
		{
			using func_t = void(decltype(this), BSFaceGenNiNode*, BGSHeadPart*, BSFixedString&, float);
			Relocation<func_t*> func("", 0x474C20);
			return func(this, a_faceGenNode, a_headPart, a_morphName, a_relative);
		}
	public:
		uint32_t		  Unk00;
		bool			  Unk04;
		bool			  Unk05;
		bool			  Unk06;
		bool			  Unk07;
		NiCamera*		  Unk08;
		BSFaceGenModelMap Unk10;
		bool			  Unk48;
	};
	static_assert(offsetof(BSFaceGenManager, Unk48) == 0x48);
}