#pragma once

// wchar_t_t
#include "../../../OrbisUtil/include/Types.h"

// xxxxxx_t
#include <stdint.h>
#include <locale>
namespace ConsoleRE
{
	class NiBinaryStream
	{
	public:
		using func_t = uint32_t(NiBinaryStream*, const void*, uint32_t, uint32_t*, uint32_t);
	public:
		NiBinaryStream();
		virtual ~NiBinaryStream();

		// add
		virtual bool	 Unk_02() = 0;  
		virtual void	 Unk_03(int32_t) = 0;
		virtual uint32_t Unk_04();
		virtual void	 Unk_05(void* rsi);
		virtual void     Unk_06(bool) = 0;

		//
		uint64_t ReadStringW(wchar_t_t* dst, uint64_t len, wchar_t_t endl = L'\n')
		{
			// string length
			uint64_t stringlength = 0;

			// string character 
			wchar_t_t chr = 0;

			while (true)
			{
				// string is outside buffer length
				if (stringlength > len)
					break;

				// returns if the current position is < file size and can read any left bytes
				if (Unk_02())
				{
					// reads bytes into a buffer with the size of length and returns the size read, -1 in case of error
					if (read(&chr, 1) == 0)
					{
						dst[stringlength] = L'\0';
						return -1;
					}
				}
				else
				{
					// termanate the stirng
					dst[stringlength] = L'\0';

					// return the string length
					return stringlength;
				}

				// skip the endl, '\r'
				if (chr == L'\r')
					continue;

				// we are at the end of the string('\n'), termanate and return the string length
				if (chr == endl)
				{
					dst[stringlength] = L'\0';
					return stringlength;
				}

				// set the string character and increase the length
				dst[stringlength] = chr;
				stringlength++;
			}

			// return on error
			return -1;
		}

		//
		uint32_t binary_read(void* a_buffer, uint32_t a_totalBytes, uint32_t* a_componentSizes, uint32_t a_numComponents = 1);
		uint32_t binary_write(void* a_buffer, uint32_t a_totalBytes, uint32_t* a_componentSizes, uint32_t a_numComponents = 1);

		template <class CharT>
		bool get(CharT& a_ch);

		template <class CharT>
		bool read(CharT* a_str, uint32_t a_count);

		template <class CharT>
		bool put(CharT a_ch);

		template <class CharT>
		bool write(const CharT* a_str, uint32_t a_count);
	public:
		uint32_t	m_streamPosition;
		uint32_t	Unk0C;
		func_t*		m_ReadFunc;
		func_t*		m_WriteFunc;
	};
	static_assert(sizeof(NiBinaryStream) == 0x20);

	template <class CharT>
	inline bool NiBinaryStream::get(CharT& a_ch)
	{
		return read(&a_ch, 1);
	}

	template <class CharT>
	inline bool NiBinaryStream::read(CharT* a_str, uint32_t a_count)
	{
		uint32_t size = sizeof(CharT);
		uint32_t toRead = a_count * size;
		uint32_t bytesRead = binary_read(a_str, toRead, &size);
		return bytesRead == toRead;
	}

	template <class CharT>
	inline bool NiBinaryStream::put(CharT a_ch)
	{
		return write(&a_ch, 1);
	}

	template <class CharT>
	inline bool NiBinaryStream::write(const CharT* a_str, uint32_t a_count)
	{
		uint32_t size = sizeof(CharT);
		uint32_t toWrite = a_count * size;
		uint32_t bytesWritten = binary_write(a_str, toWrite, &size);
		return bytesWritten == toWrite;
	}
}

namespace std
{
	template <class CharT, class Traits, class Allocator>
	inline bool getline(ConsoleRE::NiBinaryStream& a_input, std::basic_string<CharT, Traits, Allocator>& a_str)
	{
		CharT delim = std::use_facet<std::ctype<CharT>>(std::locale()).widen('\n');
		return getline(a_input, a_str, delim);
	}

	template <class CharT, class Traits, class Allocator>
	inline bool getline(ConsoleRE::NiBinaryStream& a_input, std::basic_string<CharT, Traits, Allocator>& a_str, CharT a_delim)
	{
		a_str.erase();

		CharT c;
		auto  notEOF = a_input.get(c);
		if (notEOF) 
		{
			do 
			{
				if (!std::char_traits<CharT>::eq(c, a_delim)) 
				{
					a_str.push_back(c);
				}
				else 
				{
					break;
				}

				if (a_str.size() != a_str.max_size()) 
				{
					notEOF = a_input.get(c);
				}
				else 
				{
					break;
				}
			} while (notEOF);

			return true;
		}
		else 
		{
			return false;
		}
	}
}
