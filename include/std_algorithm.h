#ifndef STD_ALGORITHM_H
#define STD_ALGORITHM_H

#include <algorithm>
#include <string>
#include <iostream>

template <typename ForwardIter, typename T> 
[[nodiscard]] int find_first_occur(ForwardIter it_begin, ForwardIter it_end, T target) {

    int counter = 0;

    for (ForwardIter it = it_begin; it != it_end; ++it) {

        if (target == *it) {
            return counter;
        }

        counter++;
    }

    return -1;
}

#endif