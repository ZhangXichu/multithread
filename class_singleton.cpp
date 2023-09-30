# include "include/class_singleton.h"

// the first thread will create an instance
// and the other threads are gonna just return the same instance

Singleton& get_singleton(){
    static Singleton single;

    return single;
}