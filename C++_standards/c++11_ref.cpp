#include "c++11_ref.h"
#include <functional>
#include <iostream>

void Cpp_11_Ref::example()
{
	auto val = 99;
	auto _ref = std::ref(val);

	auto _cref = std::cref(val);
	//_cref++; compilation error

	std::vector<std::reference_wrapper<int>>vec;
	vec.push_back(_ref);
	std::cout << val << std::endl;
	std::cout << vec[0] << std::endl;
	std::cout << _cref;
}