#include "../String/PapyrusExtString.h"

#include "../../../../../../source/B/BSFixedString.h"
#include "../../../../../../source/N/NativeFunction.h"
#include "../../../../../../source/P//PackUnpackImpl.h"

#include <algorithm>
#include <string>
#include <cctype>
#include <functional>

namespace PapyrusExtString
{
	// I really hate doing this...
	using namespace ConsoleRE;

	std::vector<BSFixedString> Split(StaticFunctionTag* thisInput, BSFixedString theString, BSFixedString theDelimiter)
	{
		std::vector<BSFixedString> result;
	
		std::string str(theString.m_data);
		std::string delimiters(theDelimiter.m_data);
	
		std::string f(str);
		std::transform(f.begin(), f.end(), f.begin(), toupper);
		std::transform(delimiters.begin(), delimiters.end(), delimiters.begin(), toupper);
	
		std::string::size_type lastPos = f.find_first_not_of(delimiters, 0);
		std::string::size_type pos = f.find_first_of(delimiters, lastPos);
	
		while (std::string::npos != pos || std::string::npos != lastPos)
		{
			std::string token = str.substr(lastPos, pos - lastPos); // Pull from original string
			result.push_back(BSFixedString(token.c_str()));
			lastPos = f.find_first_not_of(delimiters, pos);
			pos		= f.find_first_of(delimiters, lastPos);
		}
	
		return result;
	}

	uint32_t	  GetStringLength(StaticFunctionTag* tag, BSFixedString str)
	{
		if (!str.m_data)
			return 0;

		return strnlen(str.m_data, 8192);
	}

	BSFixedString GetChar(StaticFunctionTag* tag, BSFixedString str, int32_t index)
	{
		if (index < 0 || index >= strnlen(str.m_data, 8192))
			return NULL;

		char buf[2];
		buf[0] = str.m_data[index];
		buf[1] = '\0';
		return buf;
	}

	bool		  IsUpper(StaticFunctionTag* tag, BSFixedString str)
	{
		if (!str.m_data)
			return false;

		return std::isupper(str.m_data[0]);
	}
				  
	bool		  IsLower(StaticFunctionTag* tag, BSFixedString str)
	{
		if (!str.m_data)
			return false;

		return std::islower(str.m_data[0]);
	}
				  
	bool		  IsLetter(StaticFunctionTag* tag, BSFixedString str)
	{
		if (!str.m_data)
			return false;

		return std::isalpha(str.m_data[0]);
	}
				  
	bool		  IsNum(StaticFunctionTag* tag, BSFixedString str)
	{
		if (!str.m_data)
			return false;

		return std::isdigit(str.m_data[0]);
	}
				  
	bool		  IsPunctuation(StaticFunctionTag* tag, BSFixedString str)
	{
		if (!str.m_data)
			return false;

		return std::ispunct(str.m_data[0]);
	}
				  
	bool		  IsPrintable(StaticFunctionTag* tag, BSFixedString str)
	{
		if (!str.m_data)
			return false;

		return std::isprint(str.m_data[0]);
	}

	BSFixedString ToUpper(StaticFunctionTag* tag, BSFixedString str)
	{
		if (!str.m_data)
			return NULL;

		char buf[2];
		buf[0] = std::toupper(str.m_data[0]);
		buf[1] = '\0';

		return buf;
	}

	BSFixedString ToLower(StaticFunctionTag* tag, BSFixedString str)
	{
		if (!str.m_data)
			return NULL;

		static char buf[2];
		buf[0] = std::tolower(str.m_data[0]);
		buf[1] = '\0';

		return buf;
	}

	BSFixedString IntAsChar(StaticFunctionTag* tag, uint32_t c)
	{
		if (c > UINT8_MAX)
			return NULL;

		char buf[2];
		buf[0] = c;
		buf[1] = '\0';

		return buf;
	}

	uint32_t	  CharAsInt(StaticFunctionTag* tag, BSFixedString str)
	{
		return str.m_data[0];
	}

	BSFixedString Substring(StaticFunctionTag* tag, BSFixedString str, int32_t index, uint32_t Length)
	{
		if (!str.m_data || index < 0)
			return NULL;

		std::string string(str.m_data);
		if (index >= string.length())
			return NULL;
		
		if (Length)
		{
			auto st = string.substr(index, Length);
			return st.c_str();
		}
		else
		{
			auto st = string.substr(index);
			return st.c_str();
		}
	}

	uint32_t	  Find(StaticFunctionTag* tag, BSFixedString str, BSFixedString fnd, int32_t index)
	{
		if (!str.m_data || !fnd.m_data)
		{
			return -1;
		}

		std::string::size_type pos = -1;
		if (index < 0)
		{
			index = 0;
		}

		auto strfnd = std::string(fnd.m_data);
		auto string = std::string(str.m_data);
		if (index >= string.length())
		{
			return -1;
		}

		// std::transform(strfnd.begin(), strfnd.end(), strfnd.begin(), std::tolower);
		// std::transform(string.begin(), string.end(), string.begin(), std::tolower);

		if ((pos = string.find(strfnd, index)) == std::string::npos)
		{
			return -1;
		}
		else
		{
			return pos;
		}
	}

