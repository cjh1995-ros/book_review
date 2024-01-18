#include "project_binary_search_tree.hpp"

#include <iostream>

using ptr = std::shared_ptr<Node>;

int main()
{
    ptr d = std::make_shared<Node>(1);
    ptr e = std::make_shared<Node>(3);
    ptr b = std::make_shared<Node>(2, d, e);
    ptr f = std::make_shared<Node>(5);
    ptr c = std::make_shared<Node>(6, f);
    ptr a = std::make_shared<Node>(4, b, c);

    // ptr g = std::make_shared<Node>(7);

    a->preorder();
    std::cout << std::endl;
    a->inorder();
    std::cout << std::endl;
    std::cout << "Get number of nodes: " << a->get_count() << std::endl;
    std::cout << "Height of a: " << a->get_height() << std::endl;
    std::cout << "Number of leaf of a: " << a->get_leaf_count() << std::endl;
    std::cout << "Number of leaf of b: " << b->get_leaf_count() << std::endl;

    std::cout << "Id of b in a tree is " << a->get_child_id(b) << std::endl;
    std::cout << "Id of f in a tree is " << a->get_child_id(f) << std::endl;

    c->insert(7);
    a->inorder();
    std::cout << std::endl;
}