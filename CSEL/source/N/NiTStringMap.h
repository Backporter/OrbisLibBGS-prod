#pragma once

#include "../N/NiTMap.h"

namespace ConsoleRE
{
	template <class Parent, class T>
	class NiTStringTemplateMap : public Parent
	{
	public:
		NiTStringTemplateMap(uint32_t a_hashSize = 37, bool a_copy = true) : 
			Parent(a_hashSize), 
			m_copy(a_copy) 
		{}
		
		virtual ~NiTStringTemplateMap();
	public:
		bool	m_copy;
	};


	template <class T>
	class NiTStringMap : public NiTStringTemplateMap<NiTMap<const char*, T>, T>
	{
	public:
		virtual ~NiTStringMap();
	};
}