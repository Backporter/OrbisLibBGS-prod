#pragma once
#include "../M/MenuEventHandler.h"

namespace ConsoleRE
{
	class FavoritesHandler : public MenuEventHandler
	{
	public:
		virtual ~FavoritesHandler();

		bool CanProcess(InputEvent* a_event) override;      // 01
		bool ProcessKinect(KinectEvent* a_event) override;  // 02
		bool ProcessButton(ButtonEvent* a_event) override;  // 05
	public:
	};
	static_assert(sizeof(FavoritesHandler) == 0x10);
}