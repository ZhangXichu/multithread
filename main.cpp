# include <cstring>
# include <algorithm>
# include <shared_mutex>
# include <random>
# include <functional>
# include <condition_variable>
# include "include/class_singleton.h"
# include "include/dining_philosophers.h"
# include "include/producer_consumer.h"

// flagss for thread communication
bool update_progress = false;
bool completed = false; // shows whether data fetching (downloading) is completed


std::mutex task_mutex;
std::mutex print_mutex;
std::mutex mut;
std::shared_mutex shared_mut;

std::string sdata;

// mutexes to protect the shared variables
std::mutex data_mutex;
std::mutex completed_mutex; 

std::mutex mut_cond_var;
std::condition_variable cond_var;

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


/*
simulation of mutithreading with coordination
through variables
*/

void fetch_data() {
    for (int i = 0; i < 5; i++) {
        std::cout << "Fetcher thread waiting for data..." << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(2));

        std::lock_guard<std::mutex> data_lock(data_mutex);
        // update data
        sdata += "Block" + std::to_string(i+1);
        std::cout << "sdata: " << sdata << std::endl;
        // notify the progress bar thread
        update_progress = true;
    }
    std::cout << "Fetch sdata has ended" << std::endl;

    std::lock_guard<std::mutex> completed_lck(completed_mutex);
    completed = true;
}

void progress_bar() {
    size_t len = 0;

    while (true) {
        std::cout << "Progress bar thread waiting for data..." << std::endl;

        // wait until there is some new data to display
        std::unique_lock<std::mutex> data_lck(data_mutex);
        while (!update_progress) {
            data_lck.unlock();
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
            data_lck.lock();
        }

        len = sdata.size();

        // set the flag back to false
        update_progress = false;
        data_lck.unlock();

        std::cout << "Received " << len << "bytes so far" << std::endl;

        std::lock_guard<std::mutex> complete_lck(completed_mutex);
        // terminate when the download has finishes
        if (completed) {
            std::cout << "Progress bar thread has ended" << std::endl;
            break;
        }
    }
}

void process_data() {
    std::cout << "Processing thread waiting for data..." << std::endl;

    // wait until the download is completed
    std::unique_lock<std::mutex> completed_lck(completed_mutex);

    while (!completed) {
        completed_lck.unlock();
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
        completed_lck.lock();
    }

    completed_lck.unlock();

    std::lock_guard<std::mutex> data_lck(data_mutex);
    std::cout << "Processing sdata: " << sdata << std::endl;

    // Some processing
}

/*
demo - conditional variable
*/
void reader_cond() {
    std::cout << "Reader thread locking mutex" << std::endl;
    
    std::unique_lock<std::mutex> uniq_lck(mut);

    std::cout << "Reader thread has locked the mutex" << std::endl;

    std::cout << "Reader thread sleeping..." << std::endl;

    // it's necessary to use the unique_lock in this function,
    // since here the condition_variable must be able to unlock the mutex
    cond_var.wait(uniq_lck);

    std::cout << "Reader thread wakes up" << std::endl;
    std::cout << "Data is " << sdata << std::endl;
}


