#pragma once

#include <cstddef>
#include <cstdint>

#include "SoundRepeatInfo.h"

struct SoundInfo
{
private:
	const unsigned char * data = nullptr;
	std::size_t size = 0;
	std::uint_least32_t sampleRate = 0;

	SoundRepeatInfo repeatInfo = SoundRepeatInfo();

public:
	constexpr SoundInfo() = default;

	template< std::size_t size >
	constexpr SoundInfo(const unsigned char (&data)[size], std::uint_least32_t sampleRate)
		: data(data), size(size), sampleRate(sampleRate)
	{
	}

	template< std::size_t size >
	constexpr SoundInfo(const unsigned char (&data)[size], std::uint_least32_t sampleRate, bool repeatAll)
		: data(data), size(size), sampleRate(sampleRate), repeatInfo(repeatAll ? SoundRepeatInfo(0, size) : SoundRepeatInfo())
	{
	}

	template< std::size_t size >
	constexpr SoundInfo(const unsigned char (&data)[size], std::uint_least32_t sampleRate, const SoundRepeatInfo & repeatInfo)
		: data(data), size(size), sampleRate(sampleRate), repeatInfo(repeatInfo)
	{
	}

	const unsigned char * getData() const
	{
		return this->data;
	}

	constexpr std::size_t getSize() const
	{
		return this->size;
	}

	constexpr std::uint_least32_t getSampleRate() const
	{
		return this->sampleRate;
	}

	constexpr SoundRepeatInfo getRepeatInfo() const
	{
		return this->repeatInfo;
	}
	
	constexpr bool isRepeatable() const
	{
		return this->repeatInfo.isValid();
	}

	constexpr const unsigned char & operator[](std::size_t index) const
	{
		return this->data[index];
	}
};