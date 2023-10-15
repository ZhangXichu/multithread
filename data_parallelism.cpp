#include "include/data_parallelism.h"

static std::mt19937 mt;
std::uniform_real_distribution<double> dist(0, 100);

double accum(double *beg, double *end) {


    return std::accumulate(beg, end, 0.0);
}


double add_parallel(std::vector<double>& vec) {
    auto vec0 = &vec[0];
    auto vsize = vec.size();

    auto fut1 = std::async(std::launch::async, accum,  vec0, vec0 + vsize / 4);
    auto fut2 = std::async(std::launch::async, accum,  vec0 + vsize / 4, vec0 + 2 * vsize / 4);
    auto fut3 = std::async(std::launch::async, accum,  vec0 + 2 * vsize / 4, vec0 + 3 * vsize / 4);
    auto fut4 = std::async(std::launch::async, accum,  vec0 + 3 * vsize / 4, vec0 + vsize);

    return fut1.get() + fut2.get() + fut3.get() + fut4.get();
}


// same implementation as before
// with packaged tasks
double add_parallel_pac(std::vector<double>& vec) {
    using task_type = double(double *, double *);

    std::packaged_task<task_type> ptask1(accum);
    std::packaged_task<task_type> ptask2(accum);
    std::packaged_task<task_type> ptask3(accum);
    std::packaged_task<task_type> ptask4(accum);

    auto fut1 = ptask1.get_future();
    auto fut2 = ptask2.get_future();
    auto fut3 = ptask3.get_future();
    auto fut4 = ptask4.get_future();

    auto vec0 = &vec[0];

    auto vsize = vec.size();

    std::thread thr1(std::move(ptask1), vec0, vec0 + vsize / 4);
    std::thread thr2(std::move(ptask1), vec0 + vsize / 4, vec0 + 2 * vsize / 4);
    std::thread thr3(std::move(ptask1), vec0 + 2 * vsize / 4, vec0 + 3 * vsize / 4);
    std::thread thr4(std::move(ptask1), vec0 + 3 * vsize / 4, vec0 + vsize);

    thr1.join();
    thr2.join();
    thr3.join();
    thr4.join();

    return fut1.get() + fut2.get() + fut3.get() + fut4.get();
}   


int main() {
    std::vector<double> vec(16);
    std::iota(vec.begin(), vec.end(), 1.0);

    std::vector<double> vrand(100);
    std::generate(vrand.begin(), vrand.end(), [&vrand]() {return dist(mt);}); 

    double sum_n = 0.0;
    for (auto& x : vec) {
        std::cout << x << " ";
        sum_n += x;
    }
    std::cout << std::endl;
    std::cout << "sum_n = " << sum_n << std::endl;

    std::cout << "Sum of first 16 integer: " << add_parallel_pac(vec) << std::endl;
    std::cout << "Sum of 100 random numbers: " << add_parallel_pac(vrand) << std::endl;
}