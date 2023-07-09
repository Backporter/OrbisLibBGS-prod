#pragma once

#include "../B/BSFixedString.h"
#include "../L/Location.h"

namespace ConsoleRE
{
	namespace BSResource
	{
		class LooseFileLocation : public Location
		{
		public:
			~LooseFileLocation() override;

			// override (Location)
			ErrorCode                   DoCreateStream(const char* a_path, BSTSmartPointer<Stream>& a_stream, Location*& a_location, bool a_readOnly) override;
			ErrorCode                   DoCreateAsyncStream(const char* a_path, BSTSmartPointer<AsyncStream>& a_out, Location*& a_location, bool a_readOnly) override;
			ErrorCode                   DoTraversePrefix(const char* a_path, LocationTraverser& a_traverser) override;
			ErrorCode                   DoGetInfo1(const char* a_path, Info& a_info, Location*& a_location) override;
			ErrorCode                   DoGetInfo2(const char* a_path, Info& a_info, LocationTraverser* a_traverser) override;
			ErrorCode                   DoDelete(const char* a_path) override;
			const char*                 DoGetName() const override;
			uint32_t 					DoGetMinimumAsyncPacketSize() const override;
		public:
			BSFixedString	prefix;
			uint32_t		minimumAsyncPacketSize;
			bool			asyncSupported;
			uint8_t			pad1D;
			uint16_t		pad1E;
		};
		static_assert(sizeof(LooseFileLocation) == 0x20);
	}
}