#include "c++11_type_traits.h"

#include <type_traits>

void Cpp_11_TypeTraits::example()
{
	static_assert(std::is_integral<int>::value);
	static_assert(std::is_same<int, int>::value);
	static_assert(std::is_same<std::conditional<true, int, double>::type, int>::value);

	using testType = std::conditional<sizeof(int) >= sizeof(long), int, long>::type; // defines type depending on condition
	testType a{ 3 };
}