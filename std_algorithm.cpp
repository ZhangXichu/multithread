#include "include/std_algorithm.h"

int main() {

    std::string str = "This is a string";

    int res_i = find_first_occur(str.cbegin(), str.cend(), 'i');

    std::cout << "The 1st occurence of the given char is found at index: " << res_i << std::endl;

    return 0;
}