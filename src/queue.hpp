class MyQueue {
	public:
		std::queue<int> q;

		MyQueue() {
			std::queue<int> q;
		}
		void push(int item) {
			mtx.lock();
			q.push(item);
			mtx.unlock();
		}

		void pop() {
			mtx.lock();
			q.pop();
			mtx.unlock();
		}

		bool empty() {
			return q.empty();
		}

	private:
		std::mutex mtx;
};  
