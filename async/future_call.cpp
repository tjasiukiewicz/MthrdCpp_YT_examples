#include <iostream>
#include <iomanip>
#include <thread>
#include <chrono>
#include <future>

void calculate() {
	std::cout << "I'm calculate().\n";
	std::this_thread::sleep_for(std::chrono::milliseconds(100));
}

std::future<void> makeAsyncCalculate() {
	return std::async(std::launch::async, calculate);
}

std::future<void> placeAsyncCalculate(std::future<void> && ftr) {
	ftr = std::async(std::launch::async, calculate);
	return std::move(ftr);
}

int main() {
	std::cout << ">Example 1\n";
	std::future<void> ftr1 = std::async(std::launch::deferred, calculate);
	std::cout << std::boolalpha << "ftr1 valid before call (and .get())? " << ftr1.valid() << '\n';
	ftr1.get();
	std::cout << std::boolalpha << "ftr1 valid after call (and .get())? " << ftr1.valid() << '\n';

	// "Reuse" std::future
	if (ftr1.valid() == false) {
		std::cout << ">Example 2\n";
		ftr1 = std::async(std::launch::deferred, calculate);
		std::cout << "Reuse std::future.., ftr1.valid() == false\n";
		ftr1.get();
		std::cout << std::boolalpha << "ftr1 valid after call (and .get())? " << ftr1.valid() << '\n';
	}

	std::cout << ">Example 3\n";
	std::future<void> ftr2 = makeAsyncCalculate();
	ftr2.get();

	std::cout << ">Example 4\n";
	std::future<void> ftr3; // Empty future
	std::cout << std::boolalpha << "Empty ftr3 valid before call? " << ftr3.valid() << '\n';
	std::future<void> ftr4 = placeAsyncCalculate(std::move(ftr3));
	std::cout << std::boolalpha << "ftr3 valid after call? " << ftr3.valid() << '\n';
	std::cout << std::boolalpha << "ftr4 valid after call? " << ftr4.valid() << '\n';
	ftr4.get();
	std::cout << std::boolalpha << "ftr4 valid after call (and .get())? " << ftr4.valid() << '\n';

}
