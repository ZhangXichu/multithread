# include "include/dining_philosophers.h"

std::string  names[nphilosophers] = {"Plato", "René Descartes", "Immanuel Kant", "Friedrich Nietzsche", "Simone de Beauvoir"};
int mouthfuls[nphilosophers] = {0, 0, 0, 0, 0};
std::mutex fork_mutex[nforks];
std::mutex print_mutex_ph;


void print(int n, const std::string& str, int lfork, int rfork) {
    std::lock_guard<std::mutex> print_lock(print_mutex_ph);
    std::cout << "Philosopher " << names[n] << str << std::endl;
    std::cout << lfork << " and " << rfork << std::endl;
}

void print(int n, const std::string& str, int forkno) {
    std::lock_guard<std::mutex> print_lock(print_mutex_ph);
    std::cout << "Philosopher " << names[n] << str << forkno << std::endl;
}

void print(int n, const std::string& str) {
    std::lock_guard<std::mutex> print_lock(print_mutex_ph);
    std::cout << "Philosopher " << names[n] << str << std::endl;
}

// the original way of dining
// results in deadlock
void dine(int nphilo) {
    int lfork = nphilo;
    int rfork = (nphilo + 1) % nforks;

    print(nphilo, " \'s left fork is number ", lfork);
    print(nphilo, " \'s right fork is number ", rfork);
    print(nphilo, " is thinkng");

    std::this_thread::sleep_for(think_time);

    print(nphilo, "reaches for fork number ", lfork);

    // each philosohper needss 2 forks to eat

    // lock the left fork
    fork_mutex[lfork].lock();
    print(nphilo, " picks up fork", lfork);
    print(nphilo, " is thinking...");

    std::this_thread::sleep_for(think_time);
    print(nphilo, " reaches for fork number ", rfork);

    // lock the right fork
    fork_mutex[rfork].lock();

    // success
    print(nphilo, " picks up fork", rfork);
    print(nphilo, " is eating...");
    mouthfuls[nphilo] ++;

    std::this_thread::sleep_for(eat_time);

    print(nphilo, " puts down fork ", lfork);
    print(nphilo, " puts down fork ", rfork);
    print(nphilo, " is thinking...");

    fork_mutex[lfork].unlock();
    fork_mutex[rfork].unlock();
    std::this_thread::sleep_for(think_time);
}


/**
 * @brief try to lock both forks
 * 
 * @param nphilo 
 */
void dine_both_fork(int nphilo) {
    int lfork = nphilo;
    int rfork = (nphilo + 1) % nforks;

    print(nphilo, " \'s forks are ", lfork, rfork);
    print(nphilo, " is thinkng");

    std::this_thread::sleep_for(think_time);

    print(nphilo, "reaches for fork number ", lfork, rfork);

    // each philosohper needss 2 forks to eat

    // lock both of the forks
    std::lock(fork_mutex[lfork], fork_mutex[rfork]);
    print(nphilo, " picks up fork ", lfork, rfork);

    // success
    print(nphilo, " is eating...");
    mouthfuls[nphilo] ++;

    std::this_thread::sleep_for(eat_time);

    print(nphilo, " puts down fork ", lfork, rfork);
    print(nphilo, " is thinking...");

    fork_mutex[lfork].unlock();
    fork_mutex[rfork].unlock();
    std::this_thread::sleep_for(think_time);
}


/**
 * @brief hierarchy lock
 * 
 * @param nphilo 
 */
void dine_hierarchy(int nphilo) {
    int lfork = nphilo;
    int rfork = (nphilo + 1) % nforks;

    print(nphilo, " \'s forks are ", lfork, rfork);
    print(nphilo, " is thinkng");

    // must lock the fork with lower number first
    // to have access to higher number fork
    if (lfork > rfork) { 
        std::swap(lfork, rfork);
    }

    std::this_thread::sleep_for(think_time);

    print(nphilo, " reaches for fork number ", lfork);

    // each philosohper needss 2 forks to eat

    // lock the left fork
    fork_mutex[lfork].lock();
    print(nphilo, " picks up fork", lfork);
    print(nphilo, " is thinking...");

    std::this_thread::sleep_for(think_time);
    print(nphilo, " reaches for fork number ", rfork);

    // lock the right fork
    fork_mutex[rfork].lock();

    // success
    print(nphilo, " picks up fork", rfork);
    print(nphilo, " is eating...");
    mouthfuls[nphilo] ++;

    std::this_thread::sleep_for(eat_time);

    print(nphilo, " puts down left fork ", lfork);
    print(nphilo, " puts down right fork ", rfork);
    print(nphilo, " is thinking...");

    fork_mutex[lfork].unlock();
    fork_mutex[rfork].unlock();
    std::this_thread::sleep_for(think_time);
}