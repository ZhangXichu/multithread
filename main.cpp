# include <cstring>
# include <algorithm>
# include <shared_mutex>
# include <random>
# include "include/class_singleton.h"
# include "include/dining_philosophers.h"

std::mutex task_mutex;
std::mutex print_mutex;
std::mutex mut;
std::shared_mutex shared_mut;

int shared_var = 0;
int shared_x = 0;


// simple thread safe vector class
class Vector {
    std::mutex mut;
    std::vector<int> vec;

    public:

    void push_back(const int& i) {
        mut.lock();
        vec.push_back(i);
        mut.unlock();
    }

    void print() {
        mut.lock();
        for (auto i: vec) {
            std::cout << i << ", ";
        }
        mut.unlock();
    }
};



void func(int&& x) {
    std::cout << "Rvalue reference = " << x << std::endl;
}

void str_by_ref(std::string& str) {
    str = "xyz";
}

void static_var() {
    static int var_s = 1;

    var_s += 1;

    std::cout << "var_s = " << var_s << std::endl;

}

class string {

    char* data;

    public:

    string(const char* p) {
        std:: cout << "string constructor 1:" << std::endl;

        size_t size = std::strlen(p) + 1;
        data = new char[size];
        std::memcpy(data, p, size);

        std::cout << "data: " << data << std::endl;
    }

    ~string() {
        delete[] data;
    }

    string(const string& that) {
        size_t size = std::strlen(that.data) +1;
        data = new char[size];
        std::memcpy(data, that.data, size);
    }

    string(string&& that) {
        data = that.data;
        that.data = nullptr;
    }

    const char* get_data() {
        return data;
    }

};

void hello() {
    std::cout << "Hello thread" << std::endl;
}


void thread_num(int num) {
    std::this_thread::sleep_for(std::chrono::seconds(num));
    std::cout << "This is thread: " << num << std::endl;
}


void interruption_demo(std::string str) {
    for (int i = 0; i < 5; ++i) {
        std::cout << str[0];
        std::this_thread::sleep_for(std::chrono::seconds(1));
        std::cout << str[1] << str[2] << std::endl; 
    }
}


void mutex_demo(const std::string& str) {
    for (int i = 0; i < 5; i++) {
        task_mutex.lock();

        std::cout << str[0];
        std::this_thread::sleep_for(std::chrono::seconds(1));
        std::cout << str[1] << str[2] << std::endl; 

        task_mutex.unlock();
    }
}

void add_to_vec(Vector& vec) {
    for (int i = 0; i < 5; i++) {
        vec.push_back(i);
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
        vec.print();
    }
}


void add_to_vec_guard(std::string str) {
    for (int i = 0; i < 5; i++) {
        try {
            std::lock_guard<std::mutex> lck_guard(print_mutex);

            std::cout << str[0];
            std::this_thread::sleep_for(std::chrono::seconds(1));
            std::cout << str[1] << str[2] << std::endl; 

            // throw std::exception();

            std::this_thread::sleep_for(std::chrono::milliseconds(25));
        }
        catch (std::exception& e) {
            std::cout << "Exception caught: " << e.what() << std::endl;
        }
    }
}


auto unique_lock_demo() {
    int inc = 1;
    {
        std::unique_lock<std::mutex> lock(task_mutex);
        for (int i = 0; i < 10; i++) {
            shared_var += inc;

            std::this_thread::sleep_for(std::chrono::milliseconds(25));
        }
    } // The mutex is automatically released here
}


/**
 * @brief reader and writer
 * 
 */

void writer() {
    std::lock_guard<std::mutex> lck_guard(mut);
    shared_x += 1;
}

void reader() {
    std::lock_guard<std::mutex> lck_guard(mut);

    std::this_thread::sleep_for(std::chrono::milliseconds(100));
}

void reader_shared_mut() { // much faster then the reader above
    std::shared_lock<std::shared_mutex> lck_guard(shared_mut);

    std::this_thread::sleep_for(std::chrono::milliseconds(100));
}


void task_singleton() {
    Singleton& single = get_singleton();

    // check the adddress to make sure that
    // all the threads get the same instance
    std::cout << &single << std::endl; 
}


thread_local std::mt19937 mt;

void rand_nums() {
        std::uniform_real_distribution<double> dist(0, 1);

        for (int i = 0; i < 10; i++) {
            std::cout << dist(mt) << std::endl;
        }
    }


