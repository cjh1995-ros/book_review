#include "binary_search_tree.hpp"
#include <memory>


using n_type = BinaryNode<int>;
using p_n_type = std::shared_ptr<n_type>;


int main()
{
    BinarySearchTree<int> bt;

    p_n_type d = std::make_shared<n_type>(1);
    p_n_type e = std::make_shared<n_type>(3);
    p_n_type b = std::make_shared<n_type>(2, d, e);
    p_n_type f = std::make_shared<n_type>(5);
    p_n_type c = std::make_shared<n_type>(6, f, nullptr);
    p_n_type a = std::make_shared<n_type>(4, b, c);

    bt.set_root(a);

    p_n_type tmp = bt.search(3);

    std::cout << "tmp address: " << tmp.get() << std::endl;
    std::cout << "e address: " << e.get() << std::endl;

    p_n_type tmp2 = bt.search_itr(3);

    std::cout << "tmp2 address: " << tmp2.get() << std::endl;
    std::cout << "e address: " << e.get() << std::endl;

    p_n_type new_node = std::make_shared<n_type>(7);
    bt.insert(new_node);
    bt.inorder();

    std::cout << std::endl;

    bt.remove(3);
    std::cout << "Remove 3: " << std::endl;
    bt.inorder();
    std::cout << std::endl;

    return 0;
}