#ifndef BLOCK_QUEUE_H
#define BLOCK_QUEUE_H

#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>

template <class T>
class BlockQueue {
private:
	std::queue<T> queue;
	std::mutex m;
	std::condition_variable cond_var;

public:
	void push(const T& obj) {
		std::unique_lock<std::mutex> mlock(this->m);
		this->queue.push(std::move(obj));
		mlock.unlock();
		this->cond_var.notify_one();	
	}

	void push(T&& obj) {
		std::unique_lock<std::mutex> mlock(this->m);
		this->queue.push(std::move(obj));
		mlock.unlock();
		this->cond_var.notify_one();
	}

	T pop() {
		std::unique_lock<std::mutex> mlock(this->m);

		while (this->queue.empty()) {
			this->cond_var.wait(mlock);
		}

		T obj = this->queue.front();

		this->queue.pop();

		return obj;		
	}

	//Cannot be copied
	BlockQueue(const BlockQueue&) = delete;
	BlockQueue &operator=(const BlockQueue&) = delete;
};

#endif
