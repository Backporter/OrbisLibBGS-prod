#pragma once

#include "../B/BSIntrusiveRefCounted.h"

namespace ConsoleRE
{
	namespace BSScript
	{
		class Variable;
	}

	class BSStorage;

	namespace SkyrimScript
	{
		class DelayFunctor : public BSIntrusiveRefCounted
		{
		public:
			enum class FunctorType
			{
				kMoveTo = 0,
				kSetPosition = 6,
				kSetMotionType = 8,
				kDropObject = 12,
				kAttachAshPile = 14,
				kSendPlayerToJail = 19,
				kRemoveItem = 24
			};
		public:
			virtual ~DelayFunctor();

			// add
			virtual ConsoleRE::BSScript::Variable	Unk_02() = 0;
			virtual bool							IsLatent() const = 0;
			virtual bool							WantsRequeue() const;
			virtual bool							SaveImpl(BSStorage& a_storage) const;
			virtual FunctorType						GetType() const = 0;
			virtual bool							LoadImpl(const BSStorage& a_storage, uint32_t a_arg2, bool& a_arg3);
		public:
			uint32_t stackID;
		};
		static_assert(sizeof(DelayFunctor) == 0x10);
	}
}