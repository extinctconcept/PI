#include <iostream>
#include <thread>
#include <vector>
#include <memory>
#include <queue>
#include <mutex>
#include<unordered_map>

#include "computePi.hpp"
#include "queue.hpp"
#include "map.hpp"


void threadWorker(std::uint16_t threadNum, std::queue<int> &task, std::unordered_map<int,int> &pi) {
	if(threadNum < 5) {
		int digit = task.front();
		task.pop();
		pi.insert({digit, computePiDigit(digit)});
	}
}



int main() {
	MyMap pi;
	MyQueue task;
	std::mutex pi_mutex;

	// push all tasks onto queue
	for(int i = 1; i <= 1000; i++) {
		task.push(i);
	}

	// Make as many threads as there are CPU cores
    	// Assign them to run our threadWorker function, and supply arguments as necessary for that function
	
	while(!task.empty()) {
	std::vector<std::shared_ptr<std::thread>> threads;
		for (std::uint16_t core = 0; core < std::thread::hardware_concurrency(); core++) {
		// The arguments you wish to pass to threadWorker are passed as
		// arguments to the constructor of std::thread
		threads.push_back(std::make_shared<std::thread>(threadWorker, core, std::ref(task.q), std::ref(pi.m)));
			std::cout << ".";
			std::cout.flush();
		}

		// Wait for all of these threads to complete
		for (auto&& thread : threads) {
			thread->join();
		}

	}
	
	// print digits of pi in order
	pi_mutex.lock();
	std::cout << std::endl << std::endl;
	std::cout << 3 << ".";
	for(int i = 1; i <= 1000; i++) {
		std::unordered_map<int,int>::const_iterator got = pi.m.find(i);
		std::cout << got->second; 
	}
	std::cout << std::endl;
	pi_mutex.unlock();
	return 0;
}
