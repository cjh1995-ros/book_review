#pragma once

#include <iostream>
#include <string>


constexpr int MAX_STACK_SIZE = 100;


struct Student
{
    int id;
    std::string name;
    std::string dept;

    Student() = default;
    Student(int id_, std::string name_, std::string dept_)
        : id(id_), name(name_), dept(dept_) {}
    
    void print()
    {
        std::cout << "id: " << id << std::endl;
        std::cout << "name: " << name << std::endl;
        std::cout << "dept: " << dept << std::endl;
    }
};

class StudentStack
{
private:
    Student stack_[MAX_STACK_SIZE];
    int top_;

public:
    StudentStack() : top_(-1) {}

    bool isFull() { return top_ == MAX_STACK_SIZE - 1; }
    bool isEmpty() { return top_ == -1; }

    void push(Student s)
    {
        if (isFull()) std::cout << "Stack is full" << std::endl;
        else stack_[++top_] = s;
    }

    Student pop()
    {
        if (isEmpty()) std::cout << "Stack is Empty" << std::endl;
        else return stack_[top_--];
    }

    Student peek()
    {
        if (isEmpty()) std::cout << "Stack is Empty" << std::endl;
        else return stack_[top_];
    }

    void print()
    {
        std::cout << "Show Stack List" << std::endl;

        for (int i = 0; i < top_; i++)
            stack_[i].print();
    }
};