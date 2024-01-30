#include <thread>
#include <iostream>

constexpr int COUT_NUM = 10;

void func1()
{
    for (int i = 0; i < COUT_NUM; ++i)
        std::cout << "Thread1: " << i << std::endl;
}


void func2()
{
    for (int i = 0; i < COUT_NUM; ++i)
        std::cout << "Thread2: " << i << std::endl;
}


void func3()
{
    for (int i = 0; i < COUT_NUM; ++i)
        std::cout << "Thread3: " << i << std::endl;
}


int main()
{

    std::thread t1(func1);
    std::thread t2(func2);
    std::thread t3(func3);

    t1.join();
    t2.join();
    t3.join();

    return 0;
}