void writer_cond() {
    {
        std::cout << "Writer thread locking mutex" << std::endl;

        // here we can use lock_guard (less overhead) 
        // because we don't need to call unlock
        std::lock_guard<std::mutex> lck_guard(mut); 
        std::cout << "Writer thread has locked the mutex" << std::endl;

        std::this_thread::sleep_for(std::chrono::seconds(2));

        std::cout << "Writer thread modifying data..." << std::endl;

        // modify the data
        sdata = "Populated";
    }
    std::cout << "Write thread sends notification" << std::endl;

    cond_var.notify_one();
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

# ifdef THR_INTERRUPT_DEMO

    std::thread t1(thread_num, 1);
    std::thread t2(thread_num, 2);
    std::thread t3(thread_num, 3);

    t1.join();
    t2.join();
    t3.join();

    std::thread t_abc(interruption_demo, "abc");
    std::thread t_def(interruption_demo, "def");
    std::thread t_xyz(interruption_demo, "xyz");

    t_abc.join();
    t_def.join();
    t_xyz.join();

    std::cout << "after using mutex: " << std::endl;

    std::thread t_abc_2(mutex_demo, "abc");
    std::thread t_def_2(mutex_demo, "def");
    std::thread t_xyz_2(mutex_demo, "xyz");

    t_abc_2.join();
    t_def_2.join();
    t_xyz_2.join();

# endif
    

# ifdef LOCK_GUARD_DEMO
    Vector v;

    std::thread thr_v1(add_to_vec, std::ref(v));
    std::thread thr_v2(add_to_vec, std::ref(v));
    std::thread thr_v3(add_to_vec, std::ref(v));

    thr_v1.join();
    thr_v2.join();
    thr_v3.join();


    std::thread t_abc_2(add_to_vec_guard, "abc");
    std::thread t_def_2(add_to_vec_guard, "def");
    std::thread t_xyz_2(add_to_vec_guard, "xyz");

    t_abc_2.join();
    t_def_2.join();
    t_xyz_2.join();

# endif


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

    unsigned int x;

    std::cout << "Pick a dining method (enter the corresponding integer): " << std::endl;
    std::cout << "(0) Original method: everyone picks the left fork" << std::endl;
    std::cout << "(1) Solution 1: try to pick up both forks" << std::endl;
    std::cout << "(2) Solution 2: pick the 2nd fork only if the first fork has lower index (hierarchy lock)" 
        << std::endl;
    std::cin >> x;

    std::function<void(int)> dine_func;

    switch(x) {
        case 0:
            dine_func = dine;
            break;
        case 1:
            dine_func = dine_both_fork;
            break;
        case 2:
            dine_func = dine_hierarchy;
            break;
        default:
            std::cout << "No such option, slect again: " << std::endl;
            std::cin >> x;
    }

    std::vector<std::thread> philos;

    for (int i = 0; i < nphilosophers; ++i) {
        philos.push_back(std::move(std::thread{dine_func, i}));
    }

    for (auto& philo: philos) {
        philo.join();
    }

    for (int i = 0; i < nphilosophers; i++) {
        std::cout << "Philosopher " << names[i];
        std::cout << " had " << mouthfuls[i] << "mouthfuls" << std::endl;
    }

# endif
    

# ifdef SYNC
    
    std::thread fetcher(fetch_data);
    std::thread prog(progress_bar);
    std::thread processor(process_data);

    fetcher.join();
    prog.join();
    processor.join();

# endif


/*
use of conditional variable
*/
# ifdef SYNC_COND_VAR
    sdata = "Empty";

    std::cout << "Data is " << sdata << std::endl;

    std::thread reader(reader_cond);
    std::thread writer(writer_cond);

    writer.join();
    reader.join();
# endif



# ifdef PROMISE_FUTURE
    std::promise<int> prom;

    std::future<int> fut = prom.get_future();

    // the producer takes promise as argument
    std::thread thr_producer(produce, std::ref(prom));

    // the consumer takes future as argument
    std::thread thr_consumer(consume, std::ref(fut));

    thr_producer.join();
    thr_consumer.join();

    


# endif


# ifdef PROMISE_FUTURE_SH

    std::promise<int> prom;

    // can't let multiple consumers retrieve data from the same future

    std::shared_future<int> shared_fut1 = prom.get_future();
    std::shared_future<int> shared_fut2 = shared_fut1; // copy

    std::thread thr_producer(produce, std::ref(prom));

    std::thread thr_consumer1(consume_sh, std::ref(shared_fut1));
    std::thread thr_consumer2(consume_sh, std::ref(shared_fut2));

    thr_consumer1.join();
    thr_consumer2.join();
    thr_producer.join();

# endif
    

    return 0;
}