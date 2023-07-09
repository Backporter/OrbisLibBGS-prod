#pragma once

#include "../../../OrbisUtil/include/Relocation.h"

#include "../B/BSFixedString.h"
#include "../B/BSTSmartPointer.h"
#include "../T/TypeInfo.h"

#include <stdint.h>

namespace ConsoleRE
{
	namespace BSScript
	{
		class Array;
		class Object;

		class Variable
		{
		public:
			union Value
			{
			public:
				Value(void* ptr = nullptr) : p(ptr) { }
				~Value() { }
			public:
				int32_t					i;
				uint32_t				ui;
				float					f;
				bool					b;
				void*					p;
				BSTSmartPointer<Array>	arr;
				BSTSmartPointer<Object>	obj;
				BSFixedString			str;
			};
			static_assert(sizeof(Value) == 0x8);
		public:
			Variable() : type(TypeInfo::RawType::kNone), args() 
			{}

			Variable(const TypeInfo& a_type) : type(a_type), args() 
			{}

			Variable(const Variable& a_rhs) : type(), args() 
			{
				Swap(a_rhs);
			}

			~Variable() 
			{
				Destroy();
				memset(this, 0, sizeof(*this));
			}

			Variable& operator=(const Variable& a_rhs)
			{
				if (this != std::addressof(a_rhs))
				{
					Destroy();
					Swap(a_rhs);
				}

				return *this;
			}

			Variable& operator=(Variable&& a_rhs)
			{
				if (this != std::addressof(a_rhs))
				{
					Destroy();
					
					type	= std::move(a_rhs.type);
					args.p	= std::move(a_rhs.args.p);

					a_rhs.args.p = nullptr;
				}

				return *this;
			}

			bool IsArray(void)			{ return type.IsArray(); }
			bool IsBool(void)			{ return type.IsBool(); }
			bool IsFloat(void)			{ return type.IsFloat(); }
			bool IsInt(void)			{ return type.IsInt(); }
			bool IsLiteralArray(void)	{ return type.IsLiteralArray(); }
			bool IsNoneArray(void)		{ return type.IsNoneArray(); }
			bool IsNoneObject(void)		{ return type.IsNoneObject(); }
			bool IsObject(void)			{ return type.IsObject(); }
			bool IsObjectArray(void)	{ return type.IsObjectArray(); }
			bool IsString(void)			{ return type.IsString(); }

			int32_t					GetInt()	{ return args.i; }
			uint32_t				GetUInt()	{ return args.ui; }
			float                   GetFloat()	{ return args.f; }
			bool                    GetBool()	{ return args.b; }
			BSFixedString	        GetString() { return args.str; }
			BSTSmartPointer<Array>	GetArray();
			BSTSmartPointer<Object>	GetObject();

			void SetNone() 
			{ 
				ChangeType(TypeInfo::RawType::kNone); 
			}

			void SetInt(int32_t a_val)
			{
				ChangeType(TypeInfo::RawType::kInt);
				args.i = a_val;
			}

			void SetUInt(uint32_t a_val)
			{
				ChangeType(TypeInfo::RawType::kInt);
				args.ui = a_val;
			}

			void SetFloat(float a_val)
			{
				ChangeType(TypeInfo::RawType::kFloat);
				args.f = a_val;
			}

			void SetBool(bool a_val)
			{
				ChangeType(TypeInfo::RawType::kBool);
				args.b = a_val;
			}

			void SetArray(BSTSmartPointer<Array> a_val);
			void SetObject(BSTSmartPointer<Object> a_val);
			void SetObject(BSTSmartPointer<Object> a_val, TypeInfo::RawType a_type);

			void SetString(BSFixedString str)
			{
				ChangeType(TypeInfo::RawType::kString);
				args.str = str;
			}

			template <typename T>
			void Pack(T&& a_src);

			template <typename T>
			T Unpack();
		protected:
			void ChangeType(TypeInfo::RawType a_type)
			{
				Destroy();
				type  = a_type;
				args.p = nullptr;
			}

			void Destroy();
			void Swap(const Variable&);
		public:
			TypeInfo  type;
			Value	  args;
		};
	}
}