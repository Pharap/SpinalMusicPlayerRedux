#pragma once

#include <cstdint>

#include "Volume.h"
#include "PlaySpeed.h"

struct SoundSettings
{
private:
	Volume volume = Volume::maximum;
	PlaySpeed speed = PlaySpeed::maximum;

public:
	SoundSettings() = default;

	SoundSettings(Volume volume, PlaySpeed speed)
		: volume(volume), speed(speed)
	{
	}

	constexpr Volume getVolume() const
	{
		return this->volume;
	}

	constexpr PlaySpeed getSpeed() const
	{
		return this->speed;
	}
};