#pragma once

#include "../N/NiFrustum.h"
#include "../N/NiFrustumPlanes.h"

namespace ConsoleRE
{
	class BSDynamicTriShape;
	class BSFadeNode;
	class BSGeometry;
	class bhkAttachmentCollisionObject;
	class bhkBlendCollisionObject;
	class bhkLimitedHingeConstraint;
	class bhkNiCollisionObject;
	class bhkRigidBody;
	class BSLines;
	class BSMultiBoundNode;
	class BSSegmentedTriShape;
	class BSSubIndexTriShape;
	class BSTriShape;
	class NiAVObject;
	class NiCamera;
	class NiGeometry;
	class NiNode;
	class NiParticles;
	class NiSwitchNode;
	class NiRTTI;
	class NiTriBasedGeom;
	class NiTriShape;
	class NiTriStrips;
	class NiVisibleArray;

	class NiCullingProcess
	{
	public:
		// add
		virtual const NiRTTI*   			  GetRTTI() const;
		virtual NiNode*                       GetAsNiNode();
		virtual NiSwitchNode*                 GetAsNiSwitchNode();
		virtual BSFadeNode*                   GetAsBSFadeNode();
		virtual BSMultiBoundNode*             GetAsBSMultiBoundNode();
		virtual BSGeometry*                   GetAsBSGeometry();
		virtual NiTriStrips*                  GetAsNiTriStrips();
		virtual BSTriShape*                   GetAsBSTriShape();
		virtual BSSegmentedTriShape*          GetAsBSSegmentedTriShape();
		virtual BSSubIndexTriShape*           GetAsBSSubIndexTriShape();
		virtual BSDynamicTriShape*            GetAsBSDynamicTriShape();
		virtual NiGeometry*                   GetAsNiGeometry();
		virtual NiTriBasedGeom*               GetAsNiTriBasedGeom();
		virtual NiTriShape*                   GetAsNiTriShape();
		virtual NiParticles*                  GetAsNiParticles();
		virtual BSLines*                      GetAsBSLines();
		virtual bhkNiCollisionObject*         GetAsBhkNiCollisionObject();
		virtual bhkBlendCollisionObject*      GetAsBhkBlendCollisionObject();
		virtual bhkAttachmentCollisionObject* GetAsBhkAttachmentCollisionObject();
		virtual bhkRigidBody*                 GetAsBhkRigidBody();
		virtual bhkLimitedHingeConstraint*    GetAsBhkLimitedHingeConstraint();

		virtual ~NiCullingProcess();

		virtual void Process1(NiAVObject* a_object, uint32_t a_arg2);
		virtual void Process2(const NiCamera* a_camera, NiAVObject* a_scene, NiVisibleArray* a_visibleSet);
		virtual void AppendVirtual(BSGeometry& a_visible, uint32_t a_arg2);
	public:
		bool			useVirtualAppend; // const
		uint8_t			Unk009;
		uint8_t			Unk00A;
		uint8_t			Unk00B;
		uint32_t		Unk00C;
		NiVisibleArray*	visibleSet;
		NiCamera*		camera; // const
		NiFrustum       frustum;
		NiFrustumPlanes planes;
		NiFrustumPlanes customCullPlanes;
		bool            cameraRelatedUpdates;
		bool            updateAccumulateFlag;
		bool            ignorePreprocess;
		bool            doCustomCullPlanes;
		uint8_t			unk120;
		uint8_t			unk121;
		uint16_t		Unk122;
		uint32_t		Unk124;
	};
	static_assert(sizeof(NiCullingProcess) == 0x128);
}