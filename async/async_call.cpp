#include <iostream>
#include <chrono>
#include <future>
#include <thread>

// Ref. arg.
void work1(int & a) {
	std::cout << "work1(int &), a = " << a << "\n";
}

// Normal arg.
void work2(int a) {
	std::cout << "work2(int), a = " << a << "\n";
}

class FunctionalWork {
public:
	FunctionalWork(int a_)
		: a{a_} {}
	void operator()(int b) {
		std::cout << "FunctionalWork, a = " << a << ", b = " << b << '\n';
	}
private:
	int a;
};

class Work {
public:
	Work(int a_)
		: a{a_} {}
	void makeWork(int b) {
		std::cout << "Work, a = " << a << ", b = " << b << '\n';
	}
private:
	int a;
};

int main() {
	auto timeSep = [] { std::this_thread::sleep_for(std::chrono::milliseconds(20));};
	auto funWork = FunctionalWork(21);
	auto work = Work(42);
	int val = 42;

	auto ftr1 = std::async(std::launch::deferred, work1, std::ref(val)); // Run in main() thread...
	timeSep();
	auto ftr2 = std::async(std::launch::async, work2, val); // Run in other thread...
	timeSep();
	auto ftr3 = std::async(std::launch::async, [](int a) {  // Lambda example...
		std::cout << "lambda: a = " << a << '\n';
	}, val);
	timeSep();
	auto ftr4 = std::async(std::launch::async, funWork, 2); // Functional object...
	timeSep();
	auto ftr5 = std::async(std::launch::async, &Work::makeWork, &work, 1); // Object with custom method...
	timeSep();

	for (auto ft: { &ftr1, &ftr2, &ftr3, &ftr4, &ftr5 }) {
		ft->get();
	}
}
