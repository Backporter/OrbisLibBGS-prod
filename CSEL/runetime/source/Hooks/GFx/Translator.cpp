#include "Translator.h"

//
#include "../../../../../OrbisUtil/include/Types.h"
#include "../../../../../OrbisUtil/include/Macro.h"
#include "../../../../../OrbisUtil/include/MessageHandler.h"
#include "../../../../../OrbisUtil/include/Logger.h"
#include "../../../../../OrbisUtil/include/INIHandler.h"

// BGS
#include "../../../../source/B/BSResourceNiBinaryStream.h"

// C++
#include <string>
#include <algorithm>

typedef void(*_GetCachedString)(wchar_t_t**, wchar_t_t*, uint32_t);
Relocation<_GetCachedString> GetCachedString("", 0xE50340);

void ParseTranslation(const char* path, const char* language, ConsoleRE::BSScaleformTranslator* a)
{
	auto log  = xUtilty::Log::GetSingleton();
	auto attr = xUtilty::INIHandler::INIHandler::GetSingleton()->GetINIOptions();
	
	// byte order, should be 0xFEFF for utf-16
	uint16_t bom = 0;

	// buffer to hold the path for the file we need to read
	char buffer[128] { 0 };

	// put the file path inside the buffer
	sprintf(buffer, "interface\\translations\\%s_%s.txt", path, language);

	if (attr->IsDebugMode)
	{
		PRINT_FMT("[Info] Atempting to process translations in %s", buffer);
	}

	ConsoleRE::BSResourceNiBinaryStream translation(buffer);
	if (!translation.Unk_02())
	{
		log->Write(xUtilty::Log::logLevel::kWarning, "Faild to Get translation for \"%s\"", buffer);
		return;
	}

	log->Write(xUtilty::Log::logLevel::kInfo, "Reading translation for \"%s\"", buffer);

	uint32_t size = sizeof(uint16_t);
	if (translation.binary_read(&bom, sizeof(uint16_t) * 1, &size) != 2)
	{
		PRINT_POS_RETURN
	}

	if (bom != 0xFEFF)
	{
		PRINT_RETURN("bom is invalid got %d not %d", bom, 0xFEFF)
	}

	int index = 0;
	wchar_t_t wbuffer[512] { 0 };
	while (true)
	{
		auto stringlength = translation.ReadStringW(wbuffer, 512);
		if (stringlength == -1)
		{
			break;
		}

		if (stringlength < 4 || wbuffer[0] != L'$')
		{
			continue;
		}

		if (wbuffer[stringlength - 1] == L'\r')
		{
			stringlength--;
		}

		wbuffer[stringlength] = 0;

		for (int i = 0; i < stringlength; i++)
		{
			if (wbuffer[i] == static_cast<wchar_t_t>(L'\t'))
			{
				wbuffer[i] = static_cast<wchar_t_t>(L'\0');
				index = i + 1;
				break;
			}
		}

		if (index < 2)
		{
			continue;
		}

		wchar_t_t* key = NULL;
		wchar_t_t* translation = NULL;
		GetCachedString(&key, wbuffer, 0);
		GetCachedString(&translation, &wbuffer[index], 0);
		
		if (attr->IsDebugMode)
		{
			xUtilty::KernelPrintOut("Key: \"%S\", Translation: \"%S\"", key, translation);
		}

		auto ret = a->translator.translationMap.emplace(key, translation);
#if NDEBUG
		if (attr->IsDebugMode)
		{
#endif
			auto log = xUtilty::Log::GetSingleton();

			if (ret)
			{
				log->Write(xUtilty::Log::logLevel::kDebug, "Inserted \"%S\" -> \"%S\" into translationMap!", key, translation);

			}
			else
			{
				log->Write(xUtilty::Log::logLevel::kDebug, "Failed to Insert \"%S\" -> \"%S\" into translationMap!", key, translation);
			}
#if NDEBUG
		}
#endif
	}
}