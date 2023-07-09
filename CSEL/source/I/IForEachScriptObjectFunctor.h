#pragma once

#include <stdint.h>

namespace ConsoleRE
{
	namespace BSScript
	{
		class IForEachScriptObjectFunctor
		{
		public:
			struct ScriptObject
			{
			    uint32_t        unk00;
				ObjectTypeInfo*	typeInfo;
			    void*           unk08;
			    uint32_t        unk0C;
			    uint32_t        unk10;
			    uint32_t		handle;
			};
			static_assert(sizeof(ScriptObject) == 0x28);
		public:
			virtual ~IForEachScriptObjectFunctor();

			virtual bool Unk_02(ScriptObject*, void*) = 0;
		private:
		};
	}
}
