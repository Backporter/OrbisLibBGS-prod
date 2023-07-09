#pragma once

#include "../A/ActorCause.h"
#include "../B/BSAtomic.h"
#include "../B/BSTList.h"
#include "../B/BSSoundHandle.h"
#include "../T/TESObjectREFR.h"
#include "../I/InventoryEntryData.h"
#include "../T/TESAmmo.h"
#include "../T/TESObjectWEAP.h"
#include "../M/MagicSystem.h"

namespace ConsoleRE
{
	class bhkCollisionObject;
	class bhkSimpleShapePhantom;
	class QueuedFile;

	class Projectile : public TESObjectREFR
	{
	public:
		struct ImpactData
		{
		public:
			uint64_t						unk00;
			uint64_t						unk08;
			uint64_t						unk10;
			uint32_t						collidee;
			NiPointer<bhkCollisionObject>	colObj;
			uint64_t						unk28;
			uint64_t						unk30;
			uint64_t						unk38;
			uint64_t						unk40;
			uint64_t						unk48;
		};
		static_assert(sizeof(ImpactData) == 0x50);
	public:
		~Projectile() override;

		// override (TESObjectREFR)
		bool         Load(TESFile* a_mod) override;
		void         SaveGame(BGSSaveFormBuffer* a_buf) override;
		void         LoadGame(BGSLoadFormBuffer* a_buf) override;
		void         InitLoadGame(BGSLoadFormBuffer* a_buf) override;
		void         FinishLoadGame(BGSLoadFormBuffer* a_buf) override;
		void         Revert(BGSLoadFormBuffer* a_buf) override;
		bool         GetAllowPromoteToPersistent() const override;
		bool         HasKeywordHelper(const BGSKeyword* a_keyword) const override;
		void         SetActorCause(ActorCause* a_cause) override;
		ActorCause*  GetActorCause() const override;
		MagicCaster* GetMagicCaster(MagicSystem::CastingSource a_source) override;
		bool         DetachHavok(NiAVObject* a_obj3D) override;
		void         InitHavok() override;
		NiAVObject*  Load3D(bool a_backgroundLoading) override;
		void         Set3D(NiAVObject* a_object, bool a_queue3DTasks = true) override;
		void         MoveHavok(bool a_forceRec) override;
		void         GetLinearVelocity(NiPoint3& a_velocity) const override;
		Projectile*  AsProjectile() override;
		bool         OnAddCellPerformQueueReference(TESObjectCELL& a_cell) const override;
	public:
		BSSimpleList<void*>			impacts;
	};
}