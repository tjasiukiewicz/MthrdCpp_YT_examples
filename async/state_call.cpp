#include <iostream>
#include <future>
#include <chrono>
#include <thread>

void work() {
	unsigned i = 5;
	while(i--) {
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
		std::cout << "Working." << std::endl;
	}
}

int main() {

	auto ftr = std::async(std::launch::async, work);
	std::future_status status;
	do {
		switch (status = ftr.wait_for(std::chrono::milliseconds(500)); status) {
			case std::future_status::deferred:
				std::cout << "deferred (not run.. yet?)" << std::endl;
				break;
			case std::future_status::timeout:
				std::cout << "timeout  (still running)" << std::endl;
				break;
			case std::future_status::ready:
				std::cout << "ready    (complete)" << std::endl;
				break;
		}
	} while(status != std::future_status::ready);
	ftr.get();
}
