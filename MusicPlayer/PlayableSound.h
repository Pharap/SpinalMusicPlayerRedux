#pragma once

#include <cstddef>
#include <cstdint>

#include "SoundInfo.h"
#include "SoundSettings.h"
#include "SoundPlayState.h"

struct PlayableSound
{
private:
	SoundInfo info;
	SoundSettings settings;
	SoundPlayState playState;

public:
	constexpr PlayableSound() = default;

	constexpr PlayableSound(const SoundInfo & info, const SoundSettings & settings, const SoundPlayState & playState)
		: info(info), settings(settings), playState(playState)
	{
	}

	constexpr const SoundInfo & getInfo() const
	{
		return this->info;
	}

	constexpr const SoundRepeatInfo & getRepeatInfo() const
	{
		return this->info.getRepeatInfo();
	}

	constexpr const SoundSettings & getSettings() const
	{
		return this->settings;
	}

	SoundPlayState & getPlayState()
	{
		return this->playState;
	}

	constexpr const SoundPlayState & getPlayState() const
	{
		return this->playState;
	}

	bool isAtEnd() const
	{
		return (this->playState.getPosition() >= this->info.getSize());
	}
};

template< std::size_t size >
unsigned char mixSounds(const PlayableSound (&samples)[size])
{
	unsigned int sum = 0;
	unsigned int product = 1;

	for(std::size_t index = 0; index < size; ++index)
	{
		// Copy the sample in an attempt to avoid race conditions
		PlayableSound sample = samples[index];

		// Create a reference to the playState to simplify the code
		const SoundPlayState & playState = sample.getPlayState();
		
		if(!playState.isActive())
			continue;

		// Create a reference to the soundSettings to simplify the code
		const SoundSettings & settings = sample.getSettings();

		// Create a reference to the repeatInfo to simplify the code
		const SoundRepeatInfo & repeatInfo = sample.getInfo().getRepeatInfo();

		const std::size_t currentSoundIndex = ((playState.getPosition() * static_cast<std::size_t>(settings.getSpeed())) >> 8);
		unsigned char data = static_cast<unsigned char>(static_cast<unsigned int>(sample.getInfo()[currentSoundIndex] * settings.getVolume()) >> 8);
		
		// Calculating the sum and product during the loop is more efficient
		sum += data;
		product *= data;
	 }

	return static_cast<unsigned char>(sum - (product >> 8));
}

template< std::size_t size >
void updateSounds(PlayableSound (&samples)[size])
{
	for(std::size_t index = 0; index < size; ++index)
	{
		// Copy the sample in an attempt to avoid race conditions
		PlayableSound sample = samples[index];

		// Create a reference to the playState to simplify the code
		SoundPlayState & playState = sample.getPlayState();

		// Create a reference to the repeatInfo to simplify the code
		const SoundRepeatInfo & repeatInfo = sample.getInfo().getRepeatInfo();

		playState.incrementPosition();

		if(repeatInfo.isValid())
		{
			if(playState.getPosition() >= repeatInfo.getRangeEnd())
			{
				playState.setPosition(repeatInfo.getRangeStart());
			}
		}
		else 
		{
			if(playState.getPosition() >= sample.getInfo().getSize())
			{
				playState.setPosition(0);
				playState.disable();
			}
		}

		// Copy the sample back to the samples array
		samples[index] = sample;
	 }
}