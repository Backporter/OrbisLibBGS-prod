#pragma once

#include "../B/BSSoundHandle.h"
#include "../F/FormTypes.h"
#include "../N/NiSmartPointer.h"
#include "../T/TESObjectREFR.h"

namespace ConsoleRE
{
	class BGSHazard;
	class NiLight;

	class Hazard : public TESObjectREFR
	{
	public:
		static constexpr int TypeID = 70;
	public:	
		~Hazard() override;

		// override (TESObjectREFR)
		void SaveGame(BGSSaveFormBuffer* a_buf) override;
		void LoadGame(BGSLoadFormBuffer* a_buf) override;
		void FinishLoadGame(BGSLoadFormBuffer* a_buf) override;
		void Revert(BGSLoadFormBuffer* a_buf) override;
		void InitItemImpl() override;
		void SetActorCause(ActorCause* a_cause) override;
		void Release3DRelatedData() override;
		bool OnAddCellPerformQueueReference(TESObjectCELL& a_cell) const override;

		// add
		virtual void Unk_A2(void);
		virtual void Unk_A3(void);
		virtual bool IsNotGeneratedForm() const;
	public:
		void*                                  hazardDBHandle;
		uint32_t							   ownerActor;
		float                                  age;
		float                                  lifetime;
		float                                  targetTimer;
		float                                  radius;
		float                                  magnitude;
		BGSHazard*                             hazard;
		NiPointer<NiLight>                     light;
		BSSoundHandle                          sound;
		uint32_t							   flags;
	};
	static_assert(sizeof(Hazard) == 0xE8);
}