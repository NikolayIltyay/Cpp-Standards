#include "c++17_template_argument_deduction.h"
#include <iterator>
#include <vector>

template <typename T>
struct container {
	container(T t) {}

	template <typename Iter>
	container(Iter beg, Iter end) {}
};

// deduction guide
template <typename Iter>
container(Iter b, Iter e)->container<typename std::iterator_traits<Iter>::value_type>;

void Cpp_17_TemplateArgumentDeduction::example()
{

	container a{ 7 }; // OK: deduces container<int>

	std::vector<double> v{ 1.0, 2.0, 3.0 };
	auto b = container{ v.begin(), v.end() }; // OK: deduces container<double>

	//container c{ 5, 6 }; // ERROR: std::iterator_traits<int>::value_type is not a type
}