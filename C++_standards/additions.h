#pragma once
#include <iostream>
#include <mutex>
#include <sstream>

namespace additions
{
	decltype(auto) summ(int a, int b);

	template<typename T>
	decltype(auto) templateSumm(T a, T b)
	{
		return a + b;
	}

	class EmptyClassWithAllConstructors
	{
	public:
		EmptyClassWithAllConstructors();

		EmptyClassWithAllConstructors(const EmptyClassWithAllConstructors& other);

		EmptyClassWithAllConstructors(EmptyClassWithAllConstructors&& other);

		~EmptyClassWithAllConstructors();
	private:
		int a;
	};

    class ThreadSafeCout {
    public:
        // Function to print a single message
        template<typename T>
        static void print(const T& message) {
            std::lock_guard<std::mutex> guard(mutex_);
            std::cout << message;
        }

        // Function to print multiple messages with a single lock
        template<typename... Args>
        static void print(const Args&... args) {
            std::lock_guard<std::mutex> guard(mutex_);
            (std::cout << ... << args);
        }


    private:
        static inline std::mutex mutex_;
    };


}

