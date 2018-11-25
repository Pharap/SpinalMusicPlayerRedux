#include <Pokitto.h>

#include "MusicPlayer.h"
#include "SoundData.h"

int main ()
{
	using Pokitto::Core;
	using Pokitto::Sound;
	using Pokitto::Display;

	Core::begin();
	Core::setFrameRate(255);

	// Init audio stream.
	pokPlayStream(); // activate stream
	Sound::ampEnable(true);
	Sound::playMusicStream();

	// check and update the sound buffer as often as we can
	//soundPlay.attach(&updateAudioBuffer, 0.0001);
	//musicTimer.attach(&update_tune, 0.055);

	SoundPlayer player { 0.0001 };

	for(std::size_t index = 0; index < player.getChannelCount(); ++index)
		player.playSound(index, sounds[index]);

	Display::color = 1;

	while (Core::isRunning())
	{
		if (Core::update())
		{
			
		}
	}
}


