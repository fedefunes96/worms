#ifndef COUNTER_H
#define COUNTER_H

#include <thread>
#include <mutex>
#include <condition_variable>

#define SECOND_IN_MILLISECONDS 1000

class Counter {
private:
	int count;
	std::mutex m_count;

public:
	Counter();
	void set_time(const int secs);
	void start_counting();
	void stop();
};

#endif
