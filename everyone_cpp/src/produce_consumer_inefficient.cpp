#include <chrono>
#include <iostream>
#include <mutex>
#include <queue>
#include <string>
#include <thread>
#include <vector>


void producer(std::queue<std::string>* download_pages,
              std::mutex* m,
              int index)
{
    for (int i = 0; i < 5; i++)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(100 * index));

        std::string content = "웹사이트 : " + std::to_string(i) + 
            " from thread (" + std::to_string(index) + ")\n";
        
        m->lock();
        download_pages->push(content);
        m->unlock();           
    }
}


void consumer(std::queue<std::string>* download_pages,
              std::mutex* m,
              int* num_processed)
{
    while(*num_processed < 25)
    {
        m->lock();

        if (download_pages->empty())
        {
            m->unlock();

            std::this_thread::sleep_for(std::chrono::milliseconds(10));
            continue;
        }

        std::string content = download_pages->front(); download_pages->pop();

        (*num_processed)++;

        m->unlock();

        std::cout << content;
        std::this_thread::sleep_for(std::chrono::milliseconds(80));
    }
}



int main()
{
    std::queue<std::string> download_pages;
    std::mutex m;

    std::vector<std::thread> producers;
    for (int i = 0; i < 5; i++)
        producers.push_back(std::thread(
            producer,
            &download_pages,
            &m,
            i + 1
        ));

    
    int num_processed = 0;

    std::vector<std::thread> consumers;
    for (int i = 0; i < 3; i++)
        consumers.push_back(std::thread(
            consumer,
            &download_pages,
            &m,
            &num_processed
        ));

    
    
    for (int i = 0; i < 5; i++) producers[i].join();
    for (int i = 0; i < 3; i++) consumers[i].join();

    std::cout << "예제 끝!" << std::endl;

}