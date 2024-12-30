#include <iostream>
#include <thread>
#include <chrono>
#include <future>

void calculateA(std::shared_future<void> ftr) {
	ftr.get();
	std::cout << "I'm calculateA().\n";
}

void calculateB(std::shared_future<void> ftr) {
	ftr.get();
	std::cout << "I'm calculateB().\n";
}

int main() {
	std::shared_future<void> sftr = std::async(std::launch::deferred, [] {
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
		std::cout << "Lambda in main()\n";
	});

	auto ftr1 = std::async(std::launch::async, calculateA, sftr);
	auto ftr2 = std::async(std::launch::async, calculateB, sftr);

	std::this_thread::sleep_for(std::chrono::milliseconds(500));

	std::cout << "In main()\n";

	// Best practices... 
	ftr1.get();
	ftr2.get();
}
