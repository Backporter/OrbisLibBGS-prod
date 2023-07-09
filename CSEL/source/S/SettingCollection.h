#pragma once

namespace ConsoleRE
{
	template <typename T>
	class SettingCollection
	{
	public:
		virtual ~SettingCollection();
		
		// add
		virtual void InsertSetting(T* a_setting) = 0;
		virtual void RemoveSetting(T* a_setting) = 0;
		virtual bool WriteSetting(T* a_setting) = 0;
		virtual bool ReadSetting(T* a_setting) = 0;
		virtual bool OpenHandle(bool a_create);
		virtual bool CloseHandle();
		virtual void Unk_07(void);
		virtual void Unk_08(void);
		virtual void Unk_09(void);
	public:
		uint64_t unk08;
		uint64_t unk010;
		uint64_t unk018;
		uint64_t unk020;
		uint64_t unk028;
		uint64_t unk030;
		uint64_t unk038;
		uint64_t unk040;
		uint64_t unk048;
		uint64_t unk050;
		uint64_t unk058;
		uint64_t unk060;
		uint64_t unk068;
		uint64_t unk070;
		uint64_t unk078;
		uint64_t unk080;
		uint64_t unk088;
		uint64_t unk090;
		uint64_t unk098;
		uint64_t unk0A0;
		uint64_t unk0A8;
		uint64_t unk0B0;
		uint64_t unk0B8;
		uint64_t unk0C0;
		uint64_t unk0C8;
		uint64_t unk0D0;
		uint64_t unk0D8;
		uint64_t unk0E0;
		uint64_t unk0E8;
		uint64_t unk0F0;
		uint64_t unk0F8;
		uint64_t unk100;
		uint64_t unk108;
		void*	 handle;
	};
	static_assert(offsetof(SettingCollection<void*>, handle) == 0x110);
	static_assert(sizeof(SettingCollection<void*>) == 0x118);
}