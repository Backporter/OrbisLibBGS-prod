#pragma once

#include "../I/IStore.h"

namespace ConsoleRE
{
	namespace BSScript
	{
		namespace UnlinkedTypes
		{
			class Object;
		}

		class IStore;

		struct ILoader
		{
		public:
			virtual ~ILoader();

			// add
			virtual ILoader* Clone() = 0;
			virtual void	 SetScriptStore(const BSTSmartPointer<IStore>& a_store) = 0;
			virtual bool	 GetClass(const char* a_name, UnlinkedTypes::Object&) = 0;
		};
		static_assert(sizeof(ILoader) == 0x8);
	}
}