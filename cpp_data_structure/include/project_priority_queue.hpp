/**
 * File: project_priority_queue.hpp
 * Author: Jun Hyeok Choi, dkwnsgur12@gmail.com
 * Date: 2024-01-19
 * Copyright (c) 2024 Jun Hyeok Choi. All rights reserved.
 * Description: 
 * 힙 데이터 구조는 인덱스가 부모와 자식을 나타낸다는 것을 핵심으로 생각하자!
 */
#pragma once 

#include <iostream>
#include <queue>
#include <vector>
#include <memory>




struct HeapNode
{
    int key;

    HeapNode(): key(-1) {};
    HeapNode(int k): key(k) {}

    int     get_key() { return key; }
    void    set_key(int k) { key = k; }
    void    display() { printf("%d ", key); }

    bool    is_valid() { return key != -1; }
};



constexpr int MAX_HEAP_SIZE = 100;

class MaxHeap
{
private:
    HeapNode    nodes_[MAX_HEAP_SIZE];
    int         size_;
public:
    MaxHeap(): size_(0) {}
    bool is_empty() { return size_ == 0; }
    bool is_full() { return size_ == MAX_HEAP_SIZE - 1; }

    HeapNode& get_parent(int i) { return nodes_[i/2]; }
    HeapNode& get_left(int i) { return nodes_[2*i]; }
    HeapNode& get_right(int i) { return nodes_[2*i+1]; }


    /// @brief 맨 마지막에 요소 삽입 후 이를 부모와 비교하며 key가 더 크면 인덱스를 바꾸고
    /// 작으면 끝낸다.
    void insert(int k)
    {
        if (is_full())
        {
            printf("Can't insert key %d cz full!\n", k);
            return;
        }

        int i = ++size_;

        while (i != 1 && k > get_parent(i).get_key())
        {
            nodes_[i] = get_parent(i);
            i /= 2;
        }
        nodes_[i].set_key(k);        
    }



    HeapNode remove()
    {
        if (is_empty())
        {
            printf("This is empty now\n");
            return HeapNode();
        }
        
        HeapNode top = nodes_[1];
        HeapNode last = nodes_[size_--];

        int parent  = 1;
        int child   = 2;

        while (child <= size_)
        {
            if (child < size_ &&
                get_left(parent).get_key() < get_right(parent).get_key())
                child++;
            
            if (last.get_key() >= nodes_[child].get_key()) break;

            nodes_[parent] = nodes_[child];
            
            parent = child;
            child *= 2;
        }

        nodes_[parent] = last;
        
        return top;        
    }



    /// @brief 힙이 왼쪽 오른쪽 정렬이 안되어 있어서. 사실상 찾는거는 
    /// 내부 메모리를 그냥 쭉 돌아다녀야할듯?
    HeapNode find(int k)
    {
        if (is_empty()) return HeapNode();

        for (int i = 1; i <= size_; i++)
        {
            if (k == nodes_[i].get_key())
                return nodes_[i];
        }

        printf("There is no value in this heap\n");

        return HeapNode();
    }



    void display()
    {
        int i = 1;

        for (int i = 1, level = 1; i <= size_; i++)
        {
            if (i == level) 
            {
                printf("\n");
                level *= 2;
            }
                nodes_[i].display();
        }
    }
};





class MinHeap
{
private:
    HeapNode    nodes_[MAX_HEAP_SIZE];
    int         size_;
public:
    MinHeap(): size_(0) {}

    void    create(std::vector<int> leafs)
    {

    }

    bool    is_empty() { return size_ == 0; }
    bool    is_full() { return size_ == MAX_HEAP_SIZE - 1; }

    HeapNode& get_parent(int i) { return nodes_[i / 2]; }
    HeapNode& get_left(int i) { return nodes_[2 * i]; }
    HeapNode& get_right(int i) { return nodes_[2 * i + 1]; }

    void insert(int k)
    {
        if (is_full()) return;

        int i = ++size_;

        while (i != 1 && k < get_parent(i).get_key())
        {
            nodes_[i] = get_parent(i);  // 부모로 바꾸고
            i /= 2;                     // 부모 노드 인덱스로 감
        }

        nodes_[i] = k;
    }
    

    HeapNode remove()
    {
        if (is_empty()) return HeapNode();

        HeapNode top    = nodes_[1];
        HeapNode last   = nodes_[size_--];

        int parent  = 1;
        int child   = 2;

        while (child <= size_)
        {
            // 어느쪽 child 랑 비교할까.
            if (get_left(parent).get_key() > get_right(parent).get_key())
                child++;
            
            // 조건 만족하면?
            if (last.get_key() <= nodes_[child].get_key()) break;

            nodes_[parent] = nodes_[child];

            parent = child;
            child *= 2;
        }

        nodes_[parent] = last;

        return top;
    }

    void display()
    {
        int i = 1;

        for (int i = 1, level = 1; i <= size_; i++)
        {
            if (i == level) 
            {
                printf("\n");
                level *= 2;
            }
                nodes_[i].display();
        }
    }    
};





