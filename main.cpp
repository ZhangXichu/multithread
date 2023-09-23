# include <iostream>
# include <cstring>
# include <algorithm>


void func(int&& x) {
    std::cout << "Rvalue reference = " << x << std::endl;
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

    return 0;
}