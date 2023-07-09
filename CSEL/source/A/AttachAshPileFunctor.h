#pragma once

#include "../B/BSTSmartPointer.h"
#include "../D/DelayFunctor.h"

namespace ConsoleRE
{
	namespace BSScript
	{
		class IVirtualMachine;
	}

	class TESBoundObject;

	namespace SkyrimScript
	{
		class AttachAshPileFunctor : public DelayFunctor
		{
		public:
			virtual ~AttachAshPileFunctor();

			// override (DelayFunctor)
			virtual ConsoleRE::BSScript::Variable	Unk_02() override;
			virtual bool							IsLatent() const override;
			virtual bool							SaveImpl(BSStorage& a_storage) const override;
			virtual FunctorType						GetType() const override;
			virtual bool							LoadImpl(const BSStorage& a_storage, uint32_t a_arg2, bool& a_arg3) override;
		public:
			uint32_t									targetActor;
			uint32_t									pad14;
			TESBoundObject*								ashObject;
			BSTSmartPointer<BSScript::IVirtualMachine>	vm;
		};
		static_assert(sizeof(AttachAshPileFunctor) == 0x28);
	}
}