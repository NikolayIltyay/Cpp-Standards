#include "c++17_lambda_capture_this.h"
#include <iostream>

class A
{
public:
	A()
	{
		std::cout << "A()" << std::endl;
	}

	A(const A& a)
	{
		std::cout << "A(const A& a)" << std::endl;
	}

	~A()
	{
		std::cout << "~A()" << std::endl;
	}

	auto getValueCopy() {
		return [*this]{ return value; };
	}

	auto getValueRef() {
		return [this] {return value; };
	}


	int value{ 123 };
};

void Cpp_17_LambdaCaptureThis::example()
{
	A a;

	{
		//getValueCopy call create a copy of 'a' object with life cycle of 'getValByValue' variable
		auto getValByValue = a.getValueCopy();
		auto getValueByRef = a.getValueRef();

		a.value = 777;

		auto v0 = getValByValue();
		auto v1 = getValueByRef();
	}


}