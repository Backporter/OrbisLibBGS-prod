#pragma once

#include "../../../OrbisUtil/include/Relocation.h"

#include "../G/GMemory.h"

namespace ConsoleRE
{
	class GString
	{
	public:
		enum HeapType : size_t
		{
			HT_Global	= 0,
			HT_Local	= 1,
			HT_Dynamic	= 2,
			HT_Mask		= 3
		};

		struct FlagConstants
		{
			enum FlagConstant : size_t
			{
				kReserveIsSizeShift = static_cast<size_t>((sizeof(size_t) * 8 - 1))
			};
		};
		using FlagConstant = FlagConstants::FlagConstant;

		struct DataDesc
		{
			enum : size_t
			{
				kFullFlag = 1ull << FlagConstant::kReserveIsSizeShift
			};

			DataDesc() : capacity(1), refCount(1), data{ 0 }
			{}

			~DataDesc() { Release(); }

			void                AddRef()
			{
				__sync_add_and_fetch(&refCount, 1);
			}

			void                Release()
			{
				if (__sync_sub_and_fetch(&refCount, 1) == 0)
				{
					GFREE(this);
				}
			}
			
			size_t				GetCapacity() const
			{
				return capacity & ~kFullFlag;
			}
			
			bool				IsFull() const
			{
				return (capacity & kFullFlag) != 0;
			}
			
			void                SetFull(bool a_set)
			{
				if (a_set)
				{
					capacity |= kFullFlag;
				}
				else
				{
					capacity &= ~kFullFlag;
				}
			}
		public:
			size_t					capacity;
			volatile int32_t		refCount;
			char					data[1];
		};
		static_assert(sizeof(DataDesc) == 0x10);

		union DataDescUnion
		{
			DataDescUnion() : data(nullptr) { }

			DataDesc*	data;
			size_t		heapType;
		};
		static_assert(sizeof(DataDescUnion) == 0x8);
	public:
		GString(const char* a_str) 
		{ 
			ctor(a_str); 
		}
		
		~GString()
		{
			auto desc = get_desc();
			if (desc) 
			{
				desc->Release();
			}
		}

		const char* data() const noexcept
		{
			auto desc = get_desc();
			return desc ? desc->data : "";
		}

		char* data() noexcept
		{
			auto desc = get_desc();
			return desc ? desc->data : const_cast<char*>("");
		}

		const char* c_str() const noexcept
		{
			return data();
		}

		bool empty() const noexcept
		{
			return size() == 0;
		}

		size_t size() const noexcept
		{
			auto desc = get_desc();
			if (!desc) 
			{
				return 0;
			}
			else 
			{
				return desc->IsFull() ? desc->capacity : strlen(desc->data);
			}
		}

		size_t length() const noexcept
		{
			return size();
		}

		void clear() noexcept
		{
			auto desc = get_desc();
			if (desc)
			{
				desc->data[0] = '\0';
			}
		}

		static size_t BernsteinHashFunction(const void* a_dataIn, size_t a_size, size_t a_seed = 5381)
		{
			assert(a_dataIn);
			auto	dataIn = static_cast<const uint8_t*>(a_dataIn);
			size_t	hash;
			uint8_t byte = 0;

			for (hash = a_seed; a_size; hash = byte ^ 33 * hash) 
			{
				byte = *(dataIn + a_size-- - 1);
			}
			
			return hash;
		}
	protected:
		void ctor(const char* a_str)
		{
			using func_t = void(GString* const, const char*);
			Relocation<func_t*> func(__PRETTY_FUNCTION__, 0x112D000);
			func(this, a_str);
		}

		size_t heap_type() const
		{
			return _dataDesc.heapType & 3;
		}

		DataDesc* get_desc() const
		{
			DataDescUnion desc;
			desc.data = _dataDesc.data;
			desc.heapType &= ~HeapType::HT_Mask;
			return desc.data;
		}

		void set_desc(DataDesc* a_desc)
		{
			auto type = heap_type();
			_dataDesc.data = a_desc;
			assert((_dataDesc.heapType & HeapType::HT_Mask) == static_cast<HeapType>(0));
			_dataDesc.heapType |= type;
		}
	public:
		DataDescUnion _dataDesc;
	};
}