#include "../../../OrbisUtil/include/Relocation.h"

#include "../M/MagicTarget.h"

namespace ConsoleRE
{
	bool MagicTarget::HasMagicEffect(EffectSetting* a_effect)
	{
		using func_t = decltype(&MagicTarget::HasMagicEffect);
		Relocation<func_t> func("", 0x6399B0);
		return func(this, a_effect);
	}
}