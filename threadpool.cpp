//
// Created by Mark on 1/8/26.
//

#include "threadpool.h"



threadpool::~threadpool() {
    this->shutdown_pool();

    for (int i = 0; i < this->size;i++) {
        if (this->workers[i].joinable()) {
            this->workers[i].join();
        }
    }
}


void threadpool::add_task(const std::function<void()>& task) {
    tasks.emplace(task);
}

void threadpool::worker_loop() {
    while (true) {
        if (lock.try_lock()) {
            //checking if all tasks have been started we have shutdown
            if (this->tasks.empty() && this->shutdown) {
                lock.unlock();
                return;
            }

            //if a task has been added to the queue we must assign it to a thread
            if (!this->tasks.empty()) {

                //grab the latest task
                std::function<void()> task = this->tasks.front();
                this->tasks.pop();
                //run the task
                task();

            }
            lock.unlock();
        }

    }
}

bool threadpool::shutdown_pool_now() {
    if (lock.try_lock()) {
        this->shutdown = true;
        utility::clear_queue(this->tasks);
    } else {
        return false;
    }
}

bool threadpool::shutdown_pool() {
    if (lock.try_lock()) {
        this->shutdown = true;
        return true;
    } else {
        return false;
    }
}









