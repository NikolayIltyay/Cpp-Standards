#include "c++11_variadic_templates.h"
#include <iostream>
#include <numeric>

template <typename... T>
struct arity {
	constexpr static int value = sizeof...(T);
};

template <typename First, typename... Args>
auto sum(const First first, const Args... args) -> decltype(first) {
	const auto values = { first, args... };
	return std::accumulate(values.begin(), values.end(), First{ 0 });
}

void Cpp_11_VariadicTemplates::example()
{
	static_assert(arity<>::value == 0);
	static_assert(arity<char, short, int>::value == 3);

	std::cout << sum(1, 2, 3, 4, 5) << std::endl;
	std::cout << sum(1, 2, 3) << std::endl;
	std::cout << sum(1.5, 2.0, 3.7) << std::endl;
}