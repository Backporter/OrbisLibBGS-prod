#pragma once

namespace ConsoleRE
{
	namespace BSScript
	{
		struct IObjectHandlePolicy
		{
		public:
			virtual ~IObjectHandlePolicy();
			
			// add (IObjectHandlePolicy)
			virtual bool		HandleIsType(uint32_t a_typeID, uint64_t a_handle) = 0;
			virtual bool		IsHandleObjectAvailable(uint64_t a_handle) = 0;
			virtual uint64_t	EmptyHandle() = 0;
			virtual uint64_t	GetHandleForObject(uint32_t a_typeID, const void* a_srcData) = 0;
			virtual bool		HasParent(uint64_t a_handle) = 0;
			virtual uint64_t	GetParentHandle(uint64_t a_handle) = 0;
			virtual uint64_t	GetHandleScriptsMovedFrom(uint64_t a_handle) = 0;
			virtual void*		GetObjectForHandle(uint32_t a_typeID, uint64_t a_handle) = 0;
			virtual void		PersistHandle(uint64_t a_handle) = 0;
			virtual void		ReleaseHandle(uint64_t a_handle) = 0;
			virtual void		ConvertHandleToString(uint64_t a_handle, BSFixedString& a_strOut) = 0;
		public:
		};
	}
}