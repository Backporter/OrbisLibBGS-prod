#pragma once

namespace ConsoleRE
{
	namespace BSScript
	{
		class IFreezeQuery
		{
		public:
			virtual ~IFreezeQuery();
			
			// add
			virtual void Unk_02(void) = 0;
		};
	}
}