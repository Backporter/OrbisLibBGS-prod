#pragma once

#include "../N/NiPoint3.h"
#include "../R/ReferenceEffectController.h"

#include <stdint.h>

namespace ConsoleRE
{
	class ActiveEffect;

	class ActiveEffectReferenceEffectController : public ReferenceEffectController
	{
	public:
		~ActiveEffectReferenceEffectController() override;

		// override (ReferenceEffectController)
		void             Unk_02(void) override;
		void             Unk_03(void) override;
		void             Unk_04(void) override;
		void             SwitchAttachedRoot(uint64_t a_arg2, NiNode* a_attachRoot) override;
		const NiPoint3&  GetSourcePosition() override;
		bool             GetUseSourcePosition() override;
		bool             GetNoInitialFlare() override;
		bool             GetEffectPersists() override;
		bool             GetGoryVisuals() override;
		void             RemoveHitEffect(ReferenceEffect* a_refEffect) override;
		TESObjectREFR*   GetTargetReference() override;
		BGSArtObject*    GetHitEffectArt() override;
		TESEffectShader* GetHitEffectShader() override;
		bool             GetManagerHandlesSaveLoad() override;
		bool             EffectShouldFaceTarget() override;
		TESObjectREFR*   GetFacingTarget() override;
		void             SetWindPoint(const NiPoint3& a_point) override;
		const NiPoint3&  GetWindPoint() override;
		bool             GetAllowNo3D() override;
		void             SaveGame(BGSSaveGameBuffer* a_buf) override;
		void             LoadGame(BGSLoadGameBuffer* a_buf) override;
	public:
		ActiveEffect* effect;
		uint32_t	  target;
		NiPoint3	  windPoint;
	};
	static_assert(sizeof(ActiveEffectReferenceEffectController) == 0x20);
}