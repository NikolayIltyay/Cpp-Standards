#include "c++11_user_defined_literals.h"
#include <cmath>
#include <string>

long long operator "" _celsius(unsigned long long tempCelsius) {
	return std::llround(tempCelsius * 1.8 + 32);
}

int operator "" _int(const char* str, std::size_t) {
	return std::stoi(str);
}

void Cpp_11_UserDefinedLiterals::example()
{
	auto temp  = 24_celsius;
	auto num = "123"_int;
}