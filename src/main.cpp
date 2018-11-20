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
     pi.insert({1, computePiDigit(1)});

}



int main() {
	std::unordered_map<int, int> pi;
	std::queue<int> task;
	std::mutex pi_mutex;

	for(int i = 1; i <= 1000; i++) {
		task.push(i);
	}

	// Make as many threads as there are CPU cores
    	// Assign them to run our threadWorker function, and supply arguments as necessary for that function
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

	std::cout << std::endl << std::endl;

#warning TODO: Print the digits of PI from our unordered_map, in order
	for(int i = 0; i <= 1000; i++) {
		 std::unordered_map<int,int>::const_iterator got = pi.find(i);
		 std::cout << got->second; 
	}

	return 0;
}
