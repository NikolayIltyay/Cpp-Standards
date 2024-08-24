#include "c++11_constexpr.h"
#include <string>


template<typename T>
constexpr T&& greater(T&& a, T&& b)
{
	return a > b ? std::forward<T>(a) : std::forward<T>(b);
}

template<typename T>
constexpr T getMax(T&& a, T&& b)
{
	return a > b ? a : b;
}

class C
{
public:
	constexpr C(int value) : _value(value) {}

	constexpr int getValue() const
	{
		return _value;
	}

private:
	int _value;
};


void Cpp_11_Constexpr::example()
{
	constexpr int r = 5;

	auto result0 = greater<>(2, 4);

	constexpr int a = 5;
	constexpr int b = 6;

	auto result1 = greater<>(a, b);

	auto result2 = getMax<>(2, 3);

	constexpr C c(10);
	static_assert(c.getValue() == 10, "Value should be 10");

}