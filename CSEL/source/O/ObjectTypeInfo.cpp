#include "../../../OrbisUtil/include/Relocation.h"

#include "../O/ObjectTypeInfo.h"

namespace ConsoleRE
{
	namespace BSScript
	{
		ObjectTypeInfo::~ObjectTypeInfo()
		{
			Destory();
		}

		const char*	ObjectTypeInfo::GetName()
		{
			return name.c_str();
		}

		ObjectTypeInfo*	ObjectTypeInfo::GetParent() 
		{ 
			return parentTypeInfo.get();
		}

		const ObjectTypeInfo* ObjectTypeInfo::GetParent() const
		{
			return parentTypeInfo.get();
		}


		void ObjectTypeInfo::Destory()
		{
			using func_t = void(ObjectTypeInfo* const);
			Relocation<func_t*> func("", 0x15570E0);
			func(this);
		}
	}
}