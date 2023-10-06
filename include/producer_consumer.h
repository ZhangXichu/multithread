# ifndef PRODUCER_CONSUMER_H
# define PRODUCER_CONSUMER_H


# include <thread>
# include <chrono>
# include <future>
# include <iostream>

extern std::mutex mut_p_c;

void produce(std::promise<int>& px);
void consume(std::future<int>& fx);
void consume_sh(std::shared_future<int>& fx);


# endif