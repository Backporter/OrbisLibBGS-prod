#pragma once

#include "../B/BSTSmartPointer.h"
#include "../E/ErrorCodes.h"

namespace ConsoleRE
{
	namespace BSResource
	{
		class AsyncStream;
		class LocationTraverser;
		class Stream;
		struct Info;

		class Location
		{
		public:
			Location();
			virtual ~Location();

			// add
			virtual ErrorCode                   DoMount();
			virtual void                        DoUnmount();
			virtual ErrorCode                   DoCreateStream(const char* a_path, BSTSmartPointer<Stream>& a_stream, Location*& a_location, bool a_readOnly) = 0;
			virtual ErrorCode                   DoCreateAsyncStream(const char* a_path, BSTSmartPointer<AsyncStream>& a_out, Location*& a_location, bool a_readOnly);
			virtual ErrorCode                   DoTraversePrefix(const char* a_path, LocationTraverser& a_traverser) = 0;
			virtual ErrorCode                   DoGetInfo1(const char* a_path, Info& a_info, Location*& a_location);
			virtual ErrorCode                   DoGetInfo2(const char* a_path, Info& a_info, LocationTraverser* a_traverser);
			virtual ErrorCode                   DoDelete(const char* a_path);
			virtual const char*   				DoGetName() const;
			virtual uint32_t 					DoQBufferHint() const;
			virtual uint32_t 					DoGetMinimumAsyncPacketSize() const;
		public:
			bool     mounted;
			uint8_t  pad09;
			uint16_t pad0A;
			uint32_t pad0C;
		};
		static_assert(sizeof(Location) == 0x10);
	}
}