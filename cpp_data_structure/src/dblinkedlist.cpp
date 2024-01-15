#include "double_linked_list.hpp"
#include <memory>

int main()
{
    DBLinkedList dbl;

    std::shared_ptr<Node2> n1 = std::make_shared<Node2>(10);
    std::shared_ptr<Node2> n2 = std::make_shared<Node2>(20);
    std::shared_ptr<Node2> n3 = std::make_shared<Node2>(30);
    std::shared_ptr<Node2> n4 = std::make_shared<Node2>(40);


    dbl.insert(0, n1);
    dbl.insert(1, n2);
    dbl.insert(2, n3);
    dbl.insert(3, n4);

    dbl.print();

    dbl.find(10);

    return 0;
}