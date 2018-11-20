class Mutex {
	private:
		bool available;
	public: 
		aquire() {
			while(!available) {
				;
			}
			available = false;
		}

		release() {
			available = true;
		}
};