int main() {

    /**
     * @brief overview
     * 
     */

    auto add = [] (int a, int b) {
        return a + b;
    };

    int n = 1;
    auto capture_add = [n] (int a) {
        return a + n;
    };

    auto capture_ref = [&n] (int a) {
        n = n + 1;
    };

    auto res = add(5, 6);
    auto res_c = capture_add(5);
    capture_ref(5);

    std::cout << "res of add = " << res << std::endl;
    std::cout << "res of capture_add = " << res_c << std::endl;
    std::cout << "res of capture_ref = " << n << std::endl;


    int y;
    y = 2;
    func(std::move(y));

    std::cout << "y = " << y << std::endl;


    const char* text = "This is a string.";
    string str_a = string(text);
    string str_b = string(std::move(str_a));

    std::cout << "value of str_b: " << str_b.get_data() << std::endl;
    // std::cout << "value of str_a: " << str_a.get_data() << std::endl;

    std::cout << "address of str_b: " << (void*) str_b.get_data() << std::endl;
    std::cout << "address of str_a: " << (void*) str_a.get_data() << std::endl;

    std::cout << "Static variable: " << std::endl;
    static_var();
    static_var();
    static_var();


    /**
     * @brief threads
     * 
     * @return std::thread 
     */
    std::thread thr(hello);
    thr.join();

    std::string str = "abc";

    std::thread thr_abc(str_by_ref, std::ref(str));
    std::cout << "Thread handle of thr_abc before join(): " << thr_abc.native_handle() << std::endl;

    thr_abc.join();
    std::cout << "Thread handle of thr_abc after join(): " << thr_abc.native_handle() << std::endl;

    std::cout << "str is now: " << str << std::endl;

    std::cout << "Start 3 threads:" << std:: endl;

    // std::thread t1(thread_num, 1);
    // std::thread t2(thread_num, 2);
    // std::thread t3(thread_num, 3);

    // t1.join();
    // t2.join();
    // t3.join();

    // std::thread t_abc(interruption_demo, "abc");
    // std::thread t_def(interruption_demo, "def");
    // std::thread t_xyz(interruption_demo, "xyz");

    // t_abc.join();
    // t_def.join();
    // t_xyz.join();


    // std::cout << "after using mutex: " << std::endl;

    // std::thread t_abc_2(mutex_demo, "abc");
    // std::thread t_def_2(mutex_demo, "def");
    // std::thread t_xyz_2(mutex_demo, "xyz");

    // t_abc_2.join();
    // t_def_2.join();
    // t_xyz_2.join();
    

    // Vector v;

    // std::thread thr_v1(add_to_vec, std::ref(v));
    // std::thread thr_v2(add_to_vec, std::ref(v));
    // std::thread thr_v3(add_to_vec, std::ref(v));

    // thr_v1.join();
    // thr_v2.join();
    // thr_v3.join();


    // std::thread t_abc_2(add_to_vec_guard, "abc");
    // std::thread t_def_2(add_to_vec_guard, "def");
    // std::thread t_xyz_2(add_to_vec_guard, "xyz");

    // t_abc_2.join();
    // t_def_2.join();
    // t_xyz_2.join();

# ifdef UNIQUE_LOCK_DEMO

    std::thread t_a(unique_lock_demo);
    std::thread t_a2(unique_lock_demo);
    std::thread t_a3(unique_lock_demo);
    std::thread t_a4(unique_lock_demo);
    std::thread t_a5(unique_lock_demo);

    t_a.join();
    t_a2.join();
    t_a3.join();
    t_a4.join();
    t_a5.join();

    std::cout << "the value of share_var: " << shared_var << std::endl;

    // effective way to start multiple threads
    std::vector<std::thread> vec_threads;

    for (int i = 0; i < 20; i++) {
        vec_threads.push_back(std::thread(reader_shared_mut));
    }

    vec_threads.push_back(std::thread(writer));
    vec_threads.push_back(std::thread(writer));

    for (int i = 0; i < 20; i++) {
        vec_threads.push_back(std::thread(reader_shared_mut));
    }

    for (auto& thr : vec_threads) {
        thr.join();
    }


    // shared data initialization
    // singleton class
    std::vector<std::thread> threads_s;

    for (int i = 0; i < 10; i++) {
        threads_s.push_back(std::thread(task_singleton));
    }

    for (auto& thr : threads_s) {
        thr.join();
    }

    std::thread t_rnd1(rand_nums);
    std::thread t_rnd2(rand_nums);

    t_rnd1.join();
    t_rnd2.join();

# endif

    
# ifdef DINING

    std::vector<std::thread> philos;

    for (int i = 0; i < nphilosophers; ++i) {
        philos.push_back(std::move(std::thread{dine, i}));
    }

    for (auto& philo: philos) {
        philo.join();
    }

    for (int i = 0; i < nphilosophers; i++) {
        std::cout << "Philosopher " << names[i];
        std::cout << " had " << mouthfuls[i] << "mouthfuls" << std::endl;
    }

# endif
    
    

    return 0;
}