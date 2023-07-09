#pragma once

#include "../H/hkArray.h"
#include "../H/hkReferencedObject.h"
#include "../H/hkVector4.h"

namespace ConsoleRE
{
	class hkpMoppCode : public hkReferencedObject
	{
	public:
		struct CodeInfo
		{
		public:
			hkVector4 offset;
		};
		static_assert(sizeof(CodeInfo) == 0x10);
	public:
		~hkpMoppCode() override;
	public:
		CodeInfo            info;
		hkArray<uint8_t>    data;
		int8_t				buildType;
	};
	static_assert(sizeof(hkpMoppCode) == 0x40);
}