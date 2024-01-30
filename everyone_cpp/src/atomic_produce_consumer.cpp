//**
 * File: atomic_produce_consumer.cpp
 * Author: Jun Hyeok Choi, dkwnsgur12@gmail.com
 * Date: 2024-01-30
 * Copyright (c) 2024 Jun Hyeok Choi. All rights reserved.
 * Description: 
 * std::memory_order_relaxed: 빠르지만 읽는 CPU가 읽는 순서를
 * 위 아래 문장과 바꿀 수 있기에 비추.
 * std:: 
 */

#include <atomic>
#include <thread>
#include <vector>
#include <iostream>


void producer(std::atomic<bool>* is_ready, int* data)
{
    *data = 10;
    is_ready->store(true, std::memory_order_relaxed);
}

void consumer(std::atomic<bool>* is_ready, int* data)
{
    while(!is_ready->load(std::memory_order_relaxed)) {}

    std::cout << "Data: " << *data << std::endl;
}

int main()
{
    std::atomic<bool> is_ready(false);
    int data = 0;


    std::thread p(producer, &is_ready, &data);
    std::thread c(consumer, &is_ready, &data);

    p.join();
    c.join();
}