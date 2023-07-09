#include "../B/BSResourceNiBinaryStream.h"

namespace ConsoleRE
{
	BSResourceNiBinaryStream::BSResourceNiBinaryStream() :
		NiBinaryStream(),
		stream(nullptr),
		buffer(nullptr),
		streamPos(0),
		lastError(BSResource::ErrorCode::kNone)
	{}

	BSResourceNiBinaryStream::BSResourceNiBinaryStream(const char* a_fileName) :
		NiBinaryStream(),
		stream(0),
		buffer(nullptr),
		streamPos(0),
		lastError(BSResource::ErrorCode::kNone)
	{
		Ctor(a_fileName);
	}

	BSResourceNiBinaryStream::BSResourceNiBinaryStream(const std::string& a_fileName) :
		BSResourceNiBinaryStream(a_fileName.c_str())
	{}

	BSResourceNiBinaryStream::~BSResourceNiBinaryStream()
	{
		Dtor();
	}

	bool BSResourceNiBinaryStream::Unk_02()
	{
		return static_cast<bool>(stream);
	}

	void BSResourceNiBinaryStream::Unk_03(int32_t rsi) 
	{
		using func_t = decltype(&BSResourceNiBinaryStream::Unk_03);
		Relocation<func_t> func("", 0xE79380); 
		func(this, rsi);
	}

	uint32_t BSResourceNiBinaryStream::Unk_04() 
	{ 
		return streamPos; 
	}

	void BSResourceNiBinaryStream::Unk_05(void* a_info)
	{
		using func_t = decltype(&BSResourceNiBinaryStream::Unk_05);
		Relocation<func_t> func("", 0xE794E0); 
		func(this, a_info); 
	}
	
	void BSResourceNiBinaryStream::Unk_06(bool a_flag)
	{ 
		using func_t = decltype(&BSResourceNiBinaryStream::Unk_06);
		Relocation<func_t> func("", 0xE79910); 
		func(this, a_flag);
	}

	void BSResourceNiBinaryStream::Ctor(const char* a_name, bool a_writeable, BSResource::Location* a_optionalStart)
	{
		using func_t = decltype(&BSResourceNiBinaryStream::Ctor);
		Relocation<func_t> func("", 0xE78FA0); 
		func(this, a_name, a_writeable, a_optionalStart);
	}

	void BSResourceNiBinaryStream::Dtor()
	{
		using func_t = decltype(&BSResourceNiBinaryStream::Dtor);
		Relocation<func_t> func("", 0xE79250); 
		func(this);
	}
}