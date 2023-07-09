#pragma once
#include "../G/GNewOverrideBase.h"

namespace ConsoleRE
{
	class GFxEvent : GNewOverrideBase<2>
	{
	public:
		enum EventType
		{
			kNone,
			kMouseMove,
			kMouseDown,
			kMouseUp,
			kMouseWheel,
			kKeyDown,
			kKeyUp,
			kSceneResize,
			kSetFocus,
			kKillFocus,
			kDoShowMouse,
			kDoHideMouse,
			kDoSetMouseCursor,
			kCharEvent,
			kIMEEvent
		};
	public:
		GFxEvent(uint32_t a_eventType) : GNewOverrideBase<2>(), m_type(a_eventType)
		{
		}
	public:
		uint32_t m_eventType;
	};
}