#pragma once

#include "../N/NiRefObject.h"
#include "../N/NiSmartPointer.h"

#include <stdint.h>

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
	class NiCloningProcess;
	class NiControllerManager;
	class NiGeometry;
	class NiNode;
	class NiObjectGroup;
	class NiParticles;
	class NiRTTI;
	class NiStream;
	class NiSwitchNode;
	class NiTriBasedGeom;
	class NiTriShape;
	class NiTriStrips;

	class NiObject : public NiRefObject
	{
	public:
		~NiObject() override = default;
		
		// add (NiObject)
		virtual const NiRTTI*					GetRTTI() const;
		virtual NiNode*							AsNode()									{ return nullptr; }
		virtual NiSwitchNode*					AsSwitchNode()								{ return nullptr; }
		virtual BSFadeNode*						AsFadeNode()								{ return nullptr; }
		virtual BSMultiBoundNode*				AsMultiBoundNode()							{ return nullptr; }
		virtual BSGeometry*						AsGeometry()								{ return nullptr; }
		virtual NiTriStrips*					AsTriStrips()								{ return nullptr; }
		virtual BSTriShape*						AsTriShape()								{ return nullptr; }
		virtual BSSegmentedTriShape*			AsSegmentedTriShape()						{ return nullptr; }
		virtual BSSubIndexTriShape*				AsSubIndexTriShape()						{ return nullptr; }
		virtual BSDynamicTriShape*				AsDynamicTriShape()							{ return nullptr; }
		virtual NiGeometry*						AsNiGeometry()								{ return nullptr; }
		virtual NiTriBasedGeom*					AsNiTriBasedGeom()							{ return nullptr; }
		virtual NiTriShape*						AsNiTriShape()								{ return nullptr; }
		virtual NiParticles*					AsParticlesGeom()							{ return nullptr; }
		virtual BSLines*						AsLinesGeom()								{ return nullptr; }
		virtual bhkNiCollisionObject*			AsBhkNiCollisionObject()					{ return nullptr; }
		virtual bhkBlendCollisionObject*		AsBhkBlendCollisionObject()					{ return nullptr; }
		virtual bhkAttachmentCollisionObject*	AsBhkAttachmentCollisionObject()			{ return nullptr; }
		virtual bhkRigidBody*					AsBhkRigidBody()							{ return nullptr; }
		virtual bhkLimitedHingeConstraint*		AsBhkLimitedHingeConstraint()				{ return nullptr; }
		virtual NiObject*						CreateClone(NiCloningProcess&a_cloning)		{ return this; }
		virtual void							LoadBinary(NiStream& a_stream)				{ return; }
		virtual void							LinkObject(NiStream& a_stream)				{ return; }
		virtual bool							RegisterStreamables(NiStream& a_stream);
		virtual void							SaveBinary(NiStream& a_stream)				{ return; }
		virtual bool							IsEqual(NiObject*a_object);
		virtual void							ProcessClone(NiCloningProcess&a_cloning);
		virtual void							PostLinkObject(NiStream& a_stream)			{ return; }
		virtual bool							StreamCanSkip()								{ return false; }
		virtual const NiRTTI*					GetStreamableRTTI() const					{ return GetRTTI(); }
		virtual uint32_t						GetBlockAllocationSize() const				{ return 0; }
		virtual NiObjectGroup*					GetGroup() const							{ return nullptr; }
		virtual void							SetGroup(NiObjectGroup*a_group)				{ return; }
		virtual NiControllerManager*			AsNiControllerManager()						{ return nullptr; }

		void CreateDeepCopy(NiPointer<NiObject>& a_object);
	public:
	};
	static_assert(sizeof(NiObject) == 0x10);
}