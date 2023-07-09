#pragma once

#include "../B/BSAtomic.h"

#include "../../../OrbisUtil/include/INIHandler.h"
#include "../../../OrbisUtil/include/Relocation.h"
#include "../../../OrbisUtil/include/Types.h"
#include "../../../OrbisUtil/include/std.h"
#include "../../../OrbisUtil/include/MessageHandler.h"

#include <stdint.h>
#include <assert.h>
#include <atomic>

namespace ConsoleRE
{
	struct BSStringPool
	{
	public:
		class Entry
		{
		public:
			enum
			{
				kWide = 1 << 15,
				kRefCountMask = 0x7FFF,
				kLengthMask = 0xFFFFFF
			};
		public:
			static void release(const char*& a_entry) { release8(a_entry); }
			static void release(const wchar_t_t*& a_entry) { release16(a_entry);  }

			//
			static void release8(const char*& a_entry);
			static void release16(const wchar_t_t*& a_entry);

			// 
			void acquire();

			uint16_t crc() const noexcept { return _crc; }
			bool	 wide() const noexcept { return static_cast<bool>(_flags & kWide); }

			uint32_t length() const noexcept { return _length & kLengthMask; }
			uint32_t size() const noexcept	 { return length(); }

			const char* u8() const noexcept { return reinterpret_cast<const char*>(this + 1); }
			const wchar_t_t* u16() const noexcept { return reinterpret_cast<const wchar_t_t*>(this + 1); }

			template <typename T>
			const T* data() const noexcept;

		public:
			Entry*					_left;
			mutable uint16_t		_flags;
			volatile uint16_t		_crc;
			uint32_t				Unk0C;
			uint32_t				_length;
			uint32_t				Unk14;
			char					string[];
		};
		static_assert(sizeof(Entry) == 0x18);
	public:
	};
	static_assert(std::is_empty_v<BSStringPool>);

	struct BucketTable
	{
	public:
		enum HashMask
		{
			kEntryIndexMask = 0xFFFF,
			kLockIndexMask = 0x7F
		};
	public:
		static BucketTable* GetSingleton()
		{
			Relocation<BucketTable*> singleton("", 0x373C180);
			return singleton.get();
		}
	public:
		BSStringPool::Entry* buckets[0x10000];			// 00000
		mutable BSSpinLock   locks[0x1000 / 0x10];		// 80000
		bool                 initialized;				// 81000
	};
	static_assert(sizeof(BucketTable) == 0x81008);

	//
	template <>
	inline const char* BSStringPool::Entry::data<char>() const noexcept
	{
		assert(!wide());
		return u8();
	}

	template <>
	inline const wchar_t_t* BSStringPool::Entry::data<wchar_t_t>() const noexcept
	{
		assert(wide());
		return u16();
	}
}