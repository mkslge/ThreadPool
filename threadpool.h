//
// Created by Mark on 1/8/26.
//

#ifndef THREADPOOL_H
#define THREADPOOL_H

#include <thread>
#include <vector>
#include

inline int DEFAULT_SIZE = 20;

class threadpool {
private:
    int size;
    std::vector<std::thread> workers;
    std::vector<void*> tasks;



public:

    explicit threadpool(int size) : size(size), workers(std::vector<std::thread>(size)) {}
    threadpool() : threadpool(DEFAULT_SIZE) {}



};



#endif //THREADPOOL_H
