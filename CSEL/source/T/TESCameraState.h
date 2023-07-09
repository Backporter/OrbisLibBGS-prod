#pragma once

#include "../B/BSIntrusiveRefCounted.h"
#include "../B/BSTSmartPointer.h"

namespace ConsoleRE
{
	class TESCamera;
	class NiQuaternion;
	class NiPoint3;

	class TESCameraState : public BSIntrusiveRefCounted
	{
	public:
		virtual ~TESCameraState();

		// add
		virtual void Begin();
		virtual void End();
		virtual void Update(BSTSmartPointer<TESCameraState>& a_nextState);
		virtual void GetRotation(NiQuaternion& a_rotation);
		virtual void GetTranslation(NiPoint3& a_translation);
		virtual void SaveGame(void* a_buf);
		virtual void LoadGame(void* a_buf);
		virtual void Revert(void* a_buf);
	public:
		uint32_t	  pad0C;
		TESCamera*    camera;
		uint32_t	  id;
	};
	static_assert(sizeof(TESCameraState) == 0x20);
}