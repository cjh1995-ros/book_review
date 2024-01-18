#pragma once

#include <vector>
#include <iostream>
#include <memory>


constexpr int MAX_LIST = 100;


class Node : public std::enable_shared_from_this<Node>
{
using ptr = std::shared_ptr<Node>;
private:
    int id_;
    ptr next_;
public:
    Node(int id, ptr n = nullptr): id_(id), next_(n) {}
    int get_id() { return id_; }
    ptr get_link() { return next_; }
    void set_link(ptr n) { next_ = n; }
};


class AdjListGraph
{
using ptr = std::shared_ptr<Node>;
protected:
    int     size_;
    char    vertices_[MAX_LIST];
    ptr     adj_[MAX_LIST];
public:
    AdjListGraph() : size_(0) {}

    void reset()
    {
        for (int i = 0; i < size_; i++)
            if (adj_[i] != nullptr) adj_[i].reset();
        size_ = 0;
    }

    bool is_empty() { return size_ == 0; }
    bool is_full() { return size_ == MAX_LIST; }
    char get_vertex(int i) { return vertices_[i]; }

    void insert_vertex(char val)
    {
        if (!is_full())
        {
            vertices_[size_] = val;
            adj_[size_++] = nullptr;
        }
        else std::cout << "Out of range" << std::endl;
    }

    void insert_edge(int u, int v)
    {
        // 여기엔 없지만, 일단 edge가 안에 있는지 확인부터 해야할 듯.
        adj_[u] = std::make_shared<Node>(v, adj_[u]); // node = v 값을 갖고 next 가 node인 node1 생성
        adj_[v] = std::make_shared<Node>(u, adj_[v]);
    }

    void display()
    {
        std::cout << "Size: " << size_ << std::endl;
        for (int i = 0; i < size_; i++)
        {
            std::cout << "Vertex " << vertices_[i] << " ";
            for ( ptr n = adj_[i]; n != nullptr; n = n->get_link())
                std::cout << get_vertex(n->get_id());
            std::cout << std::endl;
        }
    }

    ptr adjacent(int v) { return adj_[v]; }
};