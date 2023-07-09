#pragma once

#include "../B/BSTSmartPointer.h"
#include "../N/NiPoint3.h"
#include "../N/NiSmartPointer.h"
#include "../T/TESCamera.h"
#include "../T/TESCameraState.h"

namespace ConsoleRE
{
	class NiCamera;

	class LocalMapCamera : public TESCamera
	{	
	public:
		class DefaultState : public TESCameraState
		{
		public:
			~DefaultState() override;
			
			// override (TESCameraState)
			void Begin() override;
			void Update(BSTSmartPointer<TESCameraState>& a_nextState) override;
		public:
			NiPoint3      initialPosition;
			NiPoint3      translation;
			float         zoom;
			float         minFrustumHalfWidth;
			float         minFrustumHalfHeight;
		};
		static_assert(sizeof(DefaultState) == 0x40);
	public:
		~LocalMapCamera() override;

		void SetAreaBounds(NiPoint3& a_maxExtent, NiPoint3& a_minExtent);
		void SetDefaultStateInitialPosition(NiPoint3& a_position);
		void SetDefaultStateMinFrustumDimensions(float a_width, float a_height);
		void SetDefaultStateTranslation(float a_x, float a_y, float a_z);
		void SetNorthRotation(float a_northRotation);
	public:
		NiPoint3                      maxExtent;
		NiPoint3                      minExtent;
		BSTSmartPointer<DefaultState> defaultState;
		NiPointer<NiCamera>           camera;
		float                         zRotation;
		uint32_t					  pad64;
	protected:
		void Ctor(float a_zRotation);
	};
	static_assert(sizeof(LocalMapCamera) == 0x68);
}