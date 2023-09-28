# ifndef SINGLETON_H
# define SINGLETON_H

# include <iostream>


class Singleton {

public:

    // Preventing Object Copy
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;
    Singleton(Singleton&&) = delete;
    Singleton& operator=(Singleton&&) = delete;

    Singleton() {
        std::cout << "Initializing Singleton" << std::endl;
    }

};

Singleton& get_singleton();

# endif