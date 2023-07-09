#pragma once

namespace ConsoleRE
{
	class GFxFileConstants
	{
	public:
		enum class FileFormatType
		{
			File_Unopened,
			File_Unknown,
			File_SWF,
			File_GFX,  
			File_JPEG = 10,
			File_PNG = 11,
			File_GIF = 12,
			File_TGA = 13,
			File_DDS = 14,
			File_HDR = 15,
			File_BMP = 16,
			File_DIB = 17,
			File_PFM = 18,
			File_TIFF = 19,
			File_NextAvail = 20,
			File_Original = 65535
		};
	};
}