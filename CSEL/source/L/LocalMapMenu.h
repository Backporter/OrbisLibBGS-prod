#pragma once

#include "../B/BSTArray.h"
#include "../B/BSShaderAccumulator.h"
#include "../B/BSCullingProcess.h"
#include "../M/MenuEventHandler.h"
#include "../N/NiSmartPointer.h"
#include "../L/LocalMapCamera.h"
#include "../I/ImageSpaceShaderParam.h"
#include "../I/ImageData.h"
#include "../T/TESFullName.h"
#include "../G/GFxValue.h"

namespace ConsoleRE
{
	class TESFullName;

	struct LocalMapMenu
	{
		class LocalMapCullingProcess
		{
		public:
			struct Data
			{
				NiPointer<BSShaderAccumulator> shaderAccumulator;
				void*                          unk08;
				NiPointer<NiCamera>            camera;
				uint64_t					   unk18;
				uint64_t					   unk20;
				uint64_t					   unk28;
				uint64_t					   unk30;
				uint64_t					   unk38;
				uint64_t                       unk40;
			};
			static_assert(sizeof(Data) == 0x48);
		public:
			BSCullingProcess			   cullingProcess;
			Data						   Unk30600;
			uint64_t					   Unk30648;
			uint64_t					   Unk30650;
			uint64_t					   Unk30658;
			uint64_t					   Unk30660;
			LocalMapCamera				   camera;
			NiPointer<BSShaderAccumulator> Unk306D0;
			ImageSpaceShaderParam          Unk306D8;
			uint64_t					   Unk30758;
			NiPointer<NiNode>              Unk30760;
			uint64_t					   Unk30768;
			uint64_t					   Unk30770;
			uint64_t					   Unk30778;
		};
		static_assert(sizeof(LocalMapCullingProcess) == 0x30780);

		class InputHandler : public MenuEventHandler
		{
		public:
			~InputHandler() override;

			// override (MenuEventHandler)
			bool CanProcess(InputEvent* a_event) override;
			bool ProcessButton(ButtonEvent* a_event) override;
			bool ProcessMouseMove(MouseMoveEvent* a_event) override;
			bool ProcessThumbstick(ThumbstickEvent* a_event) override;
		public:
			LocalMapMenu* localmapmenu;
		};
		static_assert(sizeof(InputHandler) == 0x18);
	public:
		BSTArray<void*>					Unk00000;
		GFxValue						Unk00010;
		float							unk00028;
		float							unk0002C;
		float							unk00030;
		float							unk00034;
		uint8_t							unk00038[0x48];
		LocalMapCullingProcess			localCullingProcess;
		ImageData						Unk30800;
		GFxValue						Unk30818;
		GFxValue						Unk30830;
		void*							Unk30848;
		BSTSmartPointer<InputHandler>	Unk30850;
		uint64_t						Unk30858;
	};
}