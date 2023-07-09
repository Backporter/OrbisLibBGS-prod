#include "../I/IAnimationGraphManagerHolder.h"

namespace ConsoleRE
{
	bool IAnimationGraphManagerHolder::GetAnimationGraphManager(BSTSmartPointer<BSAnimationGraphManager>& a_out)
	{
		return GetAnimationGraphManagerImpl(a_out);
	}

	bool IAnimationGraphManagerHolder::GetGraphVariableFloat(const BSFixedString& a_variableName, float& a_out)
	{
		return GetGraphVariableImpl1(a_variableName, a_out);
	}

	bool IAnimationGraphManagerHolder::GetGraphVariableInt(const BSFixedString& a_variableName, int32_t& a_out)
	{
		return GetGraphVariableImpl2(a_variableName, a_out);
	}

	bool IAnimationGraphManagerHolder::GetGraphVariableBool(const BSFixedString& a_variableName, bool& a_out)
	{
		return GetGraphVariableImpl3(a_variableName, a_out);
	}

	bool IAnimationGraphManagerHolder::GetGraphVariableNiPoint3(const BSFixedString& a_variableName, NiPoint3& a_out)
	{
		using func_t = decltype(&IAnimationGraphManagerHolder::GetGraphVariableNiPoint3);
		Relocation<func_t> func("", 0x5C8A70);
		return func(this, a_variableName, a_out);
	}

	bool IAnimationGraphManagerHolder::SetAnimationGraphManager(BSTSmartPointer<BSAnimationGraphManager>& a_in)
	{
		return SetAnimationGraphManagerImpl(a_in);
	}

	bool IAnimationGraphManagerHolder::SetGraphVariableBool(const BSFixedString& a_variableName, bool a_in)
	{
		using func_t = decltype(&IAnimationGraphManagerHolder::SetGraphVariableBool);
		Relocation<func_t> func("", 0x5C6A80);
		return func(this, a_variableName, a_in);
	}

	bool IAnimationGraphManagerHolder::SetGraphVariableInt(const BSFixedString& a_variableName, int32_t a_in)
	{
		using func_t = decltype(&IAnimationGraphManagerHolder::SetGraphVariableInt);
		Relocation<func_t> func("", 0x5C6B30);
		return func(this, a_variableName, a_in);
	}

	bool IAnimationGraphManagerHolder::SetGraphVariableFloat(const BSFixedString& a_variableName, float a_in)
	{
		using func_t = decltype(&IAnimationGraphManagerHolder::SetGraphVariableFloat);
		Relocation<func_t> func("", 0x5C6BE0);
		return func(this, a_variableName, a_in);
	}

	bool IAnimationGraphManagerHolder::SetGraphVariableNiPoint3(const BSFixedString& a_variableName, NiPoint3& a_in)
	{
		using func_t = decltype(&IAnimationGraphManagerHolder::SetGraphVariableNiPoint3);
		Relocation<func_t> func("", 0x5C6C90);
		return func(this, a_variableName, a_in);
	}
}