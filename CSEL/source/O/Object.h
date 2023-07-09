#pragma once

#include "../B/BSFixedString.h"
#include "../B/BSTSmartPointer.h"
#include "../V/Variable.h"

namespace ConsoleRE
{
	namespace BSScript
	{
		class ObjectTypeInfo;

		class Object
		{
		public:
			~Object();

			uint64_t				GetHandle();
			ObjectTypeInfo*			GetTypeInfo();
			const ObjectTypeInfo*	GetTypeInfo() const;

			constexpr bool			IsConstructed() const noexcept { return static_cast<bool>(constructed); }
			constexpr bool			IsInitialized() const noexcept { return static_cast<bool>(initialized); }
			constexpr bool			IsValid() const noexcept { return static_cast<bool>(valid); }
			
			void*					Resolve(uint32_t a_typeID);
			
			void					IncRef();
			uint32_t				DecRef();
		public:
			uint32_t							 constructed : 1;            // 00 - 0
			uint32_t							 initialized : 1;            // 00 - 1
			uint32_t							 valid : 1;                  // 00 - 2
			uint32_t							 remainingPropsToInit : 29;  // 00 - 3
			BSTSmartPointer<ObjectTypeInfo>		 type;						 // 0x8
			BSFixedString						 currentState;				 // 0x10
			void*								 lockStructure;				 // 0x18
			volatile int64_t					 handle;					 // 0x20
			volatile int32_t					 refCountAndHandleLock;		 // 0x28
			uint32_t							 pad2C;						 // 0x2C
			Variable							 Variable[0];				 // 0x30
		private:
			void dtor();
		};
		static_assert(sizeof(Object) == 0x30);
	}
}