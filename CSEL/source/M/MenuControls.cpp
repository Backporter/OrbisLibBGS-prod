#include "../M/MenuControls.h"

#include "../M/MenuEventHandler.h"

namespace ConsoleRE
{
	MenuControls::QueuedReg::QueuedReg(MenuEventHandler* a_handler, bool a_add) :
		handler(a_handler),
		add(a_add),
		pad08(0),
		pad09(0),
		pad0A(0)
	{}

	MenuControls* MenuControls::GetSingleton()
	{
		Relocation<MenuControls**> Singleton("", 0x30FDA40);
		return *Singleton;
	}
}