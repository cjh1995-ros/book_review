#include "dispatcher.h"
#include "request.h"


#include <iostream>
#include <string>
#include <csignal>
#include <thread>
#include <chrono>



sig_atomic_t signal_caught = 0;
std::mutex log_mutex;

void sigint_handler(int sig) { signal_caught = 1; }
void log_fnc(std::string text)
{
    log_mutex.lock();
    std::cout << text << "\n";
    log_mutex.unlock();
}




int main()
{
    signal(SIGINT, &sigint_handler);
    Dispatcher::init(10);

    std::cout << "Initialised. \n";
    int cycles = 0;
    
    Request* rq = nullptr;

    while (!signal_caught && cycles < 50)
    {
        rq = new Request();
        rq->set_value(cycles);
        rq->set_output(&log_fnc);
        Dispatcher::add_request(rq);
        cycles++;
    }

    std::this_thread::sleep_for(std::chrono::seconds(5));
    Dispatcher::stop();

    std::cout << "Clean-up done.\n";
    return 0;
}