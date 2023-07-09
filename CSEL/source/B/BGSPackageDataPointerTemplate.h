#pragma once

#include "../B/BGSNamedPackageData.h"
#include "../B/BSFixedString.h"

namespace ConsoleRE
{
	template <class P, class T>
	class BGSPackageDataPointerTemplate : public BGSNamedPackageData<P>
	{
	public:
		virtual ~BGSPackageDataPointerTemplate();
	public:
		T* pointer;
	};
}