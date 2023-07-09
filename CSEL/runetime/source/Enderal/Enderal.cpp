#include "../Enderal/Enderal.h"

namespace Runetime
{
	namespace Enderal
	{
		bool IsEnderal = false;

		void Init()
		{
			IsEnderal = xUtilty::FileSystem::PathExists(xUtilty::FileSystem::Full, "/app0/data/Enderal - Forgotten Stories.esm", false);
		}
	}
}