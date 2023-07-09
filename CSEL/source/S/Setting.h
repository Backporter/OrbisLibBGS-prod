#pragma once
#include <stdint.h>

namespace ConsoleRE
{
	class Setting
	{
	public:
		enum Type
		{
			Unkown,
			Bool,
			Float,
			Int32,
			Unkown2,
			String,
			UInt32,
		};

		union Data
		{
			bool			b;
			int32_t			i;
			uint32_t		ui;
			float			f;
			const char*		s;
		};
	public:
		virtual ~Setting();

		// add
		virtual bool Unk_02()
		{
			return false;
		}

		// Get
		bool IsManaged() const 
		{ 
			return m_name && m_name[0] == 'S'; 
		}
		
		uint32_t		GetType()
		{
			if (!m_name)
				return Unkown;

			switch (m_name[0])
			{
			case 'b':
				return Bool;
				break;
			case 'f':
				return Float;
				break;
			case 'i':
				return Int32;
				break;
			case 'r':
				return Unkown2;
			case 'S':
				return String;
				break;
			case 's':
				return String;
				break;
			case 'u':
				return UInt32;
				break;
			default:
				return Unkown;
			}
		}
		
		const char*	GetName() const 
		{ 
			return m_name ? m_name : ""; 
		}
		
		bool GetBool() const 
		{ 
			return m_data.b; 
		}
		
		int32_t	GetInt32() const 
		{ 
			return m_data.i; 
		}
		
		uint32_t GetUInt32() const 
		{ 
			return m_data.ui; 
		}
		
		float GetFloat() const 
		{ 
			return m_data.f; 
		}
		
		const char* GetString() const 
		{ 
			return m_data.s; 
		}

		void SetName(char* str) 
		{ 
			m_name = str; 
		}
		
		void SetBool(bool b) 
		{ 
			m_data.b = b; 
		}

		void SetInt32(int32_t i) 
		{ 
			m_data.i = i; 
		}

		void SetUInt32(uint32_t ui) 
		{ 
			m_data.ui = ui; 
		}
		
		void SetFloat(float f) 
		{ 
			m_data.f = f; 
		}
		
		void SetString(const char* str) 
		{ 
			m_data.s = str; 
		}
	public:
		Data	 m_data;
		char*	 m_name;
	};
}