#include <iostream>
#include "threadpool.h"

std::function<void()> printnumber(int num) {
    return [num]() {
        std::cout << "Printing value " << num << std::endl;
    };
}

int main() {
    threadpool pool(3);

    pool.add_task(printnumber(1));
    pool.wait_all();

    pool.add_task(printnumber(2));
    pool.wait_all();

    pool.add_task(printnumber(3));
    pool.add_task(printnumber(4));
    pool.shutdown_pool();
    return 0;
}