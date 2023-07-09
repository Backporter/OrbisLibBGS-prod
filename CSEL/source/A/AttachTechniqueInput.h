#pragma once

#include <stdint.h>

namespace ConsoleRE
{
	namespace BSAttachTechniques
	{
		struct AttachTechniqueInput
		{
		public:
			virtual ~AttachTechniqueInput();

			// add
			virtual void Unk_01(void);
		public:
			void*			unk08;
			void*			unk10;
			uint32_t		unk18;
			uint32_t		unk1C;
		};
		static_assert(sizeof(AttachTechniqueInput) == 0x20);
	}
}