struct MinNode : public std::enable_shared_from_this<MinNode>
{
using ptr = std::shared_ptr<MinNode>;
    int data;
    ptr next;

    MinNode() = default;
    MinNode(int d, ptr n = nullptr): data(d), next(n) {}

    void set_data(int d) { data = d; }
    int get_data() { return data; }
    void set_next(ptr n) { next = n; }
    ptr get_next() { return next; }

    void display() { printf("%d ", data); }

    void insert(ptr node)
    {
        if (node->get_data() > get_data())
        {
            // 다음이 있고 다음꺼보다 큼 => 다음 노드에서 insert함.
            if (get_next() != nullptr 
                && node->get_data() > get_next()->get_data())
                get_next()->insert(node);
            // 여기에 insert 해야함 => 다음 노드에서 insert함.
            else if (get_next() != nullptr
                && node->get_data() < get_next()->get_data())
            {
                node->set_next(get_next());
                set_next(node);
            }
            // 아예 nullptr 임.
            else if (get_next() == nullptr)
                set_next(node);

            return ;
        }
    }

    // 내 앞에 넣을거냐 뒤에 넣을거냐
    // void insert_prev(ptr node)
    // {
    //     if (node == nullptr)
    //     {
    //         printf("This node is impossible....\n");
    //         return;
    //     }
    //     get_prev()->set_next(node);
    //     set_prev(node);

    //     node->set_prev(get_prev());
    //     node->set_next(shared_from_this());
    // }
    // void insert_next(ptr node)
    // {
    //     if (node == nullptr)
    //     {
    //         printf("This node is impossible....\n");
    //         return;
    //     }

    //     // next에서 판단하기
    //     if (get_next() != nullptr) get_next()->insert_next(node);
    //     // next가 없으면 next를 세팅함.
    //     else if (get_next() == nullptr)
    //     {
    //         set_next(node);
    //         node->set_prev(shared_from_this());
    //     }
    //     else return;
    // }

    // void insert(ptr node)
    // {
    //     if (node == nullptr)
    //     {
    //         printf("This node is nullptr....\n");
    //         return;
    //     }
        
    //     // case 1. prev에 삽입
    //     if (node->get_data() < get_data())
    //     {
    //         printf("Insert to prev, (new, now) = (%d, %d)\n", 
    //             node->get_data(), get_data());
    //         // 이전 노드의 next와 새로운 노드 연결.
    //         get_prev()->set_next(node);
    //         // 내 prev와 새로운 노드 연결.
    //         set_prev(node);
    //         // 새로운 노드의 prev와 next를 연결
    //         node->set_prev(get_prev());
    //         node->set_next(shared_from_this());
            
    //         printf("After insertion to prev, (new, now) = (%d, %d)\n", 
    //             node->get_data(), get_data());
    //         printf("after_insertion (new, now) = (%d, %d)\n", 
    //             node.get(), this);
    //         printf("Address (prev, now) = (%d)\n", 
    //             get_prev().get());
    //     }
    //     // case 2. next에 삽입
    //     else if (node->get_data() > get_data())
    //     {
    //         printf("Insert to next\n");
    //         // next가 있으면 다음 노드가 판단하도록 함.
    //         if (get_next() != nullptr) get_next()->insert(node);
    //         // next가 없으면 next를 세팅함.
    //         else
    //         {
    //             set_next(node);
    //             node->set_prev(shared_from_this());
    //         }
    //     }
    //     // case 3. 동일한 값 지님 -> 그냥 삽입 안함.
    //     return;
        // // next에 삽입
        // if (k > data) 
        // {
        //     if (next != nullptr) next->insert(k);
        //     else 
        //     {
        //         ptr new_next = std::make_shared<MinNode>(k);
        //         set_next(new_next);
        //         new_next->set_prev(shared_from_this());
        //     }
        // }
        // // prev에 삽입
        // else if (k < data)
        // {
        //     ptr new_prev = std::make_shared<MinNode>(k);

        //     new_prev->set_next(shared_from_this());
        //     new_prev->set_prev(prev);
        //     set_prev(new_prev);
        //     prev->set_next(new_prev);
        // }
        // else return;
    // }
};






/// @brief 정렬된 연결 리스트 가정
class MinPriorityQueueLList
{
using ptr = std::shared_ptr<MinNode>;    
private:
    ptr min_;
    int size_;
public:
    MinPriorityQueueLList(): size_(0) { min_ = std::make_shared<MinNode>(-1); }

    bool is_empty() { return size_ == 0; }


    void insert(int k)
    {
        ptr node = std::make_shared<MinNode>(k);

        if (k < 0) 
        {
            printf("Minus is invalid value");
            return;
        }

        ++size_;
        min_->insert(node);

        return;
    }

    ptr remove()
    {
        // 사이즈 줄이고
        --size_;
        // 맨 앞 데이터
        ptr item = min_->get_next();

        min_->set_next(item->get_next());
        
        return item;
    }

    void display()
    {
        ptr start = min_->get_next();
        std::cout << "Size: " << size_ << std::endl;

        for (int i = 0; i < size_; i++)
        {
            start->display();
            start = start->get_next();
        }
            
    }
};