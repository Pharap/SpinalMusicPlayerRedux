#pragma once

#include <cstddef>

struct SoundRepeatInfo
{
private:
	bool valid = false;
	std::size_t rangeStart = 0;
	std::size_t rangeLength = 0;

public:
	constexpr SoundRepeatInfo() = default;

	constexpr SoundRepeatInfo(std::size_t rangeStart, std::size_t rangeLength)
		: valid(true), rangeStart(rangeStart), rangeLength(rangeLength)
	{
	}

	/// Whether this represents a valid range or not
	constexpr bool isValid() const
	{
		return this->valid;
	}

	/// Gets the size of the range
	constexpr std::size_t getRangeLength() const
	{
		return this->rangeLength;
	}

	/// The first index of the the range
	constexpr std::size_t getRangeStart() const
	{
		return this->rangeStart;
	}

	// The 'past-the-end' index of the range
	constexpr std::size_t getRangeEnd() const
	{
		return (this->rangeStart + this->rangeLength);
	}

	constexpr bool isIndexInRange(std::size_t index) const
	{
		return ((index >= this->getRangeStart()) && (index < this->getRangeEnd()));
	}
};