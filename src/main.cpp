#include <iostream>
#include <thread>
#include <vector>
#include <memory>
#include <queue>
#include <mutex>
#include<unordered_map>

#include "computePi.hpp"


void threadWorker(std::uint16_t threadNum, std::queue<int> &task, std::unordered_map<int,int> &pi) {
    // This code exists simply to illustrate a worker thread.
    // I had better not see this in your final submission.
   // std::cout << "Hi! I'm thread number " << threadNum << ", and I can count to 10!\n";
    //for (int i = 1; i <= 10; ++i)
//		std::cout << "[" <<  threadNum << "] " << i << std::endl;

   // std::cout << "[" <<  threadNum << "] watch me compute digit #"
     //   << threadNum+1 << " of pi: "
     int digit = task.front();
     task.pop();
     pi.insert({digit, computePiDigit(digit)});
}



int main() {
	std::unordered_map<int, int> pi;
	std::queue<int> task;
	std::mutex pi_mutex;

	// push all tasks onto queue
	for(int i = 1; i < 1000; i++) {
		task.push(i);
	}

	// Make as many threads as there are CPU cores
    	// Assign them to run our threadWorker function, and supply arguments as necessary for that function
	while(!task.empty()) {
	std::vector<std::shared_ptr<std::thread>> threads;
	for (std::uint16_t core = 0; core < std::thread::hardware_concurrency(); core++) {
	// The arguments you wish to pass to threadWorker are passed as
	// arguments to the constructor of std::thread
		pi_mutex.lock();
		threads.push_back(std::make_shared<std::thread>(threadWorker, core, std::ref(task),std::ref(pi)));
		std::cout << ".";
		std::cout.flush();
		pi_mutex.unlock();
	}

	//
	// Wait for all of these threads to complete
	for (auto&& thread : threads)
		thread->join();


	}
	
	// print digits of pi in order
	std::cout << std::endl << std::endl;
	std::cout << 3 << ".";
	for(int i = 1; i < 1000; i++) {
		std::unordered_map<int,int>::const_iterator got = pi.find(i);
		std::cout << got->second; 
		std::cout.flush();
	}
	std::cout << std::endl;
	return 0;
}
