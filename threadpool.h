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

inline int DEFAULT_SIZE = 20;

class threadpool {
private:
    int size;

    std::mutex lock;
    std::vector<std::thread> workers;
    std::queue<std::function<void()>> tasks;

    bool shutdown = false;

private:
    void worker_loop();

public:

    explicit threadpool(int size) : size(size), workers(std::vector<std::thread>(size)) {
        for (int i = 0; i < workers.max_size();i++) {

        }
    }
    threadpool() : threadpool(DEFAULT_SIZE) {}

    ~threadpool();

    void add_task(const std::function<void()>& task);





};



#endif //THREADPOOL_H
