#pragma once

#include <stdint.h>

namespace ConsoleRE
{
	class GTexture
	{
	public:
		class ChangeHandler
		{
		public:
			enum EventType
			{
				Event_DataChange,
				Event_DataLost,
				Event_RendererReleased,
			};
		public:
			virtual ~ChangeHandler() = default;
			
			// add
			virtual void Unk_02(void*, EventType);
			virtual bool Unk_03(void*);
		public:
		};
	public:
		GTexture();
		virtual ~GTexture();
	public:
		virtual void Unk_02() = 0;
		virtual void Unk_03() = 0;
		virtual void Unk_04() = 0;
		virtual void Unk_05() = 0;
		virtual void Unk_06() = 0;
		virtual void Unk_07() = 0;
		virtual void Unk_08() = 0;
		virtual void Unk_09() = 0;
		virtual void Unk_10() = 0;
		virtual void Unk_11() = 0;
		virtual void Unk_12() = 0;
	public:
		volatile int32_t refCount;
	};
}