#include "../B/BSScriptObjectBindPolicy.h"

namespace ConsoleRE
{
	namespace BSScript
	{
		void ObjectBindPolicy::BindObject(BSTSmartPointer<Object>& a_object, uint64_t a_handle)
		{
			using func_t = void(ObjectBindPolicy* const, BSTSmartPointer<Object>&, uint64_t);
			Relocation<func_t*> func("", 0x1552810);
			return func(this, a_object, a_handle);
		}
	}
}