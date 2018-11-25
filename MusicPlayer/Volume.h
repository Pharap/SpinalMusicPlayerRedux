#pragma once

#include <cstdint>

struct Volume
{
public:
	using ValueType = std::uint_least8_t;

private:
	static constexpr ValueType limitValue = 128;

public:
	static constexpr ValueType minimum = 0;
	static constexpr ValueType maximum = (static_cast<ValueType>(~0) % limitValue);

private:
	ValueType value = 0;

public:
	constexpr Volume() = default;

	constexpr Volume(ValueType value)
		: value(value % limitValue)
	{
	}

	operator ValueType()
	{
		return this->value;
	}
};