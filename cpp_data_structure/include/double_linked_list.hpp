#pragma once


#include <iostream>
#include <memory>


struct Node2: public std::enable_shared_from_this<Node2>
{
    std::shared_ptr<Node2> next;
    std::shared_ptr<Node2> prev;
    int data;

    Node2(): next(nullptr), prev(nullptr), data(0) {}
    Node2(int d): next(nullptr), prev(nullptr), data(d) {}
    
    // Don't need get or set cz its struct
    void print()
    {
        std::cout << "Data: " << data << std::endl;
    }

    bool has_data(int d) { return data == d; }

    void insert_next(std::shared_ptr<Node2> n)
    {
        if (n != nullptr)
        {
            n->prev = shared_from_this();
            n->next = next;
            if (next != nullptr) next->prev = n;
            next = n;
        }
    }

    // 현재 노드를 연결 리스트에서 제거.
    std::shared_ptr<Node2> remove()
    {
        if (prev != nullptr) prev->next = next;
        if (next != nullptr) next->prev = prev;
        return std::shared_ptr<Node2>(this);
    }
};


class DBLinkedList
{
private:
    std::shared_ptr<Node2> head_;

public:
    DBLinkedList()
    {
        head_ = std::make_shared<Node2>(0);
        std::cout << "Head point address: " << head_.get() << std::endl;
        std::cout << "prev address: " << head_->prev.get() << std::endl;
        std::cout << "next address: " << head_->next.get() << std::endl;
    }
    std::shared_ptr<Node2> get_head() { return head_; }
    bool is_empty() { return head_ == nullptr; }

    std::shared_ptr<Node2> get_entry(int position)
    {
        std::shared_ptr<Node2> cursor = head_;
        for (int i = -1; i < position; i++, cursor = cursor->next)
            if (cursor == nullptr) break;
        return cursor;
    }

    void insert(int pos, std::shared_ptr<Node2> n)
    {
        auto cursor = get_entry(pos - 1);
        if (cursor != nullptr)  cursor->insert_next(n);
    }

    std::shared_ptr<Node2> remove(int pos)
    {
        auto cursor = get_entry(pos);
        return cursor->remove();
    }

    std::shared_ptr<Node2> find(int val)
    {
        auto cursor = head_;

        int idx = 0;

        while (cursor != nullptr)
        {
            if (cursor->data == val) 
            {
                std::cout << "Find the value in idx " << idx << std::endl;
                return cursor;
            }
            cursor = cursor->next;
            idx++;
        }
        std::cout << "Can't find the value in list " << std::endl;
        return nullptr;
    }

    void print()
    {
        auto cursor = head_;
        while (cursor != nullptr)
        {
            std::cout << "DATA: " << cursor->data << std::endl;
            cursor = cursor->next;
        }
    }


};