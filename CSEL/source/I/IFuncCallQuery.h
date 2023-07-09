#pragma once

#include "../V/Variable.h"
#include "../B/BSTArray.h"
#include "../B/BSIntrusiveRefCounted.h"
#include "../B/BSTSmartPointer.h"

namespace ConsoleRE
{
	namespace BSScript
	{
		namespace Internal
		{
			class IFuncCallQuery : public BSIntrusiveRefCounted
			{
			public:
				IFuncCallQuery();
				virtual ~IFuncCallQuery();

				virtual bool Unk_02(uint32_t&, BSTSmartPointer<ObjectTypeInfo>&, BSFixedString&, Variable&, BSScrapArray<Variable>&) = 0;
			public:
			};
		}
	}
}