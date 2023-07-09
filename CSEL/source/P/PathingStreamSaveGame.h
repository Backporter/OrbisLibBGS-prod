#pragma once

namespace ConsoleRE
{
	class PathingStreamSaveGame /* : public BSPathingStreamWrite */
	{
	public:
		virtual ~PathingStreamSaveGame();
	public:
		void* Unk08;
	};
	static_assert(sizeof(PathingStreamSaveGame) == 0x10);
}