# include <iostream>
# include <cstring>
# include <algorithm>
# include <thread>
# include <chrono>


void func(int&& x) {
    std::cout << "Rvalue reference = " << x << std::endl;
}

void str_by_ref(std::string& str) {
    str = "xyz";
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
    



    return 0;
}