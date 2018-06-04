#include "counter.h"
#include <mutex>
#include <chrono>
#include <thread>
#include <condition_variable>

Counter::Counter() {
	this->count = 0;
}

void Counter::set_time(const int secs) {
	std::lock_guard<std::mutex> lock(this->m_count);

	this->count = secs;
}

void Counter::start_counting() {
	while (this->count > 0) {
		//Mutex here, allows me to add extra time
		std::lock_guard<std::mutex> lock(this->m_count);		
		//Wait 1 sec
		std::this_thread::sleep_for(std::chrono::milliseconds(SECOND_IN_MILLISECONDS));
		
		this->count--;
		printf("Counting %d\n", this->count);
	}
}

void Counter::stop() {
	//May end negative
	std::lock_guard<std::mutex> lock(this->m_count);
	this->count = 0;
}