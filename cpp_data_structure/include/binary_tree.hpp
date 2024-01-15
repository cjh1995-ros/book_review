#pragma once

#include "binary_node.hpp"
#include <memory>
#include <iostream>
#include <queue>




template <typename T>
class BinaryTree
{
using ptr = std::shared_ptr<BinaryNode<T>>;

private:
    int height_;
    ptr root_;
public:
    BinaryTree(): root_(nullptr) {}
    void set_root(ptr node) { root_ = node; }
    ptr get_root() { return root_; }
    bool is_empty() { return root_ == nullptr; }
    
    
    void inorder() { if (root_ != nullptr) root_->inorder(); }
    void inorder(ptr node)
    {
        if (node != nullptr)
        {
            inorder(node->p_left);
            std::cout << node->data << " ";
            inorder(node->p_right);
        }
    }
    

    void preorder() { if (root_ != nullptr) root_->preorder(); }
    void preorder(ptr node)
    {
        if (node != nullptr)
        {
            std::cout << node->data << " ";
            preorder(node->p_left);
            preorder(node->p_right);
        }
    }

    void postorder() { if (root_ != nullptr) root_->postorder(); }
    void postorder(ptr node)
    {
        if (node != nullptr)
        {
            postorder(node->p_left);
            postorder(node->p_right);
            std::cout << node->data << " ";
        }
    }
    
    
    void levelorder()
    {
        std::queue<ptr> q_ptr;
        q_ptr.push(root_);

        while (!q_ptr.empty())
        {
            ptr p = q_ptr.front();
            q_ptr.pop();

            std::cout << p->data << " ";

            if (p->p_left != nullptr) q_ptr.push(p->p_left);
            if (p->p_right != nullptr) q_ptr.push(p->p_right);
        }
    }

    
    int get_count() { return is_empty() ? 0 : get_count(root_); }
    int get_count(ptr node)
    {
        if (node == nullptr) return 0;
        else return 1 + get_count(node->p_left) + get_count(node->p_right);
    }

    
    int get_leaf_count() { return is_empty() ? 0 : get_leaf_count(root_); }
    int get_leaf_count(ptr node)
    {
        if (node == nullptr) return 0;
        else if (node->is_leaf()) return 1;
        else return get_leaf_count(node->p_left) + get_leaf_count(node->p_right);
    }


    int get_height() { return is_empty() ? 0 : get_height(root_); }
    int get_height(ptr node)
    {
        if (node == nullptr) return 0;
        int h_left  = get_height(node->p_left);
        int h_right = get_height(node->p_right);
        return h_left > h_right ? h_left + 1 : h_right + 1;
    }
};