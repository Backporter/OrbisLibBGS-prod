#pragma once

#include "../../../OrbisUtil/include/Relocation.h"

#include "../B/BSTArray.h"

namespace ConsoleRE
{
	class MiscStatManager
	{
	public:
		MiscStatManager() = delete;
		~MiscStatManager() = delete;
	public:
		class MiscStat
		{
		public:
			MiscStat() = delete;
			~MiscStat() = delete;
		public:
			const char* m_name;
			uint64_t	Unk08;
			uint32_t	m_value;
			uint32_t	Unk14;
		};

		class FindStatByCRC
		{
		public:
			FindStatByCRC();
			virtual ~FindStatByCRC();
			virtual uint32_t Find();
		};
	public:
		static MiscStatManager* GetSingleton() 
		{
			Relocation<MiscStatManager**> singleton("", 0x30C84F0);
			return *singleton;
		}

		MiscStat* Get(const char* a_name)
		{
			for (int i = 0; i < m_stats.size(); i++)
			{
				MiscStat* stat = &m_stats[i];
				if (!strcasecmp(a_name, stat->m_name))
				{
					return stat;
				}
			}

			return NULL;
		}
	public:
		BSTArray<MiscStat> m_stats;
	};
}