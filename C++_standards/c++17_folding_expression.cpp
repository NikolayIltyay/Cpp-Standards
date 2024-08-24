#include "c++17_folding_expression.h"


template<typename... Args>
bool logicalAdd(Args... args)
{
	return (true && ... && args);
}

template<typename... Args>
auto sum(Args... args)
{
	return(... + args);
}


void Cpp_17_FoldingExpression::example()
{
	auto sumResult = sum(1, 3.4, 45.6f);

	bool b = true;
	bool& br = b;

	auto logicalAddResult = logicalAdd(true, 4, b, br);

	constexpr auto add = [](int x, int y) {
		return x+y;
	};
}