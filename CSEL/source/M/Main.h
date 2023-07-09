#pragma once

#include "../B/BSTEvent.h"
#include "../B/BSTMessageQueue.h"
#include "../S/ScrapHeap.h"

// _SKYRIM_VER is never defined.
namespace ConsoleRE
{
	class ScrapHeap;
	struct BSGamerProfileEvent;
	struct BSPackedTask;
	struct PositionPlayerEvent;

	class Main : public BSTEventSink<PositionPlayerEvent>
#if _SKYRIM_VER >= 110
	, public BSTEventSink<BSGamerProfileEvent>
#endif
	{
	public:
		~Main() override;
		
		// override (BSTEventSink<PositionPlayerEvent>)
		BSEventNotifyControl ProcessEvent(const PositionPlayerEvent*, BSTEventSource<PositionPlayerEvent>*); // { return BSEventNotifyControl::kContinue; }

#if _SKYRIM_VER >= 110
		// override (BSTEventSink<BSGamerProfileEvent>)
		BSEventNotifyControl ProcessEvent(const BSGamerProfileEvent*, BSTEventSource<BSGamerProfileEvent>*); // { ... }
#endif
		static Main* GetSingleton();
	public:
		bool                         quitGame;
		bool                         resetGame;
		bool                         fullReset;
		bool                         gameActive;
		bool                         onIdle;
		bool                         reloadContent;
		bool                         freezeTime;
		bool                         freezeNextFrame;
	};
}