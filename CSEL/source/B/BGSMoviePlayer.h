#pragma once

#include "../B/BSTEvent.h"
#include "../M/MoviePlayer.h"

namespace ConsoleRE
{
	class InputEvent;
	struct BSMusicEvent;

	class BGSMoviePlayer : public MoviePlayer, public BSTEventSink<InputEvent*>, public BSTEventSource<BSMusicEvent>
	{
	public:
		~BGSMoviePlayer() override;
	public:
	};
}