#pragma once

#include <iostream>

constexpr int MAX_QUEUE_SIZE = 100;

class CircularQueue
{
protected:
    int front;
    int rear;
    int data[MAX_QUEUE_SIZE];
public:
    CircularQueue() { front = rear = 0; }
    bool is_empty() { return front == rear; }
    bool is_full() { return front == (rear + 1) % MAX_QUEUE_SIZE; }
    
    void enqueue(int d)
    {
        if (is_full()) std::cout << "Queue is full now!" << std::endl;
        else
        {
            rear += 1;
            data[rear] = d;
        }
    }
    
    int dequeue()
    {
        if (is_empty()) std::cout << "Queue is empty now!" << std::endl;
        else 
        {
            front = (front + 1) % MAX_QUEUE_SIZE;
            return data[front];
        }
    }
    
    int peek()
    {
        if (is_empty()) std::cout << "Queue is empty now!" << std::endl;
        else return data[(front + 1) % MAX_QUEUE_SIZE];
    }
    
    virtual void print() 
    {
        int maxi = front < rear ? rear : rear + MAX_QUEUE_SIZE;

        for ( int i = front + 1; i < maxi; i++)
            std::cout << data[i % MAX_QUEUE_SIZE] << " ";
        std::cout << std::endl;
    }
};




class CircularDeque: public CircularQueue
{
public:
    CircularDeque() = default;

    void add_rear(int val) { enqueue(val); }
    int delete_front() { return dequeue(); }
    int get_front() { return peek(); }
    
    void add_front(int val)
    {
        if (is_full()) std::cout << "Queue is full now!" << std::endl;
        else
        {
            data[front] = val;
            front = (front - 1 + MAX_QUEUE_SIZE) % MAX_QUEUE_SIZE;
        }
    }

    int delete_rear()
    {
        if (is_empty()) std::cout << "Queue is empty now!" << std::endl;
        else 
        {
            int ret = data[rear];
            rear = (rear - 1 + MAX_QUEUE_SIZE) % MAX_QUEUE_SIZE;
            return ret;
        }
    }

    int get_rear()
    {
        if (is_empty()) std::cout << "Queue is empty now!" << std::endl;
        else return data[rear];
    }

    void print() override
    {
        std::cout << "Print Queue" << std::endl;

        int maxi = front < rear ? rear : rear + MAX_QUEUE_SIZE;

        for (int i = front + 1; i <= maxi; i++)
            std::cout << data[i % MAX_QUEUE_SIZE] << " ";
        std::cout << std::endl;
    }
};