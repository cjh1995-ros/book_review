#pragma once

#include <string>
#include <iostream>
#include <memory>





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





class Node: public Student
{
private:    
    std::shared_ptr<Node> next_;
public:
    Node(int id_, std::string n_, std::string dp_)
        : Student(id_, n_, dp_) { next_ = nullptr; }
    ~Node(){}

    std::shared_ptr<Node> get_next() { return next_; }
    void set_next(std::shared_ptr<Node> n) { next_ = n; }
};





class LinkedStack
{
private:
    std::shared_ptr<Node> top_;

public:
    LinkedStack() { top_ = nullptr; }
    ~LinkedStack() {}

    bool is_empty() { return top_ == nullptr; }

    void push(const Student& s)
    {
        std::shared_ptr<Node> new_node = std::make_shared<Node>(s.id, s.name, s.dept);
        // std::cout << "Address of new node: " << new_node.get() << std::endl;
        // std::cout << "Address of next new node: " << new_node->get_next().get() << std::endl;

        if (is_empty()) top_ = new_node;
        else 
        {
            // std::cout << "Address of top: " << top_.get() << std::endl;
            new_node->set_next(top_);    
            top_ = new_node;
            // std::cout << "Address of top: (new node add)" << top_.get() << std::endl;
            // std::cout << "Address of top next (prev top): " << top_->get_next().get() << std::endl;
        }
    }

    std::shared_ptr<Node> pop()
    {
        if (is_empty()) return nullptr;
        
        std::shared_ptr<Node> p = top_;

        top_ = top_->get_next();

        return p;
    }

    std::shared_ptr<Node> peek() { return top_; }

    void print()
    {
        std::cout << "Show Linked Stack Contents" << std::endl;

        auto n = top_;

        while (n != nullptr)
        {
            std::cout << "Name: " << n->name << std::endl;
            std::cout << "ID: " << n->id << std::endl;
            std::cout << "Dept: " << n->dept << std::endl;
            n = n->get_next();
        }
    }
};





class LinkedQueue
{
private:
    std::shared_ptr<Node> front_;
    std::shared_ptr<Node> rear_;
public:
    LinkedQueue(): front_(nullptr), rear_(nullptr) {}
    ~LinkedQueue(){}

    bool is_empty() { return front_ == nullptr; }

    void enqueue(const Student& s)
    {
        std::shared_ptr<Node> new_node = std::make_shared<Node>(s.id, s.name, s.dept);

        if (is_empty())
        {
            front_ = new_node;
            rear_ = new_node;
        }
        else
        {
            rear_->set_next(new_node);
            rear_ = new_node;
        }
    }

    std::shared_ptr<Node> dequeue()
    {
        if (is_empty()) return nullptr;
        std::shared_ptr<Node> ret = front_;
        front_ = ret->get_next();

        if (front_ == nullptr) rear_ = nullptr;

        return ret;
    }

    std::shared_ptr<Node> peek() { return front_; }
    
    void print()
    {
        std::cout << "Print Student Queue Contents" << std::endl;

        auto n = front_;

        while (n != nullptr)
        {
            std::cout << "Name: " << n->name << std::endl;
            std::cout << "ID: " << n->id << std::endl;
            std::cout << "Dept: " << n->dept << std::endl;
            n = n->get_next();
        }
    }

};