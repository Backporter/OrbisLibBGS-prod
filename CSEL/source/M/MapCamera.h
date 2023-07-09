#pragma once

#include "../T/TESCamera.h"
#include "../T/TESWorldSpace.h"
#include "../I/IMapCameraCallbacks.h"

namespace ConsoleRE
{
	namespace MapCameraStates
	{
		class World
		{
		public:
		};

		class Exit
		{
		public:
		};

		class Transition
		{
		public:
		};
	}

	class MapCamera : public TESCamera
	{
	public:
		~MapCamera();
	public:
		float                                        unk38;
		float                                        unk3C;
		float                                        unk40;
		float                                        unk44;
		float                                        unk48;
		uint32_t									 unk4C;
		TESWorldSpace*                               worldSpace;
		IMapCameraCallbacks*                         unk58;
		uint32_t									 unk60;
		uint32_t									 unk64;
		BSTSmartPointer<MapCameraStates::World>      unk68[2];
		BSTSmartPointer<MapCameraStates::Exit>       unk78;
		BSTSmartPointer<MapCameraStates::Transition> unk80;
		uint8_t										 unk88;
		uint8_t										 pad89;
		uint16_t									 pad8A;
		uint32_t									 pad8C;
	};
}