	bool RegisterString(ConsoleRE::BSScript::Internal::VirtualMachine* VM)
	{
		// VM->RegisterFunction(new BSScript::NativeFunction1<decltype(ToUpper),         StaticFunctionTag, BSFixedString, BSFixedString>				      ("ToUpper",	    "StringUtil", ToUpper));
		// VM->RegisterFunction(new BSScript::NativeFunction1<decltype(ToLower),         StaticFunctionTag, BSFixedString, BSFixedString>				      ("ToLower",	    "StringUtil", ToLower));
		// VM->SetFunctionFlags("StringUtil", "ToUpper", 			true);
		// VM->SetFunctionFlags("StringUtil", "ToLower", 			true);

		//
		VM->RegisterFunction(new BSScript::NativeFunction<false, NFDLSE(Split), StaticFunctionTag, std::vector<BSFixedString>, BSFixedString, BSFixedString>		 ("Split",			"StringUtil", Split));
		//

		VM->RegisterFunction(new BSScript::NativeFunction<false, NFDLSE(GetStringLength), StaticFunctionTag, uint32_t, BSFixedString>				                 ("GetLength",      "StringUtil", GetStringLength));
		VM->RegisterFunction(new BSScript::NativeFunction<false, NFDLSE(IsLetter),        StaticFunctionTag, bool, BSFixedString>							         ("IsLetter",       "StringUtil", IsLetter));
		VM->RegisterFunction(new BSScript::NativeFunction<false, NFDLSE(IsNum),		      StaticFunctionTag, bool, BSFixedString>							         ("IsDigit",        "StringUtil", IsNum));
		VM->RegisterFunction(new BSScript::NativeFunction<false, NFDLSE(IsPunctuation),   StaticFunctionTag, bool, BSFixedString>                                    ("IsPunctuation",  "StringUtil", IsPunctuation));
		VM->RegisterFunction(new BSScript::NativeFunction<false, NFDLSE(IsPrintable),     StaticFunctionTag, bool, BSFixedString>                                    ("IsPrintable",    "StringUtil", IsPrintable));
		VM->RegisterFunction(new BSScript::NativeFunction<false, NFDLSE(IntAsChar),		  StaticFunctionTag, BSFixedString, uint32_t>						         ("AsChar",         "StringUtil", IntAsChar));
		VM->RegisterFunction(new BSScript::NativeFunction<false, NFDLSE(CharAsInt),		  StaticFunctionTag, uint32_t, BSFixedString>						         ("AsOrd",          "StringUtil", CharAsInt));
		VM->RegisterFunction(new BSScript::NativeFunction<false, NFDLSE(IsUpper),         StaticFunctionTag, bool,    BSFixedString>				                 ("IsUpper",        "StringUtil", IsUpper));
		VM->RegisterFunction(new BSScript::NativeFunction<false, NFDLSE(IsLower),         StaticFunctionTag, bool,    BSFixedString>				                 ("IsLower",        "StringUtil", IsLower));
		VM->RegisterFunction(new BSScript::NativeFunction<false, NFDLSE(GetChar),		  StaticFunctionTag, BSFixedString, BSFixedString, uint32_t>		         ("GetNthChar",     "StringUtil", GetChar));
		VM->RegisterFunction(new BSScript::NativeFunction<false, NFDLSE(Substring),       StaticFunctionTag, BSFixedString, BSFixedString, uint32_t, uint32_t>       ("Substring",		"StringUtil", Substring));
		VM->RegisterFunction(new BSScript::NativeFunction<false, NFDLSE(Find),			  StaticFunctionTag, uint32_t, BSFixedString, BSFixedString, uint32_t>       ("Find",			"StringUtil", Find));
		
		VM->SetCallableFromTasklets("StringUtil", "GetLength",    		true);
		VM->SetCallableFromTasklets("StringUtil", "IsLetter",     		true);
		VM->SetCallableFromTasklets("StringUtil", "IsDigit",      		true);
		VM->SetCallableFromTasklets("StringUtil", "IsPunctuation",		true);
		VM->SetCallableFromTasklets("StringUtil", "IsPrintable",		true);
		VM->SetCallableFromTasklets("StringUtil", "AsChar",  			true);
		VM->SetCallableFromTasklets("StringUtil", "AsOrd",   			true);
		VM->SetCallableFromTasklets("StringUtil", "IsUpper", 			true);
		VM->SetCallableFromTasklets("StringUtil", "IsLower", 			true);
		VM->SetCallableFromTasklets("StringUtil", "GetNthChar", 		true);
		VM->SetCallableFromTasklets("StringUtil", "Substring",  		true);
		VM->SetCallableFromTasklets("StringUtil", "Find",       		true);

		return true;
	}
}