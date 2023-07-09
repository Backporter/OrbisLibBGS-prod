#pragma once

#include "../B/BSFixedString.h"
#include "../B/BSTSmartPointer.h"

namespace ConsoleRE
{
	namespace BSScript
	{
		class Object;

		class IVMObjectBindInterface
		{
		public:
			virtual ~IVMObjectBindInterface();
			
			// add (IVMObjectBindInterface)
			virtual uint64_t			   GetBoundHandle(const BSTSmartPointer<Object>& a_objPtr) const = 0;
			virtual bool                   TypeCanBeBound(const BSFixedString& a_className, uint64_t a_handle) = 0;
			virtual void                   BindObject(BSTSmartPointer<Object>& a_objPtr, uint64_t a_handle, bool a_conditional) = 0;
			virtual void                   HandleLoadedBinding(BSTSmartPointer<Object>& a_objPtr, uint64_t a_handle, bool a_conditional) = 0;
			virtual void                   RemoveAllBoundObjects(uint64_t a_handle) = 0;
			virtual void                   RemoveAllDiskLoadedBoundObjects(uint64_t a_handle) = 0;
			virtual void                   HandleCObjectDeletion(uint64_t a_handle) = 0;
			virtual void                   UnbindObject(const BSTSmartPointer<Object>& a_objPtr) = 0;
			virtual bool                   CreateObjectWithProperties(const BSFixedString& a_className, uint32_t a_numProperties, BSTSmartPointer<Object>& a_objPtr) = 0;
			virtual bool                   InitObjectProperties(BSTSmartPointer<Object>& a_objPtr, void* a_property, bool a_arg3) = 0;
		private:
		};
	}
}