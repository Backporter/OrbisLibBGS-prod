#include "../Math/PapyrusExtMath.h"

#include "../../../../../../source/B/BSFixedString.h"
#include "../../../../../../source/N/NativeFunction.h"

#include <math.h>
#include <cmath>

namespace PapyrusExtMath
{
	// I really hate doing this...
	using namespace ConsoleRE;

	uint32_t Lsh(StaticFunctionTag* tag, uint32_t val, uint32_t lshcount)
	{
		return (val << lshcount);
	}

	uint32_t Rsh(StaticFunctionTag* tag, uint32_t val, uint32_t rshcount)
	{
		return (val >> rshcount);
	}

	uint32_t And(StaticFunctionTag* tag, uint32_t val, uint32_t count)
	{
		return (val & count);
	}

	uint32_t Or(StaticFunctionTag* tag, uint32_t val, uint32_t count)
	{
		return (val | count);
	}

	uint32_t Xor(StaticFunctionTag* tag, uint32_t val, uint32_t count)
	{
		return (val ^ count);
	}

	uint32_t Not(StaticFunctionTag* tag, uint32_t val)
	{
		return (~val);
	}

	float	 log(StaticFunctionTag* tag, float val)
	{
		return std::log(val);
	}

	bool RegisterMath(ConsoleRE::BSScript::Internal::VirtualMachine* VM)
	{
		VM->RegisterFunction(new BSScript::NativeFunction<false, NFDLSE(Lsh),  StaticFunctionTag, uint32_t, uint32_t, uint32_t>("LeftShift",   "Math", Lsh));
		VM->RegisterFunction(new BSScript::NativeFunction<false, NFDLSE(Rsh),  StaticFunctionTag, uint32_t, uint32_t, uint32_t>("RightShift",  "Math", Rsh));
		VM->RegisterFunction(new BSScript::NativeFunction<false, NFDLSE(And),  StaticFunctionTag, uint32_t, uint32_t, uint32_t>("LogicalAnd",  "Math", And));
		VM->RegisterFunction(new BSScript::NativeFunction<false, NFDLSE(Or),   StaticFunctionTag, uint32_t, uint32_t, uint32_t>("LogicalOr",   "Math", Or));
		VM->RegisterFunction(new BSScript::NativeFunction<false, NFDLSE(Xor),  StaticFunctionTag, uint32_t, uint32_t, uint32_t>("LogicalXor",  "Math", Xor));
		VM->RegisterFunction(new BSScript::NativeFunction<false, NFDLSE(Not),  StaticFunctionTag, uint32_t, uint32_t>          ("LogicalNot",  "Math", Not));
		VM->RegisterFunction(new BSScript::NativeFunction<false, NFDLSE(log),  StaticFunctionTag, float, float>                ("Log",		   "Math", log));

		VM->SetCallableFromTasklets("Math", "LeftShift",   true);
		VM->SetCallableFromTasklets("Math", "RightShift",  true);
		VM->SetCallableFromTasklets("Math", "LogicalAnd",  true);
		VM->SetCallableFromTasklets("Math", "LogicalOr",   true);
		VM->SetCallableFromTasklets("Math", "LogicalXor",  true);
		VM->SetCallableFromTasklets("Math", "LogicalNot",  true);
		VM->SetCallableFromTasklets("Math", "Log",		   true);

		return true;
	}
}