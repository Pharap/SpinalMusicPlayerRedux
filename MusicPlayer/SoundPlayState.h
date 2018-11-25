#pragma once

#include <cstddef>

struct SoundPlayState
{
private:
	bool active = false;
	std::size_t position = 0;

public:
	constexpr SoundPlayState() = default;

	constexpr SoundPlayState(bool active)
		: active(active)
	{
	}

	constexpr SoundPlayState(bool active, std::size_t position)
		: active(active), position(position)
	{
	}

	std::size_t getPosition() const
	{
		return this->position;
	}

	void incrementPosition()
	{
		++this->position;
	}

	void setPosition(std::size_t position)
	{
		this->position = position;
	}

	bool isActive() const
	{
		return this->active;
	}

	void enable()
	{
		this->active = true;
	}

	void disable()
	{
		this->active = false;
	}
};