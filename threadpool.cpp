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


bool threadpool::add_task(std::function<void()> task) {
    {
        std::lock_guard<std::mutex> lock_guard(lock);

        if (this->shutdown) {
            return false;
        }
        tasks.emplace(std::move(task));
    }
    cv.notify_one();
    return true;
}

bool threadpool::work_finished() const {
    return this->tasks.empty() && this->shutdown;
}


void threadpool::worker_loop() {
    while (true) {
        std::function<void()> task;

        {
            std::unique_lock<std::mutex> ul(lock);

            cv.wait(ul, [this] {
                return this->shutdown || !this->tasks.empty();
            });

            //checking if all tasks have been started we have shutdown
            if (this->shutdown && tasks.empty()) {
                return;
            }


            //grab the latest task
            task = std::move(this->tasks.front());
            this->tasks.pop();
            active_threads++;
        }

        task();

        {
            std::unique_lock<std::mutex> ul(lock);
            active_threads--;
            if (active_threads == 0) {
                finished_cv.notify_all();
            }
        }

    }
}

bool threadpool::shutdown_pool_now() {
    {
        std::lock_guard<std::mutex> lg(lock);
        this->shutdown = true;
        utility::clear_queue(this->tasks);

    }
    cv.notify_all();
    return true;
}

bool threadpool::shutdown_pool() {
    {
        std::lock_guard<std::mutex> lg(lock);
        this->shutdown = true;
    }
    cv.notify_all();
    return true;
}



void threadpool::wait_all() {

    {
        std::unique_lock<std::mutex> ul(lock);
        finished_cv.wait(ul,
        [this] {return tasks.empty() && active_threads == 0;
        });
        ul.unlock();
    }

}









