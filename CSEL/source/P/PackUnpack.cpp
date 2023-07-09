#include "../P/PackUnpack.h"

#include "../B/BSScriptObjectBindPolicy.h"
#include "../I/IObjectHandlePolicy.h"
#include "../O/Object.h"
#include "../O/ObjectTypeInfo.h"
#include "../V/Variable.h"
#include "../V/VirtualMachine.h"

namespace ConsoleRE
{
	namespace BSScript
	{
		TypeInfo::RawType GetRawTypeFromVMType(uint32_t a_typeID)
		{
			auto vm = Internal::VirtualMachine::GetSingleton();
			BSTSmartPointer<ObjectTypeInfo> typeinfo;
			if (vm && vm->GetScriptObjectType(a_typeID, typeinfo))
			{
				return typeinfo->GetRawType();
			}
			else
			{
				//
				return TypeInfo::RawType::kNone;
			}
		}

		void			  BindID(BSTSmartPointer<Object>& a_objectPtr, const void* a_src, uint32_t a_typeID)
		{
			uint32_t id = 0;
			auto vm = Internal::VirtualMachine::GetSingleton();

			BSTSmartPointer<ObjectTypeInfo> typeinfo(a_objectPtr->GetTypeInfo());
			if (vm && typeinfo && vm->GetTypeIDForScriptObject(typeinfo->GetName(), id))
			{
				auto handlePolicy = vm->GetObjectHandlePolicy();
				if (handlePolicy)
				{
					auto handle = handlePolicy->GetHandleForObject(a_typeID, a_src);

					if (handlePolicy->HandleIsType(id, handle) && handlePolicy->IsHandleObjectAvailable(handle))
					{
						auto bindPolicy = vm->GetObjectBindPolicy();
						if (bindPolicy)
						{
							bindPolicy->BindObject(a_objectPtr, handle);
						}
					}

				}
			}
		}

		void			  PackHandle(Variable* a_dst, const void* a_src, uint32_t a_typeID)
		{
			assert(a_dst);
			a_dst->SetNone();

			if (!a_src)
			{
				return;
			}

			auto vm = Internal::VirtualMachine::GetSingleton();
			BSTSmartPointer<ObjectTypeInfo> objecttypeinfo;
			if (!vm || !vm->GetScriptObjectType(a_typeID, objecttypeinfo) || !objecttypeinfo)
			{
				return;
			}

			auto policy = vm->GetObjectHandlePolicy();
			if (!policy)
			{
				return;
			}

			auto handle = policy->GetHandleForObject(a_typeID, a_src);
			BSTSmartPointer<Object> objectPtr;

			if (!vm->FindBoundObject(handle, objecttypeinfo->GetName(), objectPtr))
			{
				if (vm->CreateObject(objecttypeinfo->GetName(), objectPtr) && objectPtr)
				{
					BindID(objectPtr, a_src, a_typeID);
				}
			}

			if (objectPtr)
			{
				a_dst->SetObject(objectPtr, objecttypeinfo->GetRawType());
			}
		}

		void*			  UnpackHandle(Variable* a_src, uint32_t a_typeID)
		{
			assert(a_src);
			const auto object = a_src->GetObject();
			return object ? object->Resolve(a_typeID) : nullptr;
		}
	}
}