#include <iostream>
#include <future>

/*
 *   /-> B ->\
 *  A         D
 *   \-> C ->/
 */

void work_node(char c) {
	std::cout << c << ' ';
}

int main() {

	//auto launch_policy = std::launch::deferred;
	auto launch_policy = std::launch::async;

	// Prepare graph
	
	// A node
	std::shared_future<void> ftrA = std::async(launch_policy, work_node, 'A');

	// B node
	std::future<void> ftrB = std::async(launch_policy, [&](char c) {
		ftrA.get();
		work_node(c);
	}, 'B');

	// C node
	std::future<void> ftrC = std::async(launch_policy, [&](char c) {
		ftrA.get();
		work_node(c);
	} , 'C');

	// D node
	std::future<void> ftrD = std::async(launch_policy, [&](char c) {
		// swap 2 next lines
		ftrC.get();
		ftrB.get();

		work_node(c);
	}, 'D');

	// Launch graph on node D
	ftrD.get();

	std::cout << '\n';
}
