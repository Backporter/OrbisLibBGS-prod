#pragma once

#include "../B/BSAtomic.h"
#include "../B/BSTHashMap.h"
#include "../B/BSTSmartPointer.h"

namespace ConsoleRE
{
	namespace BSScript
	{
		class IVirtualMachine;
		class Object;
		class IVMObjectBindInterface;

		class ObjectBindPolicy
		{
		public:
			virtual ~ObjectBindPolicy();

			// add
			virtual void Unk_02() = 0;
			virtual void Unk_03() = 0;
			virtual void Unk_04() = 0;
			virtual void Unk_05() = 0;
			virtual void Unk_06() = 0;
			virtual void Unk_07() = 0;
			virtual void Unk_08() = 0;
			virtual void Unk_09() = 0;
			virtual void Unk_10() = 0;
			virtual void Unk_11() = 0;
			virtual void Unk_12() = 0;
			virtual void Unk_13() = 0;

			void BindObject(BSTSmartPointer<Object>& a_object, uint64_t a_handle);
		private:
			IVirtualMachine*               vm;
			IVMObjectBindInterface*        bindInterface;
			mutable BSSpinLock             attachedScriptsLock;
			BSTHashMap<uint64_t, UnkValue> attachedScripts;
		};
		static_assert(sizeof(ObjectBindPolicy) == 0x48);
	}
}