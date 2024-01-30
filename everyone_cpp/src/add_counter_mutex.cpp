#include <thread>
#include <mutex>
#include <vector>
#include <iostream>



void worker(int& counter, std::mutex& m)
{
    for (int i = 0; i < 10000; i++)
    {
        // m.lock();
        // counter++;
        // m.unlock();
        // 위 아래 동일한 효과
        std::lock_guard<std::mutex> lock(m);
        counter++;
    }
}


int main()
{
    int counter = 0;

    std::vector<std::thread> workers;
    std::mutex counter_mutex;

    for (int i = 0; i < 4; i++)
        workers.push_back(std::thread(
            worker,
            std::ref(counter),
            std::ref(counter_mutex)
        ));

    
    for (int i = 0; i < 4; i++)
        workers[i].join();

    
    std::cout << "Final count: " << counter << std::endl;
}