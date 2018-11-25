#pragma once

#include <cstdint>

struct PlaySpeed
{
public:
	using ValueType = std::uint_least16_t;

private:
	static constexpr ValueType limitValue = 257;

public:
	static constexpr ValueType minimum = 0;
	static constexpr ValueType maximum = (static_cast<ValueType>(~0) % limitValue);

private:
	ValueType value = 0;

public:
	constexpr PlaySpeed() = default;

	constexpr PlaySpeed(ValueType value)
		: value(value % limitValue)
	{
	}

	operator ValueType()
	{
		return this->value;
	}
};