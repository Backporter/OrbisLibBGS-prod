#include "../../../OrbisUtil/include/Relocation.h"

#include "../N/NiBinaryStream.h"

namespace ConsoleRE
{
	NiBinaryStream::NiBinaryStream() :
		m_streamPosition(0),
		Unk0C(0),
		m_ReadFunc(nullptr),
		m_WriteFunc(nullptr)
	{}

	NiBinaryStream::~NiBinaryStream()
	{}

	uint32_t NiBinaryStream::Unk_04()
	{
		return m_streamPosition;
	}

	void NiBinaryStream::Unk_05(void* a_rsi)
	{ 
		using func_t = decltype(&NiBinaryStream::Unk_05);
		Relocation<func_t> func("", 0xE41040); 
		return func(this, a_rsi);
	}

	uint32_t NiBinaryStream::binary_read(void* a_buffer, uint32_t a_totalBytes, uint32_t* a_componentSizes, uint32_t a_numComponents)
	{
		assert(m_ReadFunc != nullptr);
		
		uint32_t bytesRead = m_ReadFunc(this, a_buffer, a_totalBytes, a_componentSizes, a_numComponents);
		m_streamPosition += bytesRead;
		return bytesRead;
	}
	
	uint32_t NiBinaryStream::binary_write(void* a_buffer, uint32_t a_totalBytes, uint32_t* a_componentSizes, uint32_t a_numComponents)
	{
		assert(m_WriteFunc != nullptr);

		uint32_t bytesWritten = m_WriteFunc(this, a_buffer, a_totalBytes, a_componentSizes, a_numComponents);
		m_streamPosition += bytesWritten;
		return bytesWritten;
	}
}