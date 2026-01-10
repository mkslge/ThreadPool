//
// Created by Mark on 1/8/26.
//

#ifndef THREADPOOL_H
#define THREADPOOL_H

#include <thread>
#include <vector>
#include <queue>
#include <mutex>
#include <functional>
#include <iostream>
#include "utility.h"

inline int DEFAULT_SIZE = 20;
inline int QUEUE_MAX_SIZE = 1000;
class threadpool {
private:
    int size;

    std::condition_variable finished_cv;
    int active_threads = 0;

    std::mutex lock = std::mutex();
    std::condition_variable cv;
    std::vector<std::thread> workers;
    std::queue<std::function<void()>> tasks;

    bool shutdown = false;

private:
    void worker_loop();
    [[nodiscard]] bool work_finished() const;

public:

    explicit threadpool(int size) : size(size) {
        workers.reserve(size);

        for (int i = 0; i < this->size;i++) {
            workers.emplace_back(&threadpool::worker_loop, this);
        }

    }
    threadpool() : threadpool(DEFAULT_SIZE) {}

    ~threadpool();

    bool add_task(std::function<void()> task);

    void wait_all();

    bool shutdown_pool();
    bool shutdown_pool_now();







};



#endif //THREADPOOL_H
