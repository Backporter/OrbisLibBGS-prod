#pragma once

#include "../N/NiObject.h"

namespace ConsoleRE
{
	class BGSLoadGameBuffer;
	class BGSSaveGameBuffer;
	class NiAVObject;
	class TESObjectCELL;

	class BSTempEffect : public NiObject
	{
	public:
		~BSTempEffect() override;

		// override (NiObject)
		const NiRTTI*                 GetRTTI() const override;
		NiNode*                       AsNode() override;
		NiSwitchNode*                 AsSwitchNode() override;
		BSFadeNode*                   AsFadeNode() override;
		BSMultiBoundNode*             AsMultiBoundNode() override;
		BSGeometry*                   AsGeometry() override;
		NiTriStrips*                  AsTriStrips() override;
		BSTriShape*                   AsTriShape() override;
		BSSegmentedTriShape*          AsSegmentedTriShape() override;
		BSSubIndexTriShape*           AsSubIndexTriShape() override;
		BSDynamicTriShape*            AsDynamicTriShape() override;
		NiGeometry*                   AsNiGeometry() override;
		NiTriBasedGeom*               AsNiTriBasedGeom() override;
		NiTriShape*                   AsNiTriShape() override;
		NiParticles*                  AsParticlesGeom() override;
		BSLines*                      AsLinesGeom() override;
		bhkNiCollisionObject*         AsBhkNiCollisionObject() override;
		bhkBlendCollisionObject*      AsBhkBlendCollisionObject() override;
		bhkAttachmentCollisionObject* AsBhkAttachmentCollisionObject() override;
		bhkRigidBody*                 AsBhkRigidBody() override;
		bhkLimitedHingeConstraint*    AsBhkLimitedHingeConstraint() override;
		
		// add
		virtual void                           Initialize();
		virtual void                           Attach();
		virtual void                           Detach();
		virtual bool                           Update(float a_arg1);
		virtual NiAVObject*					   Get3D() const;
		virtual bool						   GetManagerHandlesSaveLoad() const;
		virtual bool						   GetClearWhenCellIsUnloaded() const;
		virtual uint32_t					   GetType() const;
		virtual void                           SaveGame(BGSSaveGameBuffer* a_buf);
		virtual void                           LoadGame(BGSLoadGameBuffer* a_buf);
		virtual void                           FinishLoadGame(BGSLoadGameBuffer* a_buf);
		virtual bool						   IsInterfaceEffect() const;
		virtual void                           SetInterfaceEffect(bool a_set);
		virtual bool						   GetStackable() const;
		virtual bool                           GetStackableMatch(BSTempEffect* a_effect) const;
		virtual void                           Push();
		virtual void                           Pop();
	public:
		TESObjectCELL*	cell;
		float			lifetime;
		float			age;
		bool			initialized;
		uint8_t			pad25;
		uint16_t		pad26;
		uint32_t		effectID;
	};
	static_assert(sizeof(BSTempEffect) == 0x28);
}