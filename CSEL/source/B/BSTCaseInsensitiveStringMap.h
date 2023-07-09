#pragma once

#include "../N/NiTStringMap.h"

namespace ConsoleRE
{
	template <typename T>
	class BSTCaseInsensitiveStringMap : public NiTStringMap<T>
	{
	public:
		virtual ~BSTCaseInsensitiveStringMap();
	public:
	};
}