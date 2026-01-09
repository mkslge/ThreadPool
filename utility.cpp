//
// Created by Mark on 1/8/26.
//

#include "utility.h"


void utility::clear_queue(std::queue<std::function<void()>> &queue) {
    std::queue<std::function<void()>> empty;
    queue.swap(empty);
}
