#include "../ColorForm/PapyrusExtColorForm.h"

#include "../../../../../../source/B/BSFixedString.h"
#include "../../../../../../source/N/NativeFunction.h"
#include "../../../../../../source/B/BGSColorForm.h"

namespace PapyrusExtColorForm
{
	// I really hate doing this...
	using namespace ConsoleRE;

	uint32_t GetColor(BGSColorForm* colorForm)
	{
		return (colorForm) ? (__bswap32(colorForm->color) >> 8) | (colorForm->color.a << 24) : 0;
	}

	void SetColor(BGSColorForm* colorForm, uint32_t color)
	{
		if (colorForm) 
		{
			colorForm->color.r = ((color >> 16) & 0xFF);
			colorForm->color.g = ((color >> 8) & 0xFF);
			colorForm->color.b = ((color >> 0) & 0xFF);
		}
	}

	bool RegisterColorForm(ConsoleRE::BSScript::Internal::VirtualMachine* VM)
	{
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(GetColor), BGSColorForm, uint32_t>		  ("GetColor", "ColorForm", GetColor));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(SetColor), BGSColorForm, void, uint32_t> ("SetColor", "ColorForm", SetColor));

		VM->SetCallableFromTasklets("ColorForm", "GetColor", true);
		VM->SetCallableFromTasklets("ColorForm", "SetColor", true);

		return true;
	}
}