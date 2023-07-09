#pragma once

#include "../B/BSTSmartPointer.h"
#include "../L/Location.h"
#include "../S/Stream.h"

namespace ConsoleRE
{
	namespace BSResource
	{
		class DevNull : public Location
		{
		public:
			struct NullStream : public Stream
			{
			public:
				~NullStream() override;
			};
		public:
			~DevNull() override;
		public:
			uint8_t					pad11;
			uint16_t				pad12;
			uint32_t				pad14;
			BSTSmartPointer<Stream> nullReader;
			BSTSmartPointer<Stream> nullWriter;
		};
		static_assert(sizeof(DevNull) == 0x28);
	}
}