#ifndef COUNTER_H
#define COUNTER_H

#include <thread>
#include <mutex>

#define SECOND_IN_MILLISECONDS 1000

class Counter {
private:
	int count;
	bool count_over;
	std::thread t;
	std::mutex m_count;
	std::mutex m_over;

	void counting();
public:
	Counter();
	bool is_over();
	void set_time(const int secs);
	void start_counting();
	void stop();
};

#endif
