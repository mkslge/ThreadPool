//
// Created by Mark on 1/8/26.
//

#ifndef UTILITY_H
#define UTILITY_H

#include <queue>
#include <functional>

class utility {
public:
    static void clear_queue(std::queue<std::function<void()>> &queue);
};



#endif //UTILITY_H
