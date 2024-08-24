#include "c++11_decltype.h"
#include "additions.h"

#include <vector>
#include <utility>

namespace
{
	decltype(auto) getNumbers()
	{
		return std::vector<int>();
	}

	int s = 0;

	// decltype(auto) as a return type of getRef() preserve reference of ref variable
	// in case of using just auto we would need to specify & manually
	decltype(auto) getRef()
	{
		int& ref = s;
		return ref;
	}
}




void Cpp_11_Decltype::example()
{
	//auto result = additions::summ(2, 3); //compile error decltype(auto) can't be used before function is defined
	auto result = additions::templateSumm(2, 3); // ok with template function which is defined in header

	auto numbers = getNumbers(); // ok, function definition is in this cpp

	// decltype(auto) as a return type of getRef() preserve reference of ref variable
	int& ref = getRef();
	ref = 3;

	int a = 10;
	auto f1 = [](int& e) ->auto& {return e; };

	auto f2 = [](int& e) {return e; };

	int& ref1 = f1(a);

	ref1 = 5; // a == 5

	//int& ref2 = f2(a);  // compile error. Return type is rvalue int, can't be assigned to reference

	// universal reference can be used for lambda using auto&&
	// we can return reference depending on it is rvl or lvl using std::forward
	// -> decltype(auto) makes a compiler to deduct the exact type of std::forward<decltype(p)>(p)
	auto f3 = [](auto&& p) -> decltype(auto) {
		return std::forward<decltype(p)>(p); 
	};

	auto& res1 = f3(a);
	auto&& res2 = f3(4);

}