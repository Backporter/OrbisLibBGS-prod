#pragma once

#include <stdint.h>

namespace ConsoleRE
{
	class BGSArtObject;
	class BGSLoadGameBuffer;
	class BGSSaveGameBuffer;
	class NiAVObject;
	class NiNode;
	class NiPoint3;
	class ReferenceEffect;
	class TESEffectShader;
	class TESObjectREFR;

	class ReferenceEffectController
	{
	public:
		virtual ~ReferenceEffectController();

		// add
		virtual void             Unk_02(void);
		virtual void             Unk_03(void);
		virtual void             Unk_04(void);
		virtual void             SwitchAttachedRoot(uint64_t a_arg2, NiNode* a_attachRoot);
		virtual const NiPoint3&  GetSourcePosition();
		virtual bool             GetUseSourcePosition();
		virtual bool             GetNoInitialFlare();
		virtual bool             GetEffectPersists();
		virtual bool             GetGoryVisuals();
		virtual void             RemoveHitEffect(ReferenceEffect* a_refEffect);
		virtual TESObjectREFR*   GetTargetReference() = 0;
		virtual BGSArtObject*    GetHitEffectArt() = 0;
		virtual TESEffectShader* GetHitEffectShader() = 0;
		virtual bool             GetManagerHandlesSaveLoad() = 0;
		virtual NiAVObject*      GetAttachRoot();
		virtual float            GetParticleAttachExtent();
		virtual bool             GetUseParticleAttachExtent();
		virtual bool             GetDoParticles();
		virtual bool             GetParticlesUseLocalSpace();
		virtual bool             GetUseRootWorldRotate();
		virtual bool             GetIsRootActor();
		virtual bool             GetClearWhenCellIsUnloaded();
		virtual bool             EffectShouldFaceTarget();
		virtual TESObjectREFR*   GetFacingTarget();
		virtual bool             GetShaderUseParentCell();
		virtual bool             EffectAttachesToCamera();
		virtual bool             EffectRotatesWithCamera();
		virtual bool             GetAllowTargetRoot();
		virtual bool             IsReadyForAttach();
		virtual void             SetWindPoint(const NiPoint3& a_point);
		virtual const NiPoint3&  GetWindPoint();
		virtual bool             GetAllowNo3D();
		virtual void             SaveGame(BGSSaveGameBuffer* a_buf);
		virtual void             LoadGame(BGSLoadGameBuffer* a_buf);
	};
	static_assert(sizeof(ReferenceEffectController) == 0x8);
}