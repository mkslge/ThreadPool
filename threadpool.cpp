//
// Created by Mark on 1/8/26.
//

#include "threadpool.h"



threadpool::~threadpool() {
    this->shutdown = true;
}


void threadpool::add_task(const std::function<void()>& task) {
    tasks.emplace(task);
}

void threadpool::worker_loop() {
    while (true) {
        //checking if all tasks have been started we have shutdown
        if (this->tasks.empty() && this->shutdown) {
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
    }
}





