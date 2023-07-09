#pragma once

#include "../../../OrbisUtil/include//Relocation.h"

#include "../B/BSFile.h"

#if defined(__ORBIS__)
#include <save_data.h>
#elif defined(__OPENORBIS__)
#include <orbis/SaveData.h>
typedef OrbisSaveDataMountResult SceSaveDataMountResult;
#endif

#include <stdint.h>

namespace ConsoleRE
{
	class BSOrbisSaveDataSystemUtility
	{
	public:
		class FileType // : public BSFile
		{
		public:
			FileType();
			virtual ~FileType();
			uint8_t pad[0xBE0];
		private:			
		};
		// 0xBE0
		static_assert(sizeof(FileType) != 0, "class size mismatch");

		virtual ~BSOrbisSaveDataSystemUtility();
		int		  CopyIn(char* Unk);								   // copies some data into Unk
		int		  CopyTo(const char* Unk0, char* Unk1);				   // does "strcpy_s(Unk0, 0x104, Unk1);"
		void	  Initialize(void);									   // Initializes commonDialog/SaveData
		int32_t   Terminate(void);									   // Terminates SaveData and unloads the system module
		FileType* GetFileType(const char* Unk0, uint32_t Unk1);		   // Does Something with FileType/SaveDataSystemUtilityFile.. not sure needs more RE
		uint32_t  Unk00(void* Unk00, uint32_t Unk01);				   // ??? calls sceSaveDataDirNameSearch? so maybe Search?
		void	  Unk01(void);										   // has at least 3 args, just not sure what they are/do
		void	  Unk02(void);										   // Empty Function
		void	  Unk03(void);										   // has at least 1 argument that apears to be a pointer?
		void	  Unk04(void* Unk0, SceSaveDataMountResult ** Unk1);   // ??? Unk0 is a struct/class of some sort, contains a very speciifc string(aka general path to the save "%s/SAVEDATA.DAT" %s is usally savedata0 as only one is normally mounted at once), i do know it handles mount/unmount
		void	  Unk05(void* Unk0);								   // similar to Unk04
		void	  Unk06(void* Unk0, void* Unk1);					   // ^
		void	  Unk07(void);										   // empty function
		bool	  Unk08(void);										   // = 1... pure?
		bool	  Unk09(void);										   // = 1... pure?
		bool	  Unk10(void);										   // = 0... pure?
		void	  Unk11(void);										   // Not sure, does call a function with the "%s/SAVEDATA.DAT" string

		static inline BSOrbisSaveDataSystemUtility* GetSingleton()
		{
			typedef BSOrbisSaveDataSystemUtility*(*__GetSingleton)();
			static Relocation<__GetSingleton> _GetSingleton(0x16855A0);
			return _GetSingleton();
		}

	private:
	};
	static_assert(sizeof(BSOrbisSaveDataSystemUtility) != 0, "class size mismatch");
}