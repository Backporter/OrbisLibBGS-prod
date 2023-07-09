#pragma once

#include "../B/BSTEvent.h"
#include "../D/DefaultObjectsReadyEvent.h"

namespace ConsoleRE
{
	class TESImageSpaceModifier;

	class UIBlurManager : public BSTEventSink<DefaultObjectsReadyEvent::Event> 
	{
	public:
		~UIBlurManager() override;

		static UIBlurManager* GetSingleton();

		void IncrementBlurCount();
		void DecrementBlurCount();
	public:
		TESImageSpaceModifier* blurEffect;
		uint32_t			   blurCount;
	};
	static_assert(sizeof(UIBlurManager) == 0x18);
}