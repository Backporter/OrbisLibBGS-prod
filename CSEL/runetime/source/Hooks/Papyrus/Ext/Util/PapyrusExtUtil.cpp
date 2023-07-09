#include "../INI/PapyrusExtINI.h"

#include "../../../../../../source/B/BSFixedString.h"
#include "../../../../../../source/N/NativeFunction.h"
#include "../../../../../../source/T/TESForm.h"
#include "../../../../../../source/B/BGSBaseAlias.h"
#include "../../../../../../source/P/PackUnpackImpl.h"

#include <utility>

#define max(a, b) (((a) > (b)) ? (a) : (b))
#define min(a, b) (((a) < (b)) ? (a) : (b))

namespace PapyrusExtUtil
{
	using namespace ConsoleRE;

#pragma region
	template<typename T>
	std::vector<T> CreateArray(StaticFunctionTag* base, uint32_t size, T fillValue)
	{
		std::vector<T> data;
		data.resize(size, fillValue);
		return data;
	}

	template<typename T>
	std::vector<T> ResizeArray(StaticFunctionTag* base, std::vector<T> inArray, uint32_t size, T fillValue)
	{
		std::vector<T> data;
		data.resize(size, fillValue);
		
		uint32_t arrayLength = min(inArray.size(), size);
		for (uint32_t i = 0; i < arrayLength; i++)
		{
			data[i] = inArray[i];
		}

		return data;
	}
#pragma endregion

	bool RegisterUtil(ConsoleRE::BSScript::Internal::VirtualMachine* VM)
	{
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(CreateArray<float>),			StaticFunctionTag, std::vector<float>, uint32_t, float>                                             ("CreateFloatArray",  "Utility", CreateArray<float>));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(CreateArray<int32_t>),			StaticFunctionTag, std::vector<int32_t>, uint32_t, int32_t>                                         ("CreateIntArray",    "Utility", CreateArray<int32_t>));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(CreateArray<BSFixedString>),	StaticFunctionTag, std::vector<BSFixedString>, uint32_t, BSFixedString>                             ("CreateStringArray", "Utility", CreateArray<BSFixedString>));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(ResizeArray<float>),			StaticFunctionTag, std::vector<float>, std::vector<float>, uint32_t, float>                         ("ResizeFloatArray",  "Utility", ResizeArray<float>));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(ResizeArray<int32_t>),			StaticFunctionTag, std::vector<int32_t>, std::vector<int32_t>, uint32_t, int32_t>                   ("ResizeIntArray",    "Utility", ResizeArray<int32_t>));
	    VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(ResizeArray<BSFixedString>),	StaticFunctionTag, std::vector<BSFixedString>, std::vector<BSFixedString>, uint32_t, BSFixedString> ("ResizeStringArray", "Utility", ResizeArray<BSFixedString>));
	    VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(ResizeArray<BGSBaseAlias*>),	StaticFunctionTag, std::vector<BGSBaseAlias*>, std::vector<BGSBaseAlias*>, uint32_t, BGSBaseAlias*> ("ResizeAliasArray",  "Utility", ResizeArray<BGSBaseAlias*>));
	    VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(CreateArray<BGSBaseAlias*>),	StaticFunctionTag, std::vector<BGSBaseAlias*>, uint32_t, BGSBaseAlias*>                             ("CreateAliasArray",  "Utility", CreateArray<BGSBaseAlias*>));
	    VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(ResizeArray<TESForm*>),		StaticFunctionTag, std::vector<TESForm*>, std::vector<TESForm*>, uint32_t, TESForm*>                ("ResizeFormArray",   "Utility", ResizeArray<TESForm*>));
	    VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(CreateArray<TESForm*>),		StaticFunctionTag, std::vector<TESForm*>, uint32_t, TESForm*>                                       ("CreateFormArray",   "Utility", CreateArray<TESForm*>)); 
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(ResizeArray<bool>),			StaticFunctionTag, std::vector<bool>, std::vector<bool>, uint32_t, bool>                            ("ResizeBoolArray",   "Utility", ResizeArray<bool>));
	    VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(CreateArray<bool>),			StaticFunctionTag, std::vector<bool>, uint32_t, bool>                                               ("CreateBoolArray",   "Utility", CreateArray<bool>));
	
		VM->SetCallableFromTasklets("Utility", "ResizeBoolArray",   true);
		VM->SetCallableFromTasklets("Utility", "CreateBoolArray",   true);
		VM->SetCallableFromTasklets("Utility", "CreateFloatArray",  true);
		VM->SetCallableFromTasklets("Utility", "CreateIntArray",    true);
		VM->SetCallableFromTasklets("Utility", "CreateStringArray", true);
		VM->SetCallableFromTasklets("Utility", "CreateFormArray",   true);
		VM->SetCallableFromTasklets("Utility", "CreateAliasArray",  true);
		VM->SetCallableFromTasklets("Utility", "ResizeFloatArray",  true);
		VM->SetCallableFromTasklets("Utility", "ResizeIntArray",    true);
		VM->SetCallableFromTasklets("Utility", "ResizeStringArray", true);
		VM->SetCallableFromTasklets("Utility", "ResizeFormArray",   true);
		VM->SetCallableFromTasklets("Utility", "ResizeAliasArray",  true);

		return true;
	}
}