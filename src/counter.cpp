#include "counter.h"
#include <mutex>
#include <chrono>
#include <thread>

Counter::Counter() {
	this->count = 0;
	this->count_over = true;
}

bool Counter::is_over() {
	std::lock_guard<std::mutex> lock(this->m_over);

	return this->count_over;
}

void Counter::set_time(const int secs) {
	std::lock_guard<std::mutex> lock(this->m_count);

	this->count = secs;
}

void Counter::start_counting() {
	//Start counting in another thread
	this->count_over = false;
	this->t = std::thread(&Counter::counting, this);
}

void Counter::counting() {
	while (this->count > 0) {
		//Mutex here, allows me to add extra time
		std::lock_guard<std::mutex> lock(this->m_count);		
		//Wait 1 sec
		std::this_thread::sleep_for(std::chrono::milliseconds(SECOND_IN_MILLISECONDS));
		
		this->count--;
	}

	//Count ends
	std::lock_guard<std::mutex> lock(this->m_over);
	this->count_over = true;
}

void Counter::stop() {
	//May end negative
	this->m_count.lock();
	this->count = 0;
	this->m_count.unlock();
	this->t.join();
}