#include <atomic>
#include <thread>
#include <iostream>
#include <vector>


struct CustomData
{
    int x;
    int y;
    int z;
    float xyz;
};

void worker(std::atomic<int>& c)
{
    for (int i = 0; i < 10000; i++)
        c++;
}


void t1(std::atomic<int>* a, std::atomic<int>* b)
{
    b->store(1, std::memory_order_relaxed);
    int x = a->load(std::memory_order_relaxed);

    printf("x: %d \n", x);
}

void t2(std::atomic<int>* a, std::atomic<int>* b)
{
    a->store(1, std::memory_order_relaxed);
    int y = b->load(std::memory_order_relaxed);

    printf("y: %d \n", y);
}

int main()
{
    // std::atomic<int> count = 0;
    // std::atomic<CustomData> test;

    // std::cout << "Is atomic possible for (int)?: " << count.is_lock_free() << std::endl;
    // std::cout << "Is atomic possible for (CustomData)?: " << test.is_lock_free() << std::endl;


    // std::vector<std::thread> workers;
    // for (int i = 0; i < 4; i++)
    //     workers.push_back(std::thread(
    //         worker,
    //         std::ref(count)
    //     ));
    

    // for (int i = 0; i < 4; i++)
    //     workers[i].join();
    
    // std::cout << "Final: " << count << std::endl;


    /////////////////////

    std::atomic<int> a(0);
    std::atomic<int> b(0);

    std::vector<std::thread> threads;

    threads.push_back(std::thread(t1, &a, &b));
    threads.push_back(std::thread(t2, &a, &b));

    threads[0].join();
    threads[1].join();



}