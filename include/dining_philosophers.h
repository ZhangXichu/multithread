# ifndef DINING_PHILOSOPHER_H
# define DINING_PHILOSOPHER_H

# include <iostream>
# include <thread>
# include <mutex>
# include <vector>
# include <string>
# include <chrono>

constexpr int nforks = 5;
constexpr int nphilosophers = nforks;

extern std::string names[nphilosophers];

extern int mouthfuls[nphilosophers];

// a philosopher is either eating or thinkng
constexpr auto think_time = std::chrono::seconds(2);
constexpr auto eat_time = std::chrono::seconds(1);

extern std::mutex fork_mutex[nforks];

extern std::mutex print_mutex_ph;

void print(int n, const std::string& str, int forkno);
void print(int n, const std::string& str);
void dine(int nphilo);

# endif