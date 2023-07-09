#pragma once

#include "../B/BSExtraData.h"
#include "../E/ExtraDataTypes.h"

namespace ConsoleRE
{
	class BGSKeyword;
	class TESObjectREFR;

	class ExtraMissingLinkedRefIDs : public BSExtraData
	{
	public:
		static constexpr int TypeID = ExtraDataType<ExtraDataTypes::kMissingLinkedRefIDs>;

		struct Entry
		{
		public:
			BGSKeyword* keyword;
			uint32_t	linkedRefID;
		};

		struct Array
		{
		public:
			union Data
			{
				Entry* entryPtr;
				Entry  entry[1];
			};
			static_assert(sizeof(Data) == 0x10);
		public:
			Entry& operator[](uint32_t a_idx)
			{
				assert(a_idx < size());
				return size() > 1 ? m_data.entryPtr[a_idx] : m_data.entry[a_idx];
			}

			Entry* begin()
			{
				return size() > 1 ? m_data.entryPtr : m_data.entry;
			}

			Entry* end()
			{
				return size() > 1 ? std::addressof(m_data.entryPtr[size()]) : std::addressof(m_data.entry[size()]);
			}

			uint32_t size()
			{
				return m_size;
			}
		public:
			Data	 m_data;
			uint32_t m_size;
		};
	public:
		~ExtraMissingLinkedRefIDs() override;

		// override (BSExtraData)
		uint32_t GetType() const override;

		//
		TESObjectREFR* GetLinkedRef(BGSKeyword* a_keyword);
	public:
		Array entries;
	};
	static_assert(sizeof(ExtraMissingLinkedRefIDs) == 0x28);
}
