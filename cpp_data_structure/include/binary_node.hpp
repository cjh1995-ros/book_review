#pragma once

#include <memory>
#include <iostream>


template<typename T>
struct BinaryNode : public std::enable_shared_from_this<BinaryNode<T>>
{
using ptr = std::shared_ptr<BinaryNode<T>>;
    T data;
    ptr p_left;
    ptr p_right;

    BinaryNode(T d, ptr l, ptr r): data(d), p_left(l), p_right(r) {}
    BinaryNode(T d): data(d), p_left(nullptr), p_right(nullptr) {}
    void set_data(T d) { data = d; }
    void set_left(ptr p_l) { p_left = p_l; }
    void set_right(ptr p_r) { p_right = p_r; }
    T get_data() { return data; }
    ptr get_left() { return p_left; }
    ptr get_right() { return p_right; }
    bool is_leaf() { return ( p_left == nullptr && p_right == nullptr); }

    void preorder()
    {
        std::cout << data << " ";
        if (p_left != nullptr) p_left->preorder();
        if (p_right != nullptr) p_right->preorder();
    }

    void inorder()
    {
        if (p_left != nullptr) p_left->inorder();
        std::cout << data << " ";
        if (p_right != nullptr) p_right->inorder();
    }

    void postorder()
    {
        if (p_left != nullptr) p_left->postorder();
        if (p_right != nullptr) p_right->postorder();
        std::cout << data << " ";
    }
};
