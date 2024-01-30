#include <thread>
#include <iostream>
#include <vector>
#include <cstdio>



void worker(std::vector<int>::iterator begin,
            std::vector<int>::iterator end,
            int* result)
{
    int sum = 0;
    for (auto it = begin; it != end; ++it)
        sum += *it;
    *result = sum;

    std::thread::id this_id = std::this_thread::get_id();

    printf("Thread %d: %d\n", this_id, sum);
}

int main()
{
    std::vector<int> data(10000);

    for (int i = 0; i < data.size(); ++i)
        data[i] = i;


    std::vector<int> partial_sums(4);

    std::vector<std::thread> threads;

    for (int i = 0; i < partial_sums.size(); i++)
    {
        threads.push_back(std::thread(worker,
                                      data.begin() + i * (data.size() / partial_sums.size()),
                                      data.begin() + (i + 1) * (data.size() / partial_sums.size()),
                                      &partial_sums[i]));
    }

    for (auto& thread : threads)
        thread.join();

    int total = 0;

    for (auto& partial_sum : partial_sums)
        total += partial_sum;

    printf("Total: %d\n", total);



}