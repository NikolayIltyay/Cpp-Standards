#include "c++11_static_assert.h"
#include <type_traits>
#include <vector>

template <typename T>
void processNumber(T number) {
    static_assert(std::is_integral<T>::value, "T must be an integral type");
    // Function implementation
}

template <typename T>
struct Container {
    static_assert(std::is_default_constructible<T>::value, "T must be default constructible");
    // Implementation
};

class A
{
public:
    A(int a)
    {

    }
};



void Cpp_11_StaticAssert::example()
{
    processNumber<>(2);
    //processNumber<>(2.0); //compilation error

    Container<std::vector<int>> cont;
    //Container<A> cont; //compilation error

    // checking data type size
    static_assert(sizeof(long) == 4, "Expected long to be 4 bytes on this platform");
    //static_assert(sizeof(long) == 8, "Expected long to be 4 bytes on this platform");  //compilation error
}