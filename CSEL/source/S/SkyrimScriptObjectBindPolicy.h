#pragma once

#include "../B/BSScriptObjectBindPolicy.h"
#include "../B/BSTHashMap.h"

namespace ConsoleRE
{
	namespace SkyrimScript
	{
		class ObjectBindPolicy : public BSScript::ObjectBindPolicy
		{
		public:
			~ObjectBindPolicy() override;

			// override (BSScript::ObjectBindPolicy)
			void Unk_02(void) override;
			void Unk_03(void) override;
			void Unk_04(void) override;
			void Unk_05(void) override;
			void Unk_06(void) override;
			void Unk_07(void) override;
			void Unk_08(void) override;
			void Unk_09(void) override;
			void Unk_10(void) override;
			void Unk_11(void) override;
			void Unk_12(void) override;
			void Unk_13(void) override;
		private:
			uint64_t					 unk50;
			uint64_t					 unk58;
			BSTHashMap<UnkKey, UnkValue> unk60;
			uint64_t					 unk90;
			uint64_t					 unk98;
			uint64_t					 unkA0;
			BSTHashMap<UnkKey, UnkValue> unkA8;
		};
		static_assert(sizeof(ObjectBindPolicy) == 0xB0);
	}
}