#include <iostream>
#include <string>
#include <vector>
#include <mutex>
#include <condition_variable>
#include <thread>
#include <queue>
#include <chrono>



void producer(std::queue<std::string>* download_pages,
              std::mutex* m,
              int index,
              std::condition_variable* cv)
{
    for (int i = 0; i < 5; i++)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(100 * index));
        std::string content = "웹사이트: " + std::to_string(i) +
            " from thread (" + std::to_string(index) + ")\n";
        
        m->lock();
        download_pages->push(content);
        m->unlock();

        cv->notify_one();
    }
}



void consumer(std::queue<std::string>* download_content,
              std::mutex* m,
              int* num_processed,
              std::condition_variable* cv)
{
    while (*num_processed < 25)
    {
        std::unique_lock<std::mutex> lk(*m);

        // 기다리는 조건 삽입
        cv->wait(
            lk, [&] { return !download_content->empty() ||
                      *num_processed == 25; }
        );

        if (*num_processed == 25)
        {
            lk.unlock();
            return;
        }

        std::string content = download_content->front();
        download_content->pop();

        (*num_processed)++;
        lk.unlock();

        std::cout << content;
        std::this_thread::sleep_for(std::chrono::milliseconds(80));
    }
}




int main()
{
    std::queue<std::string> downloads;
    std::mutex m;
    std::condition_variable cv;

    std::vector<std::thread> producers;
    for (int i = 0; i < 5; i++)
        producers.push_back(std::thread(
            producer,
            &downloads,
            &m,
            i,
            &cv
        ));


    int num_processed = 0;

    std::vector<std::thread> consumers;
    for (int i = 0; i < 3; i++)
        consumers.push_back(std::thread(
            consumer,
            &downloads,
            &m,
            &num_processed,
            &cv
        ));

    
    for (int i = 0; i < 5; i++) producers[i].join();

    cv.notify_all();

    for (int i = 0; i < 3; i++) consumers[i].join();

    std::cout << "끝" << std::endl;
}