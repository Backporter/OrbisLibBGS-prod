#pragma once

#include "../B/BSFixedString.h"
#include "../B/BSIntrusiveRefCounted.h"
#include "../B/BSTSmartPointer.h"
#include "../T/TypeInfo.h"

namespace ConsoleRE
{
	namespace BSScript
	{
		class ObjectTypeInfo : public BSIntrusiveRefCounted
		{
		public:
			~ObjectTypeInfo();

			//
			const char*				GetName();
			ObjectTypeInfo*			GetParent();
			const ObjectTypeInfo*	GetParent() const;

			TypeInfo::RawType		GetRawType()	{ return static_cast<TypeInfo::RawType>(reinterpret_cast<size_t>(this)); }
		public:
			BSFixedString						name;
			BSTSmartPointer<ObjectTypeInfo>		parentTypeInfo;
			BSFixedString						unkstr;
		private:
			void Destory();
		};
	}
}
