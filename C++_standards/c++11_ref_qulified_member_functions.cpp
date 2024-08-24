#include "c++11_ref_qulified_member_functions.h"
#include <vector>


namespace
{
	class A
	{
	public:
		decltype(auto) getNumbers()&
		{
			return _numbers;
		}

		decltype(auto) getNumbers() const&
		{
			return _numbers;
		}

		decltype(auto) getNumbers()&&
		{
			return std::move(_numbers);
		}

	private:
		std::vector<int> _numbers;
	};
}


A getObject()
{
	return A();
}


void Cpp_11_RefQualifiedMemberFunctions::example()
{
	const char* msg1 = "\nHello,\n\tworld!\n";
	const char* msg2 = R"(

Hello,

	world!

)";

	A a;
	auto numbers0 = a.getNumbers();
	
	const A ac;
	auto numbers1 = ac.getNumbers();

	auto numbers2 = getObject().getNumbers();
}