#pragma once

#include "../B/BSTSmartPointer.h"
#include "../E/ErrorCodes.h"
#include "../N/NiBinaryStream.h"
#include "../S/Stream.h"

// std::string
#include <string>

namespace ConsoleRE
{
	namespace BSResource
	{
		class Location;
	}

	class BSResourceNiBinaryStream : public NiBinaryStream
	{
	public:
		struct BufferType
		{
		public:
		};
	public:
		BSResourceNiBinaryStream();
		BSResourceNiBinaryStream(const char* a_path);
		BSResourceNiBinaryStream(const std::string& a_fileName);
		~BSResourceNiBinaryStream() override;
		
		//
		bool     Unk_02() override;
		void     Unk_03(int32_t) override;
		uint32_t Unk_04() override;
		void	 Unk_05(void*) override;
		void	 Unk_06(bool) override;
	protected:
		BSTSmartPointer<BSResource::Stream> stream;
		BufferType*                         buffer;
		uint32_t							streamPos;
		BSResource::ErrorCode               lastError;
	protected:
		void Ctor(const char* a_name, bool a_writeable = false, BSResource::Location* a_optionalStart = 0);
		void Dtor();
	};
	static_assert(sizeof(BSResourceNiBinaryStream) == 0x38);

}