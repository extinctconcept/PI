class MyMap {
	public:
		std::unordered_map<int, int> m;

		void insert(int i, int j) {
			mtx.lock();
			m.insert({i, j});
			mtx.unlock();
		}

		void find(int i) {
			mtx.lock();
			m.find(i);
			mtx.unlock();
		}

	private:
		std::mutex mtx;
};  
