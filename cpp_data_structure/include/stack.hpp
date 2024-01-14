#pragma once 

#include <iostream>

constexpr int MAX_ARRAY_SIZE = 100;

class ArrayStack
{
private:
    int top_;
    int data_[MAX_ARRAY_SIZE];

public:
    ArrayStack() { top_ = -1; }
    ~ArrayStack() {};

    bool isEmpty() { return top_ == -1;}
    bool isFull() { return top_ == MAX_ARRAY_SIZE - 1; }

    void push(int data)
    {
        if (isFull()) std::cout << "Stack is full" << std::endl;
        else data_[++top_] = data;
    }

    int pop()
    {
        if (isEmpty()) std::cout << "Stack is empty" << std::endl;
        else return data_[top_--];
    }
    
    // 삭제하지 않고 값 반환
    int peek()
    {
        if (isEmpty()) std::cout << "Stack is empty" << std::endl;
        else return data_[top_];
    }

    void print(bool from_top = true)
    {
        std::cout << "N in stack: " << top_ + 1 << std::endl;

        if (from_top)
        {
            for (int i = top_; i >= 0; i--)
                std::cout << "[" << i << "] " << data_[i] << std::endl;
        } else 
        {
            for (int i = 0; i < top_; i++)
                std::cout << "[" << i << "] " << data_[i] << std::endl;
        }
    }
};
