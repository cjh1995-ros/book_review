#include <memory>
#include <iostream>
#include <queue>
#include <utility>



struct Node : public std::enable_shared_from_this<Node>
{
using ptr = std::shared_ptr<Node>;
    
    char data;
    ptr left;
    ptr right;

    Node(char d, ptr l = nullptr, ptr r = nullptr)
        : data(d), left(l), right(r) {}
    
    void set_left(ptr l) { left = l; }
    void set_right(ptr r) { right = r; }
    ptr get_left() { return left; }
    ptr get_right() { return right; }
    char get_data() { return data; }
    bool is_leaf() { return (left == nullptr && right == nullptr); }
    bool is_child(ptr node) 
    { 
        if (node == nullptr) return false;
        if (is_leaf()) return false;
        return (left == node || right == node); 
    }


    void show() { std::cout << data << " "; }
};




class BinaryTree
{
using ptr = std::shared_ptr<Node>;
private:
    ptr root_;
    int count_;
    int height_;

public:
    BinaryTree(): root_(nullptr) {}

    void set_root(ptr r) { root_ = r; }
    ptr  get_root() { return root_; }
    bool is_empty() { return root_ == nullptr; }


    void insert(ptr node)
    {
        // 초기화 시켜야하면
        if (root_ == nullptr)
        {
            root_ = node;
            return;
        }
        // 초기화 된 상태면 순환 구조로 insert 한다.
        insert(root_, node);
    }
    void insert(ptr parent, ptr node)
    {
        if (parent == nullptr) parent = node;
        else if (node->get_data() < parent->get_data()) insert(parent->get_left(), node);
        else insert(parent->get_right(), node);
    }

    void preorder_show() { preorder_show(root_); }
    void preorder_show(ptr r)
    {
        if (r != nullptr)
        {
            r->show();
            preorder_show(r->get_left());
            preorder_show(r->get_right());
        }
    }

    void inorder_show() { inorder_show(root_); }
    void inorder_show(ptr r)
    {
        if (r != nullptr)
        {
            inorder_show(r->get_left());
            r->show();
            inorder_show(r->get_right());
            
        }
    }

    void level_order_show()
    {
        std::queue<ptr> q;
        q.push(root_);

        while (!q.empty())
        {
            ptr node = q.front();
            q.pop();

            node->show();

            if (node->get_left() != nullptr ) q.push(node->get_left());
            if (node->get_right() != nullptr) q.push(node->get_right());
        }
    }

    int get_count() { return  is_empty() ? 0 : get_count(root_); }
    int get_count(ptr node)
    {
        if (node == nullptr) return 0;
        return 1 + get_count(node->get_left()) + get_count(node->get_right());
    }

    int get_leaf_count() { return is_empty() ? 0 : get_leaf_count(root_); }
    int get_leaf_count(ptr node)
    {
        if (node == nullptr) return 0;
        if (!node->is_leaf()) return get_leaf_count(node->get_left()) +
                                        get_leaf_count(node->get_right());
        else return 1;
    }

    int get_height() { return is_empty() ? 0 : get_height(root_); }
    int get_height(ptr node)
    {
        if (node == nullptr) return 0;
        int h_left  = get_height(node->get_left());
        int h_right = get_height(node->get_right());
        return (h_left > h_right) ? h_left + 1 : h_right + 1;
    }

    bool is_full() { return is_empty() ? false : is_full(root_); }
    bool is_full(ptr node)
    {
        // case 1. leaf 이다. 통과
        // case 2. 왼쪽 존재한다. 뭐든 상관 없음.
        // case 3. 왼쪽 없는데 오른쪽 있다. fail --> 
        // 전체 순환이 맞음. 균형이 안맞을 수도 있잖아?
        // 높이도 체크해. 
        if (node == nullptr) return true; // root_가 없음.
        if (node->is_leaf()) return true; // 말단에 도착하면 고려할게 없음.
        if (node->get_left() != nullptr) 
            return is_full(node->get_left()) && is_full(node->get_right());
        if (node->get_right() != nullptr) return false;
        return true;
    }

    int get_level(ptr node)
    {
        std::queue<std::pair<ptr, int>> q;
        
        q.push({root_, 1});

        while (!q.empty())
        {
            auto [n, current_level] = q.front();
            q.pop();

            if (n == node) return current_level;
            if (n->get_left() != nullptr ) q.push({n->get_left(), current_level+1});
            if (n->get_right() != nullptr) q.push({n->get_right(), current_level+1});
        }

        return -1;
    }

    bool is_disjoint_form(BinaryTree& that)
    {
        ptr big, small;
        
        if (get_height() > that.get_height())
        {
            big = get_root();
            small = that.get_root();
        }
        else
        {
            big = that.get_root();
            small = get_root();
        }

        std::queue<ptr> big_q;
        big_q.push(big);
        
        while (!big_q.empty())
        {
            ptr node = big_q.front();
            big_q.pop();

            if (small == node) return true;

            if (node->get_left() != nullptr) big_q.push(node->get_left());
            if (node->get_right() != nullptr) big_q.push(node->get_right());
        }

        return false;
    }

};



using ptr = std::shared_ptr<Node>;
using std::make_shared;

int main()
{
    BinaryTree bt;
    BinaryTree bt2;
    BinaryTree bt3;

    ptr h = make_shared<Node>('H');
    ptr g = make_shared<Node>('G');
    ptr d = make_shared<Node>('D', g, h);
    ptr e = make_shared<Node>('E');
    ptr b = make_shared<Node>('B', d, e);
    ptr f = make_shared<Node>('F');
    ptr c = make_shared<Node>('C', nullptr, f);
    ptr a = make_shared<Node>('A', b, c);

    ptr j = make_shared<Node>('J');
    ptr k = make_shared<Node>('K');
    ptr i = make_shared<Node>('I', j, k);

    bt.set_root(a);

    bt.preorder_show();
    std::cout << std::endl;
    bt.inorder_show();
    std::cout << std::endl;
    bt.level_order_show();
    std::cout << std::endl;
    std::cout << "Nodes number: " << bt.get_count() << std::endl;
    std::cout << "Leafs number: " << bt.get_leaf_count() << std::endl;
    std::cout << "Height: " << bt.get_height() << std::endl;
    std::cout << "Is full tree?: " << bt.is_full() << std::endl;

    std::cout << "Does 'A' is parent of 'C'?: " << a->is_child(c) << std::endl;
    std::cout << "Does 'A' is parent of 'D'?: " << a->is_child(d) << std::endl;
    std::cout << "Level of 'A': " << bt.get_level(a) << std::endl;
    std::cout << "Level of 'B': " << bt.get_level(b) << std::endl;
    std::cout << "Level of 'C': " << bt.get_level(c) << std::endl;
    std::cout << "Level of 'D': " << bt.get_level(d) << std::endl;
    std::cout << "Level of 'E': " << bt.get_level(e) << std::endl;
    std::cout << "Level of 'F': " << bt.get_level(f) << std::endl;
    std::cout << "Level of 'G': " << bt.get_level(g) << std::endl;
    std::cout << "Level of 'H': " << bt.get_level(h) << std::endl;

    bt2.set_root(d);

    bt2.level_order_show();

    bool is_it = bt.is_disjoint_form(bt2);

    std::cout << "Does bt2 is subset of bt?: " << is_it << std::endl;

    bt3.set_root(i);
    bt3.level_order_show();

    bool is_it2 = bt.is_disjoint_form(bt3);

    std::cout << "Does bt3 is subset of bt?: " << is_it2 << std::endl;


}