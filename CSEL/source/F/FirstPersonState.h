#pragma once
#include "../T/TESCameraState.h"
#include "../P/PlayerInputHandler.h"

#include "../N/NiPoint3.h"
#include "../N/NiQuaternion.h"

namespace ConsoleRE
{
	class FirstPersonState : public TESCameraState, public PlayerInputHandler
	{
	public:
		virtual ~FirstPersonState();

		bool CanProcess(InputEvent* a_event) override;

		virtual void Unk_02(void);
		virtual void Unk_03(void);
		virtual void Unk_04(void);
		virtual void GetRotation(NiQuaternion& a_rotation);
		virtual void GetTranslation(NiPoint3& a_translation);
	public:
		uint32_t	  pad0C; 
		void*		  camera;
		uint32_t      id;    
		uint32_t	  pad1C; 
	};
}