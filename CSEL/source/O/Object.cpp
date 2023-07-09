#include "../../../OrbisUtil/include/Relocation.h"

#include "../O/Object.h"

#include "../I/IObjectHandlePolicy.h"
#include "../O/ObjectTypeInfo.h"
#include "../V/VirtualMachine.h"

namespace ConsoleRE
{
	namespace BSScript
	{
		Object::~Object()
		{
			dtor();
		}

		uint64_t Object::GetHandle()
		{
			using func_t = uint64_t(Object* const);
			Relocation<func_t*> func("", 0x154E840);
			return func(this);
		}

		ObjectTypeInfo*	Object::GetTypeInfo()
		{
			return type.get();
		}

		const ObjectTypeInfo* Object::GetTypeInfo() const
		{
			return type.get();
		}

		void* Object::Resolve(uint32_t a_typeID)
		{
			auto vm = Internal::VirtualMachine::GetSingleton();
			auto policy = vm ? vm->GetObjectHandlePolicy() : nullptr;
			auto handle = GetHandle();

			if (policy && policy->HandleIsType(a_typeID, handle) && policy->IsHandleObjectAvailable(handle))
			{
				return policy->GetObjectForHandle(a_typeID, handle);
			}
			else
			{
				return nullptr;
			}
		}

		void Object::IncRef()
		{
			using func_t = void(Object* const);
			Relocation<func_t*> func("", 0x154E660);
			return func(this);
		}

		uint32_t Object::DecRef()
		{
			using func_t = uint32_t(Object* const);
			Relocation<func_t*> func("", 0x154E750);
			return func(this);
		}


		void Object::dtor()
		{
			using func_t = void(Object* const);
			Relocation<func_t*> func("", 0x154D630);
			func(this);
		}
	}
}