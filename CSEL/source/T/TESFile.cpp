// #include "../T/TESFile.h"
// 
// namespace ConsoleRE
// {
// 	bool TESFile::IsFormInMod(uint32_t a_formID) const
// 	{
// 		if (!IsLight() && (a_formID >> 24) == compileIndex)
// 		{
// 			return true;
// 		}
// 
// 		if (IsLight() && (a_formID >> 24) == 0xFE && ((a_formID & 0x00FFF000) >> 12) == smallFileCompileIndex)
// 		{
// 			return true;
// 		}
// 
// 		return false;
// 	}
// }