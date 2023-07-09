#include "../../../OrbisUtil/include//Relocation.h"

#include "../U/UIBlurManager.h"

namespace ConsoleRE
{
	UIBlurManager* UIBlurManager::GetSingleton()
	{
		Relocation<UIBlurManager**> Singleton("", 0x313D168);
		return *Singleton;
	}

	void UIBlurManager::IncrementBlurCount()
	{
		using func_t = decltype(&UIBlurManager::IncrementBlurCount);
		Relocation<func_t> func("", 0xA85B80);
		return func(this);
	}

	void UIBlurManager::DecrementBlurCount()
	{
		using func_t = decltype(&UIBlurManager::DecrementBlurCount);
		Relocation<func_t> func("", 0xA85BE0);
		return func(this);
	}
}