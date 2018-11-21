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

		int pop() {
			int i = -1;
			mtx.lock();
			i = q.front();
			q.pop();
			mtx.unlock();
			return i;
		}

		bool empty() {
			return q.empty();
		}

	private:
		std::mutex mtx;
};  
