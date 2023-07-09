#pragma once

#include "../R/ReferenceEffectController.h"

namespace ConsoleRE
{
	class SkyEffectController : public ReferenceEffectController
	{
	public:
		~SkyEffectController() override;

		// override (ReferenceEffectController)
		void             RemoveHitEffect(ReferenceEffect* a_refEffect) override;
		TESObjectREFR*   GetTargetReference() override;
		BGSArtObject*    GetHitEffectArt() override;
		TESEffectShader* GetHitEffectShader() override;
		bool             GetManagerHandlesSaveLoad() override;
		NiAVObject*      GetAttachRoot() override;
		bool             EffectAttachesToCamera() override;
		bool             EffectRotatesWithCamera() override;
	};
	static_assert(sizeof(SkyEffectController) == 0x8);
}