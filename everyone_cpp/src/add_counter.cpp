#include <thread>
#include <iostream>
#include <vector>


void worker(int& counter)
{
    for (int i = 0; i < 10000; i++)
        counter++;
}





int main()
{
    int counter = 0;

    std::vector<std::thread> workers;

    for (int i = 0; i < 4; i++)
        workers.push_back(std::thread(
            worker,
            std::ref(counter)
        ));
    
    for (int i = 0; i < 4; i++)
        workers[i].join();

    std::cout << "Final counter: " << counter << std::endl;
}