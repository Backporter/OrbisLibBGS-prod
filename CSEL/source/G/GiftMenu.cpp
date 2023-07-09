#include "../../../OrbisUtil/include/Relocation.h"

#include "../G/GiftMenu.h"

namespace ConsoleRE
{
	uint32_t GiftMenu::GetTargetRefHandle()
	{
		Relocation<uint32_t*> ref("", 0x319988C);
		return *ref;
	}
}