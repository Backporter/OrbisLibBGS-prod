#include "../V/Variable.h"

#include "../A/Array.h"
#include "../O/Object.h"
#include "../O/ObjectTypeInfo.h"
#include "../P/PackUnpack.h"

#define USE_IMPL 1

namespace ConsoleRE
{
	namespace BSScript
	{
		BSTSmartPointer<Array>	Variable::GetArray()  { return args.arr; }
		BSTSmartPointer<Object>	Variable::GetObject() { return args.obj; }

		void Variable::SetArray(BSTSmartPointer<Array> a_val)
		{
			assert(a_val);
			ChangeType(a_val->type());
			args.arr = std::move(a_val);
		}


		void Variable::SetObject(BSTSmartPointer<Object> a_val)
		{
			assert(a_val);
			ChangeType(a_val->GetTypeInfo()->GetRawType());
			args.obj = std::move(a_val);
		}

		void Variable::SetObject(BSTSmartPointer<Object> a_val, TypeInfo::RawType a_type)
		{
			assert(a_val);
			ChangeType(a_type);
			args.obj = std::move(a_val);
		}

		void Variable::Destroy()
		{
#if USE_IMPL
			switch (type.GetUnmangledRawType())
			{
				case TypeInfo::RawType::kObject:
					args.obj.~BSTSmartPointer();
					break;
				case TypeInfo::RawType::kString:
					args.str.~BSFixedString();
					break;
				case TypeInfo::RawType::kNone:
				case TypeInfo::RawType::kInt:
				case TypeInfo::RawType::kFloat:
				case TypeInfo::RawType::kBool:
					break;
				case TypeInfo::RawType::kObjectArray:
				case TypeInfo::RawType::kStringArray:
				case TypeInfo::RawType::kIntArray:
				case TypeInfo::RawType::kFloatArray:
				case TypeInfo::RawType::kBoolArray:
					args.arr.~BSTSmartPointer();
					break;
				default:
					assert(false);
					break;
			}
#else
			using func_t = void(Variable* const);
			Relocation<func_t*> func("", 0x1570F50);
			return func(this);
#endif
		}

		void Variable::Swap(const Variable& a_rhs)
		{
#if USE_IMPL
			type = a_rhs.type;
			switch (type.GetUnmangledRawType())
			{
			case TypeInfo::RawType::kObject:
				args.obj = a_rhs.args.obj;
				break;
			case TypeInfo::RawType::kString:
				args.str = a_rhs.args.str;
				break;
			case TypeInfo::RawType::kNone:
			case TypeInfo::RawType::kInt:
			case TypeInfo::RawType::kFloat:
			case TypeInfo::RawType::kBool:
				args.p = a_rhs.args.p;
				break;
			case TypeInfo::RawType::kObjectArray:
			case TypeInfo::RawType::kStringArray:
			case TypeInfo::RawType::kIntArray:
			case TypeInfo::RawType::kFloatArray:
			case TypeInfo::RawType::kBoolArray:
				args.arr = a_rhs.args.arr;
				break;
			default:
				assert(false);
				break;
			}
#else
			using func_t = void(Variable* const, const Variable*);
			Relocation<func_t*> func("", 0x1572580);
			return func(this, dst);
#endif
		}
	}
}