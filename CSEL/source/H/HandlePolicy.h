#pragma once

#include "../../../OrbisUtil/include//Relocation.h"

#include "../B/BSTHashMap.h"
#include "../I/IObjectHandlePolicy.h"

#include <stdint.h>

namespace ConsoleRE
{
	namespace SkyrimScript
	{
		class HandlePolicy : public BSScript::IObjectHandlePolicy
		{
		public:
			static inline HandlePolicy* GetSingleton() { Relocation<HandlePolicy**> Singleton("HandlePolicy:Singleton", 0x399F5B0); return *Singleton; }

			~HandlePolicy() override;

			// override (BSScript::IObjectHandlePolicy)
			bool     HandleIsType(uint32_t a_typeID, uint64_t a_handle) override;
			bool     IsHandleObjectAvailable(uint64_t a_handle) override;
			uint64_t EmptyHandle() override;
			uint64_t GetHandleForObject(uint32_t a_typeID, const void* a_srcData) override;
			bool     HasParent(uint64_t a_handle) override;
			uint64_t GetParentHandle(uint64_t a_handle) override;
			uint64_t GetHandleScriptsMovedFrom(uint64_t a_handle) override;
			void*    GetObjectForHandle(uint32_t a_typeID, uint64_t a_handle) override;
			void     PersistHandle(uint64_t a_handle) override;
			void     ReleaseHandle(uint64_t a_handle) override;
			void     ConvertHandleToString(uint64_t a_handle, BSFixedString& a_strOut) override;
		public:
			uint64_t					 Unk08;
			uint64_t				     Unk10;
			BSTHashMap<UnkKey, UnkValue> unk18;  // 10
			BSTHashMap<UnkKey, UnkValue> unk38;  // 40
		};
		static_assert(sizeof(HandlePolicy) == 0x58, "#");
	}
}