#pragma once

#include "../B/BSFixedString.h"
#include "../N/NiObject.h"

namespace ConsoleRE
{
	class NiExtraData : public NiObject
	{
	public:
		~NiExtraData() override;

		const NiRTTI* GetRTTI() const override;
		void          LoadBinary(NiStream& a_stream) override;
		void          LinkObject(NiStream& a_stream) override;
		bool          RegisterStreamables(NiStream& a_stream) override;
		void          SaveBinary(NiStream& a_stream) override;
		bool          IsEqual(NiObject* a_object) override;
		
		// add
		virtual bool IsStreamable() const;
		virtual bool IsCloneable() const;

		// ...
		static NiExtraData* Create(size_t a_size, uintptr_t a_vtbl)
		{
			auto ptr = malloc(a_size);
			memset(ptr, 0, a_size);
			(*reinterpret_cast<uintptr_t*>(ptr)) = a_vtbl;
			return static_cast<NiExtraData*>(ptr);
		}

		template <typename T>
		static T* Create(uintptr_t);

		const BSFixedString& GetName() const { return name; }
		void SetName(const BSFixedString& a_name) { name = a_name; }
	public:
		BSFixedString name;
	};
	static_assert(sizeof(NiExtraData) == 0x18);


	template <typename T>
	T* NiExtraData::Create(uintptr_t a_vtbl)
	{
		return static_cast<T*>(Create(sizeof(T), a_vtbl));
	}
}		