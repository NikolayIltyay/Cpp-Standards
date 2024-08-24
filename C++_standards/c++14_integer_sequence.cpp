#include "c++14_integer_sequence.h"
#include <array>
#include <cstddef>
#include <iostream>
#include <tuple>
#include <utility>

//T... ints - parameter pack
template<typename T, T... ints>
void print_sequence(std::integer_sequence<T, ints...> int_seq)
{
	std::cout << "The sequence size=" << int_seq.size() << ": ";
	//fold expression
	((std::cout << ints << " "), ...);
	std::cout << std::endl;
}

template<typename Array, size_t... I>
auto a2t_impl(const Array& a, std::index_sequence<I...>)
{
	//a[I]... - unpackig parameter pack
	return std::make_tuple(a[I]...);
}


template<typename T, size_t N, typename Indices = std::make_index_sequence<N>>
auto a2t(const std::array<T, N>& a)
{
	return a2t_impl(a, Indices{});
}

template<auto... seq>
void testFunc()
{
	((std::cout << seq << " "), ...);
}

//template<typename ...T>
//void testFunc()
//{
//	((std::cout << T << " "), ...);
//
//}



void Cpp_14_IntegerSequence::example()
{
	//auto ptr = testFunc<int, int, int, int>;
	testFunc<1, 2, 3, 4>();

	print_sequence(std::integer_sequence<int, 1, 2, 3, 4, 5, 6>());
	print_sequence(std::make_integer_sequence<int, 20>());
	print_sequence(std::make_index_sequence<10>());
	print_sequence(std::index_sequence_for<int, std::iostream, char, long > ());

	std::array<int, 4> array = { 10, 2, 36, 4568 };
	auto tuple = a2t(array);
}