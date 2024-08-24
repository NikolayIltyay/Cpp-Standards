#include "c++11_forwarding_references.h"
#include <utility>
#include <iostream>

namespace{
	class A
	{
	public:
		A() {}

		A(const A& other)
		{
			std::cout << "A copy constructor" << std::endl;
		}

		A(A&& other)
		{
			std::cout << "A move constructor" << std::endl;
		}
	};
}


void func(auto&& p)
{
	A a(std::forward<decltype(p)>(p));
}

A getA()
{
	return A();
}

void Cpp_11_ForwardingReferences::example()
{
	A lval;
	func(lval);
	func(getA());
}