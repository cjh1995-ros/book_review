#pragma once

#include "binary_node.hpp"
#include "binary_tree.hpp"


template<typename T>
class BinarySearchTree : public BinaryTree<T>
{
using node_type = BinaryNode<T>;
using ptr = std::shared_ptr<node_type>;
public:
    BinarySearchTree(): BinaryTree<T>() {}

    // 탐색 연산
    ptr search(T key) { return search(this->root_, key); }
    ptr search(ptr node, T key)
    {
        if (node == nullptr) return nullptr;
        if (node->data == key) return node;
        ptr next = node->data > key ? node->p_left : node->p_right;
        return search(next, key);
    }
    ptr search_itr(T key) { return search_itr(this->root_, key); }
    ptr search_itr(ptr node, T key)
    {
        while (node != nullptr)
        {
            if (node->data == key)  return node;
            if (node->data > key)   node = node->p_left;
            else                    node = node->p_right;
        }
        return nullptr;
    }

    // 삽입 연산
    void insert(ptr node) { return insert(this->root_, node); }
    void insert(ptr r, ptr node)
    {   
        if (node->data == r->data) return;
        else if (node->data > r->data) 
        {
            if (r->get_right() == nullptr) r->set_right(node);
            else insert(r->p_right, node);
        }        
        else
        {
            if (r->get_left() == nullptr) r->set_left(node);
            else insert(r->p_left, node);
        }
    }

    // 삭제 연산. find parent
    void remove(T key)
    {
        if (this->is_empty()) return ;

        ptr parent = nullptr;
        ptr node = this->root_;

        while (node != nullptr && node->get_data() != key)
        {
            parent = node;
            node = (key < node->get_data())
                ? node->get_left() : node->get_right();
        }

        if (node == nullptr) return;
        remove(parent, node);
    }
    void remove(ptr parent, ptr node)
    {
        // case 1: 단말 노드 삭제 경우
        if (node->is_leaf())
        {   
            // node == root_ 노드인 경우 root -> null => 공백상태 만듬.
            if (parent == nullptr)  this->root_.reset();
            else 
            {
                if (parent->get_left() == node) parent->set_left(nullptr);
                else parent->set_right(nullptr);
            }
        }

        // case 2: 삭제하려는 노드가 왼쪽이나 오른쪽 자식만 갖는 경우
        else if (node->get_left() == nullptr || node->get_right() == nullptr)
        {
            ptr child = (node->get_left() != nullptr) ? node->get_left() : node->get_right();
            if (node == this->root_) this->root_ = child;
            else
            {
                if (parent->get_left() == node) parent->set_left(child);
                else                            parent->set_right(child);
            }
        }

        // case 3: 삭제하려는 노드가 두개의 자식이 모두 있는 경우
        else
        {
            // 삭제하려는 오른쪽 서브트리에서 가장 작은 노드를 탐색
            ptr succp = node;
            ptr succ = node->get_right();
            
            while(succ->get_left() != nullptr)
            {
                succp = succ;
                succ = succ->get_left();
            }

            // 후계 노드의 부모와 후계 노드의 오른쪽 자식을 직접 연결
            if (succp->get_left() == succ) succp->set_left(succ->get_right());
            else succp->set_right(succ->get_right());

            node->set_data(succ->get_data());
            node = succ;
        }
        node.reset();
    }
};