#pragma once

#include "../N/NiAVObject.h"
#include "../N/NiSmartPointer.h"

namespace ConsoleRE
{
	class BSMultiIndexTriShape;
	class BSSkinnedDecalTriShape;
	class NiProperty;
	class NiSkinInstance;

	class BSGeometry : public NiAVObject
	{
	public:
		enum class Type
		{
			kGeometry = 0,
			kParticles = 1,
			kStripParticles = 2,
			kTriShape = 3,
			kDynamicTriShape = 4,
			kMeshLODTriShape = 5,
			kLODMultiIndexTriShape = 6,
			kMultiIndexTriShape = 7,
			kSubIndexTriShape = 8,
			kSubIndexLandTriShape = 9,
			kMultiStreamInstanceTriShape = 10,
			kParticleShaderDynamicTriShape = 11,
			kLines = 12,
			kDynamicLines = 13,
			kInstanceGroup = 14
		};

		struct States
		{
			enum State
			{
				kProperty,
				kEffect,
				kTotal
			};
		};
	public:
		~BSGeometry() override;

		// override (NiAVObject)
		const NiRTTI* GetRTTI() const override;                                                                                    
		BSGeometry*   AsGeometry() override;                                                                                       
		void          LoadBinary(NiStream& a_stream) override;                                                                     
		void          LinkObject(NiStream& a_stream) override;                                                                     
		bool          RegisterStreamables(NiStream& a_stream) override;                                                            
		void          SaveBinary(NiStream& a_stream) override;                                                                     
		bool          IsEqual(NiObject* a_object) override;                                                                        
		void          ProcessClone(NiCloningProcess& a_cloning) override;                                                          
		void          PostLinkObject(NiStream& a_stream) override;                                                                 
		void          AttachProperty(NiAlphaProperty* a_property) override;                                                        
		void          SetSelectiveUpdateFlags(bool& a_selectiveUpdate, bool a_selectiveUpdateTransforms, bool& a_rigid) override;  
		void          UpdateDownwardPass(NiUpdateData& a_data, uint32_t a_arg2) override;                                     
		void          UpdateSelectedDownwardPass(NiUpdateData& a_data, uint32_t a_arg2) override;                             
		void          UpdateRigidDownwardPass(NiUpdateData& a_data, uint32_t a_arg2) override;                                
		void          UpdateWorldBound() override;                                                                                 
		void          OnVisible(NiCullingProcess& a_process) override;                                                             

		// add
		virtual BSMultiIndexTriShape*   AsMultiIndexTriShape(); 
		virtual BSSkinnedDecalTriShape* AsSkinnedDecalTriShape(); 
		virtual void                    Unk_37(void); 
	public:
		NiBound									modelBound;
		NiPointer<NiProperty>					properties[States::kTotal];
		NiPointer<NiSkinInstance>				skinInstance;
		void*									rendererData;
		void*									unk140;
		uint64_t								vertexDesc;
		uint8_t									type;
		uint8_t									pad151;
		uint16_t								pad152;
	};
	static_assert(sizeof(BSGeometry) == 0x158);
}