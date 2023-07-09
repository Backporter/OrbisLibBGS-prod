#include "../ColorComponent/PapyrusExtColorComponent.h"

#include "../../../../../../source/B/BSFixedString.h"
#include "../../../../../../source/N/NativeFunction.h"
#include "../../../../../../source/C/Color.h"


namespace PapyrusExtColorComponent
{
	// I really hate doing this...
	using namespace ConsoleRE;

	uint32_t GetAlpha(StaticFunctionTag* base, uint32_t argb)
	{
		return ((argb >> 24) & 0xFF);
	}

	uint32_t GetRed(StaticFunctionTag* base, uint32_t argb)
	{
		return ((argb >> 16) & 0xFF);
	}

	uint32_t GetGreen(StaticFunctionTag* base, uint32_t argb)
	{
		return ((argb >> 8) & 0xFF);
	}

	uint32_t GetBlue(StaticFunctionTag* base, uint32_t argb)
	{
		return ((argb >> 0) & 0xFF);
	}

	float GetHue(StaticFunctionTag* base, uint32_t argb)
	{
		Color rgb(((argb >> 16) & 0xFF), ((argb >> 8) & 0xFF), ((argb >> 0) & 0xFF), ((argb >> 24) & 0xFF));
		return rgb.GetHue();
	}

	float GetSaturation(StaticFunctionTag* base, uint32_t argb)
	{
		Color color(((argb >> 16) & 0xFF), ((argb >> 8) & 0xFF), ((argb >> 0) & 0xFF), ((argb >> 24) & 0xFF));
		return color.GetSaturation();
	}

	float GetValue(StaticFunctionTag* base, uint32_t argb)
	{
		Color color(((argb >> 16) & 0xFF), ((argb >> 8) & 0xFF), ((argb >> 0) & 0xFF), ((argb >> 24) & 0xFF));
		return color.GetValue();
	}

	uint32_t SetColor(StaticFunctionTag* base, uint32_t red, uint32_t green, uint32_t blue, uint32_t alpha)
	{
		return (((alpha & 0xFF) << 24) | ((red & 0xFF) << 16) | ((green & 0xFF) << 8) | ((blue & 0xFF) << 0));
	}

	uint32_t SetAlpha(StaticFunctionTag* base, uint32_t argb, uint32_t alpha)
	{
		return (argb & ~0xFF000000) | (alpha << 24);
	}

	uint32_t SetRed(StaticFunctionTag* base, uint32_t argb, uint32_t red)
	{
		return (argb & ~0x00FF0000) | (red << 16);
	}

	uint32_t SetGreen(StaticFunctionTag* base, uint32_t argb, uint32_t green)
	{
		return (argb & ~0x0000FF00) | (green << 8);
	}

	uint32_t SetBlue(StaticFunctionTag* base, uint32_t argb, uint32_t blue)
	{
		return (argb & ~0x000000FF) | blue;
	}

	uint32_t SetHue(StaticFunctionTag* base, uint32_t argb, float hue)
	{
		Color color(((argb >> 16) & 0xFF), ((argb >> 8) & 0xFF), ((argb >> 0) & 0xFF), ((argb >> 24) & 0xFF));
		color.SetHue(hue);
		return color;
	}

	uint32_t SetSaturation(StaticFunctionTag* base, uint32_t argb, float sat)
	{
		Color color(((argb >> 16) & 0xFF), ((argb >> 8) & 0xFF), ((argb >> 0) & 0xFF), ((argb >> 24) & 0xFF));
		color.SetSaturation(sat);
		return color;
	}

	uint32_t SetValue(StaticFunctionTag* base, uint32_t argb, float val)
	{
		Color color(((argb >> 16) & 0xFF), ((argb >> 8) & 0xFF), ((argb >> 0) & 0xFF), ((argb >> 24) & 0xFF));
		color.SetValue(val);
		return color;
	}

	bool RegisterColorComponent(ConsoleRE::BSScript::Internal::VirtualMachine* VM)
	{
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(GetRed),			StaticFunctionTag, uint32_t, uint32_t>				("GetAlpha",	  "ColorComponent", GetRed));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(GetRed),			StaticFunctionTag, uint32_t, uint32_t>				("GetRed",		  "ColorComponent", GetRed));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(GetGreen),			StaticFunctionTag, uint32_t, uint32_t>				("GetGreen",	  "ColorComponent", GetGreen));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(GetBlue),			StaticFunctionTag, uint32_t, uint32_t>				("GetBlue",		  "ColorComponent", GetBlue));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(GetHue),			StaticFunctionTag, float, uint32_t>					("GetHue",		  "ColorComponent", GetHue));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(GetSaturation),	StaticFunctionTag, float, uint32_t>					("GetSaturation", "ColorComponent", GetSaturation));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(GetValue),			StaticFunctionTag, float, uint32_t>					("GetValue",	  "ColorComponent", GetValue));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(SetAlpha),			StaticFunctionTag, uint32_t, uint32_t, uint32_t>	("SetAlpha",	  "ColorComponent", SetAlpha));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(SetRed),			StaticFunctionTag, uint32_t, uint32_t, uint32_t>	("SetRed",		  "ColorComponent", SetRed));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(SetGreen),			StaticFunctionTag, uint32_t, uint32_t, uint32_t>	("SetGreen",	  "ColorComponent", SetGreen));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(SetBlue),			StaticFunctionTag, uint32_t, uint32_t, uint32_t>	("SetBlue",		  "ColorComponent", SetBlue));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(SetHue),			StaticFunctionTag, uint32_t, uint32_t, float>		("SetHue",		  "ColorComponent", SetHue));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(SetSaturation),	StaticFunctionTag, uint32_t, uint32_t, float>		("SetSaturation", "ColorComponent", SetSaturation));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(SetValue),			StaticFunctionTag, uint32_t, uint32_t, float>		("SetValue",	  "ColorComponent", SetValue));

		VM->SetCallableFromTasklets("ColorComponent", "GetAlpha", 1);
		VM->SetCallableFromTasklets("ColorComponent", "GetRed", 1);
		VM->SetCallableFromTasklets("ColorComponent", "GetGreen", 1);
		VM->SetCallableFromTasklets("ColorComponent", "GetBlue", 1);
		VM->SetCallableFromTasklets("ColorComponent", "GetHue", 1);
		VM->SetCallableFromTasklets("ColorComponent", "GetSaturation", 1);
		VM->SetCallableFromTasklets("ColorComponent", "GetValue", 1);
		VM->SetCallableFromTasklets("ColorComponent", "SetAlpha", 1);
		VM->SetCallableFromTasklets("ColorComponent", "SetRed", 1);
		VM->SetCallableFromTasklets("ColorComponent", "SetGreen", 1);
		VM->SetCallableFromTasklets("ColorComponent", "SetBlue", 1);
		VM->SetCallableFromTasklets("ColorComponent", "SetHue", 1);
		VM->SetCallableFromTasklets("ColorComponent", "SetSaturation", 1);
		VM->SetCallableFromTasklets("ColorComponent", "SetValue", 1);

		return true;
	}
}