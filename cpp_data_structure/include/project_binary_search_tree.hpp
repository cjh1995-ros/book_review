#pragma once

#include <memory>
#include <queue>






struct Node : public std::enable_shared_from_this<Node>
{
using ptr = std::shared_ptr<Node>;    
    int data;
    ptr left;
    ptr right;

    Node(int d, ptr l = nullptr, ptr r = nullptr): data(d), left(l), right(r) {}

    // setter and getter
    void set_data(int d) { data = d; }
    int get_data() { return data; }

    void set_left(ptr l) { left = l;}
    ptr get_left() { return left; }
    
    void set_right(ptr r) { right = r; }
    ptr get_right() { return right; }

    bool is_leaf() { return left == nullptr && right == nullptr; }
    
    bool is_child(ptr cand_child)
    {
        if (is_leaf()) return false;
        if (cand_child == nullptr) return false;
        return (left == cand_child || right == cand_child);
    }

    ptr search(int key)
    {
        if (key == data) return shared_from_this();
        else if (key < data) left->search(key);
        else if (key > data) right->search(key);
        return nullptr;
    }
    ptr search(ptr node)
    {
        if (node.get() == this && node->get_data() == data) 
            return shared_from_this();
        else if (node->get_data() < data) left->search(node);
        else if (node->get_data() > data) right->search(node);
        return nullptr;
    }

    void insert(int key)
    {
        if (key == data)
        {
            printf("Can't insert same value %d", key);
            return;
        }
        
        if (key < data)
        {
            if (left == nullptr) left = std::make_shared<Node>(key);
            else left->insert(key);
        } 
        else
        {
            if (right == nullptr) right = std::make_shared<Node>(key);
            else right->insert(key);
        }
    }
    void insert(ptr node)
    {
        if (node->get_data() == data || node.get() == this)
        {
            printf("Can't insert same value %d", node->get_data());
            return;
        }
        
        if (node->get_data() < data)
        {
            if (left == nullptr) left = node;
            else left->insert(node);
        } 
        else
        {
            if (right == nullptr) right = node;
            else right->insert(node);
        }
    }

    void preorder()
    {
        printf("%d ", data);
        if (left != nullptr) left->preorder();
        if (right != nullptr) right->preorder();
    }
    void inorder()
    {
        if (left != nullptr) left->inorder();
        printf("%d ", data);
        if (right != nullptr) right->inorder();        
    }
    void postorder()
    {
        if (left != nullptr) left->postorder();
        if (right != nullptr) right->postorder();        
        printf("%d ", data);
    }
    void levelorder()
    {
        std::queue<ptr> q;
        q.push(shared_from_this());

        while (!q.empty())
        {
            ptr node = q.front();
            q.pop();

            printf("%d ", node->get_data());

            if (node->get_left() != nullptr) q.push(node->get_left());
            if (node->get_right() != nullptr) q.push(node->get_right());

        }

        return ;        
    }

    int get_count()
    {
        if (is_leaf()) return 1;
        else if (left != nullptr && right == nullptr) return 1 + left->get_count();
        else if (left == nullptr && right != nullptr) return 1 + right->get_count();
        else if (left != nullptr && right != nullptr) return 1 + left->get_count() + right->get_count();
        else return 0;
    }

    int get_height()
    {
        if (is_leaf()) return 1;
        int h_l = left  != nullptr ? left->get_height() : 0;
        int h_r = right != nullptr ? right->get_height() : 0;
        return h_l > h_r ? h_l + 1 : h_r + 1;
    }

    int get_leaf_count()
    {
        if (is_leaf()) return 1;
        else if (left != nullptr && right == nullptr) return left->get_leaf_count();
        else if (left == nullptr && right != nullptr) return right->get_leaf_count();
        else if (left != nullptr && right != nullptr) return left->get_leaf_count() + right->get_leaf_count();
        else return 0;
    }

    int get_child_id(ptr child)
    {
        int id = 1;

        std::queue<ptr> q;
        q.push(shared_from_this());

        while (!q.empty())
        {
            ptr node = q.front();
            q.pop();

            if (node == child) return id;
            
            if (node->left != nullptr) q.push(node->left);
            if (node->right != nullptr) q.push(node->right);

            id++;
        }

        printf("Can't have proper id...");
        return -1;
    }
};


/**
 * 위 처럼 Node가 구성되면 Tree에서 코드가 더 간단해짐.
 * 트리에서 하는일은? root 만 관리하게 될듯. 애초에 node 접근 방식은 root 
 * 존재 여부를 걱정할 필요가 없어짐. 그래서 더 간단함. 이런걸 그냥 root에서
 * 실행한다고 생각하면 될듯.
 */