#include "binary_tree.hpp"
#include <memory>


using b_char = BinaryNode<char>;
using p_char = std::shared_ptr<b_char>;


int main()
{
    BinaryTree<char> bt;

    p_char d = std::make_shared<b_char>('D');
    p_char e = std::make_shared<b_char>('E');
    p_char b = std::make_shared<b_char>('B', d, e);
    p_char f = std::make_shared<b_char>('F');
    p_char c = std::make_shared<b_char>('C', f, nullptr);
    p_char a = std::make_shared<b_char>('A', b, c);

    bt.set_root(a);

    std::cout << "In Tree!" << std::endl;
    bt.preorder(bt.get_root());
    std::cout << std::endl;
    bt.inorder(bt.get_root());
    std::cout << std::endl;
    bt.postorder(bt.get_root());
    std::cout << std::endl;

    std::cout << "In Node!" << std::endl;
    bt.preorder();
    std::cout << std::endl;
    bt.inorder();
    std::cout << std::endl;
    bt.postorder();
    std::cout << std::endl;

    std::cout << "Level order!" << std::endl;
    bt.levelorder();
    std::cout << std::endl;

    std::cout << "Total number of nodes: " << bt.get_count() << std::endl;

    std::cout << "Total number of leafs: " << bt.get_leaf_count() << std::endl;

    std::cout << "Height of tree: " << bt.get_height() << std::endl;


    
    return 0;
}