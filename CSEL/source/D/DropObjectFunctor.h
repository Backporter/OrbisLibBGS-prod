#pragma once

#include "../B/BSTSmartPointer.h"
#include "../D/DelayFunctor.h"

namespace ConsoleRE
{
	namespace BSScript
	{
		class IVirtualMachine;
	}

	namespace SkyrimScript
	{
		class DropObjectFunctor : public DelayFunctor
		{
		public:
			~DropObjectFunctor() override;

			// override (DelayFunctor)
			ConsoleRE::BSScript::Variable	Unk_02() override;
			bool							IsLatent() const override;
			bool							SaveImpl(BSStorage& a_storage) const override;
			FunctorType						GetType() const override;
			bool							LoadImpl(const BSStorage& a_storage, uint32_t a_arg2, bool& a_arg3) override;
		public:
			uint32_t									dropper;
			uint32_t									itemToDrop;
			uint32_t									countToDrop;
			uint32_t									pad1C;
			BSTSmartPointer<BSScript::IVirtualMachine>	vm;
		};
		static_assert(sizeof(DropObjectFunctor) == 0x28);
	}
}