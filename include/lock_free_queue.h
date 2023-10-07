# ifndef LOCK_FREE_QUEUE_H
# define LOCK_FREE_QUEUE_H

# include <vector>
# include <list>
# include <thread>
# include <iostream>

template <typename T>
struct lock_free_queue {
private:
    std::list<T> lst;

    typename std::list<T>::iterator iHead, iTail;

public:
    lock_free_queue() {
        lst.push_back(T());  // dummy element for separating iHead from iTail
        iHead = lst.begin();
        iTail = lst.end();
    }

    void produce(const T& t) {
        std::cout << "producer adds " << t << std::endl;

        lst.push_back(t);
        iTail = lst.end();
        lst.erase(lst.begin(), iHead);
    }

    bool consume(T& t) {
        auto iFirst = iHead;
        ++iFirst;

        if (iFirst != iTail) {
            iHead = iFirst;

            t = *iHead;

            std::cout << "consumer consumes " << t << std::endl;

            return true;
        }

        // no element to fetch
        return false;
    }

    void print() {
        auto head = iHead;
        ++head;

        for (auto elem = head; elem != iTail; ++elem) {
            std::cout << *elem << ", ";
        }
        std::cout << std::endl;
    }

};


# endif