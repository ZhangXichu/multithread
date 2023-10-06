# include "include/producer_consumer.h"

std::mutex mut_p_c;

void produce(std::promise<int>& px) {
    int x = 42;

    std::cout << "Promise sets shared state to: " << x << std::endl;

    px.set_value(x);
}

void consume(std::future<int>& fx) {

    int x = fx.get();

    std::cout << "The promised x = " << x << std::endl;
}

void consume_sh(std::shared_future<int>& fx) {
    int x = fx.get();

    std::lock_guard<std::mutex> lck_guard(mut_p_c);

    std::cout << "Thread " << std::this_thread::get_id() << " with shared future hass x = " << x << std::endl;

}
