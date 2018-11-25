#pragma once

#include "PlayableSound.h"

#include <Pokitto.h>

// In Pokitto
extern uint8_t soundbuf[];
extern uint16_t soundbufindex;
extern uint8_t* soundbufptr;

class SoundPlayer
{
public:
	static constexpr std::size_t channelCount = 4;

private:
	static constexpr std::size_t bytesPerChannel = (SBUFSIZE / channelCount);

private:
	PlayableSound samples[channelCount];

	Ticker soundTimer;

	// Marked volatile to account for use in interrupt
	volatile std::size_t previousBufferChannel = 0;

private:
	void updateAudioBuffer()
	{
		const std::size_t currentBufferChannel = (soundbufindex / bytesPerChannel);

		if(currentBufferChannel != previousBufferChannel)
		{
			previousBufferChannel = currentBufferChannel;

			const std::size_t baseIndex = (currentBufferChannel * bytesPerChannel);
			for(std::size_t index = 0; index < bytesPerChannel; ++index)
			{
				const unsigned char sample = mixSounds(this->samples);
				soundbuf[baseIndex + index] = sample;
				updateSounds(this->samples);
			}
		}
	}

public:
	SoundPlayer(float updateInterval)
	{
		soundTimer.attach(callback(this, &SoundPlayer::updateAudioBuffer), updateInterval);
	}

	~SoundPlayer()
	{
		soundTimer.detach();
	}

	constexpr std::size_t getChannelCount() const
	{
		return this->channelCount;
	}

	bool playSound(std::size_t channelIndex, const SoundInfo & info)
	{
		return playSound(channelIndex, info, SoundSettings());
	}

	bool playSound(std::size_t channelIndex, const SoundInfo & info, const SoundSettings & settings)
	{
		if(channelIndex >= channelCount)
			return false;

		samples[channelIndex] = PlayableSound(info, settings, SoundPlayState(true));
		return true;
	}
};