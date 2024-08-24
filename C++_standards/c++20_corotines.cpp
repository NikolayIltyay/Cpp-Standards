#include "c++20_corotines.h"
#include <iostream>
#include <thread>
#include <chrono>
#include <coroutine>

class CoroTask {
public:
	// helper type for state and customization:
	struct promise_type {
		auto get_return_object() { // create the coroutine handle
			return std::coroutine_handle<promise_type>::from_promise(*this);
		}
		auto initial_suspend() { // start immediately?
			return std::suspend_always{}; // - suspend immediately
		}
		auto final_suspend() noexcept { // clean-ups / postprocessing
			return std::suspend_always{}; // - suspend at the end
		}
		void unhandled_exception() { // deal with exceptions
			std::terminate(); // - terminate the program
		}
		void return_void() { // deal with the end or with return;
		}
	};
private:
	// internal handle to allocated state:
	std::coroutine_handle<promise_type> coroHdl;
public:
	// constructor to initialize the coroutine:
	CoroTask(auto h) : coroHdl{ h } {
		std::cout << "- CoroTask: construct\n";
	}
	~CoroTask() {
		std::cout << "- CoroTask: destruct\n";
		if (coroHdl) {
			coroHdl.destroy();
		}
	}
	// don’t copy or move:
	CoroTask(const CoroTask&) = delete;
	CoroTask& operator=(const CoroTask&) = delete;
	// API to resume the coroutine
	// - returns whether there is still something to process
	bool resume() const {
		std::cout << "- CoroTask: resume()\n";
		if (!coroHdl) {
			return false; // nothing (more) to process
		}
		coroHdl.resume(); // RESUME (just coroHdl() is also possible)
		return !coroHdl.done();
	}
};

CoroTask sayHello()
{
	std::cout << "Hello" << '\n';
	co_await std::suspend_always(); // SUSPEND
	std::cout << "World" << '\n';
	co_await std::suspend_always(); // SUSPEND
	std::cout << "!" << '\n';
}


///////////////////////////

class IntGen {
public:
	// customization points:
	struct promise_type {
		int currentValue; // last value from co_yield
		auto yield_value(int value) { // reaction on co_yield
			currentValue = value; // - store value locally
			return std::suspend_always{}; // - suspend coroutine
		}
		// the usual callbacks:
		auto get_return_object() {
			return std::coroutine_handle<promise_type>::from_promise(*this);
		}
		auto initial_suspend() { return std::suspend_always{}; }
		auto final_suspend() noexcept { return std::suspend_always{}; }
		void unhandled_exception() { std::terminate(); }
		void return_void() { }
	};
private:
	// internal coroutine handle:
	std::coroutine_handle<promise_type> coroHdl;
public:
	// constructors and destructor:
	IntGen(auto h) : coroHdl{ h } {
	}
	~IntGen() {
		if (coroHdl) {
			coroHdl.destroy();
		}
	}
	// no copying, but moving is supported:
	IntGen(IntGen const&) = delete;
	IntGen(IntGen&& rhs)
		: coroHdl(rhs.coroHdl) {
		rhs.coroHdl = nullptr;
	}
	IntGen& operator=(IntGen const&) = delete;
	// API:
	// - resume() to resume the coroutine
	// - getValue() to get the last value from co_yield
	bool resume() const {
		if (!coroHdl) {
			return false; // nothing (more) to process
		}
		coroHdl.resume(); // RESUME
		return !coroHdl.done();
	}
	int getValue() const {
		return coroHdl.promise().currentValue;
	}
};


template <typename T>
IntGen loopOver(const T& coll)
{
	// coroutine that iterates over the elements of a collection:
	for (int elem : coll) {
		std::cout << "- yield " << elem << '\n';
		co_yield elem; // calls yield_value(elem) on promise
		std::cout << "- resume\n";
	}
}



////////////////////////////////////////////////////

class StringTask {
public:
	// customization points:
	struct promise_type {
		std::string result; // value from co_return
		void return_value(const auto& value) { // reaction on co_return
			result = value; // - store value locally
		}
		// the usual callbacks:
		auto get_return_object() {
			return std::coroutine_handle<promise_type>::from_promise(*this);
		}
		auto initial_suspend() { return std::suspend_always{}; }
		auto final_suspend() noexcept { return std::suspend_always{}; }
		void unhandled_exception() { std::terminate(); }
	};
private:
	// internal coroutine handle:
	std::coroutine_handle<promise_type> coroHdl;
public:
		// constructors and destructor:
		StringTask(auto h) : coroHdl{ h } {
	}
	~StringTask() {
		if (coroHdl) {
			coroHdl.destroy();
		}
	}
	// no copying or moving is supported:
	StringTask(StringTask const&) = delete;
	StringTask& operator=(StringTask const&) = delete;
	// API:
	// - resume() to resume the coroutine
	// - getValue() to get the last value from co_yield
	bool resume() const {
		if (!coroHdl) {
			return false; // nothing (more) to process
		}
		coroHdl.resume(); // RESUME
		return !coroHdl.done();
	}
	std::string getResult() const {
		return coroHdl.promise().result;
	}
};


StringTask computeInSteps()
{
	std::string ret;
	ret += "Hello";
	co_await std::suspend_always(); // SUSPEND
	ret += " World";
	co_await std::suspend_always(); // SUSPEND
	ret += "!";
	co_return ret;
}

void Cpp_20_Coroutines::example()
{
	using namespace std::literals;
	// start coroutine:
	CoroTask sayHelloTask = sayHello();
	std::cout << "coroutine sayHello() started\n";
	// loop to resume the coroutine until it is done:
	while (sayHelloTask.resume()) { // resume
		std::this_thread::sleep_for(500ms);
	}

	/////////////////////

	using namespace std::literals;
	// define generator that yields the elements of a collection:
	std::vector<int> coll{ 0, 8, 15, 33, 42, 77 };
	IntGen gen = loopOver(coll);
	// loop to resume the coroutine until there is no more value:
	std::cout << "start loop:\n";
	while (gen.resume()) { // resume until we have the next value
		std::cout << "main(): value: " << gen.getValue() << '\n';
		std::this_thread::sleep_for(1s);
	}


	////////////////////////

	using namespace std::literals;
	// start coroutine:
	StringTask task = computeInSteps();
	// loop to resume the coroutine until it is done:
	while (task.resume()) { // RESUME
		std::this_thread::sleep_for(500ms);
	}
	// print return value of coroutine:
	std::cout << "result: " << task.getResult() << '\n';
}
