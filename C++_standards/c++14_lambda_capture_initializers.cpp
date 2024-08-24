#include "c++14_lambda_capture_initializers.h"
#include <memory>
#include <iostream>

namespace
{
	class A
	{
	public:
		A() :
			_a(0)
		{
			std::cout << "A()" << std::endl;
		}

		A(const A& a):
			_a(a._a)
		{
			std::cout << "A(const A&)" << std::endl;
		}

		A(A&& a) :
			_a(a._a)
		{
			std::cout << "A(A&&)" << std::endl;
		}

		~A()
		{
			std::cout << "~A()" << std::endl;
		}

		int getA()
		{
			return _a;
		}


	private:
		int _a{ 0 };
	};
}


void Cpp_14_LambdaCaptureInitializers::example()
{

	auto p = std::make_unique<A>();
	// creating NEW p variable from rvalue
	auto task = [p = std::move(p)]{ return p->getA(); };
	auto n = task();

	{
		A a;
		// adding mutable because a_capture would be const by default
		// a_capture is created through copy constructor in this example
		// a_capture gets destroyed when task2 lambda gets out of the scope
		auto task2 = [a_capture = a]() mutable { return a_capture.getA(); };
		auto n = task2();
	}
}