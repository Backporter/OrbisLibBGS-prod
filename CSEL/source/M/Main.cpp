#include "../../../OrbisUtil/include/Relocation.h"

#include "../M/Main.h"

namespace ConsoleRE
{
	Main* Main::GetSingleton()
	{
		Relocation<Main**> Singleton("", 0x313D840);
		return *Singleton;
	}
}