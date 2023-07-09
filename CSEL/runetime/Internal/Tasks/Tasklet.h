#pragma once

#include <stdint.h>

namespace Task
{
	enum task_type : uint32_t
	{
		Invalid	= static_cast<uint32_t>(-1),
		General = 0,
		UI,
		Sound,
		Control,
		World,
		Geometry,
		Texture,
	};

	class Tasklet
	{
	public:
		Tasklet(const char* a_taskname, uint32_t a_taskversion, uint32_t a_tasktype) : m_taskname(a_taskname), m_taskversion(a_taskversion), m_tasktype(a_tasktype) 
		{}

		// ...
		virtual ~Tasklet() = default;
		
		// add
		virtual bool Invoke() = 0;

		// 
		inline const char* GetName() { return m_taskname; }
		inline const uint32_t GetVersion() { return m_taskversion; }
		inline const uint32_t GetTaskType() { return m_tasktype; }
	protected:
		const char* m_taskname;
		uint32_t	m_taskversion;
		uint32_t	m_tasktype;
	};
}